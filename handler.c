/**
 * @file handler.c
 * @brief Source file that contains our signal handler and game controller implementation
 *
 * @authors Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date January 22, 2017
 * @version 1.0
 */

#include "handler.h"

/**
 * Function to check the result of a game
 * @param vals A pointer to the first element of the array of wheels values
 * @return 0 in case of no win, 1 in case of double win, 2 in case of jackpot
 */
int checkVals(unsigned int* vals){
	int values[10] = {0};
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		values[vals[i]]++;
	}
	int max = 0;
	for (size_t i = 0; i < 10; i++) {
		if (values[i]>max) {
			max = values[i];
		}
	}
	return max == 1 ? 0 : max == WHEEL_COUNT ? 2 : 1;
}

/**
 * Function that the handler thread will run
 * @param args A pointer to the arguments of the thread
 * @return NULL
 */
void* handle(void* args){
	HandlerArgs* hArgs = (HandlerArgs*) args;
	sigset_t mask;
	sigfillset(&mask);
	int sig;
	int currentWheel = 0;
	do {
		if (currentWheel == WHEEL_COUNT) {
			alarm(0);
			*hArgs->score = checkVals(hArgs->values);
			if (*hArgs->score == 1) {
				*hArgs->lastGain = *hArgs->money >=2 ? 2 : *hArgs->money;
			}else if (*hArgs->score == 2) {
				*hArgs->lastGain = *hArgs->money / 2;
			}else{
				*hArgs->lastGain = 0;
			}
			*hArgs->money -= *hArgs->lastGain;
			*(hArgs->state) = DONE;
			sleep(5);
			*(hArgs->state) = WAITING;
			currentWheel = 0;
		}
		sigwait(&mask, &sig);
		if (sig == SIGTSTP) {
			*(hArgs->state) = RUNNING;
			currentWheel = 0;
			*(hArgs->money) += 1;
			for (size_t i = 0; i < WHEEL_COUNT; i++) {
				(hArgs->runningBools)[i] = 1;
			}
			pthread_cond_broadcast(hArgs->wheelCond);
			alarm(3);
		}
		if (sig == SIGINT || sig == SIGALRM) {
            if (*hArgs->state == RUNNING){
                (hArgs->runningBools)[currentWheel] = 0;
                currentWheel++;
				alarm(3);
            }
		}
	} while(sig != SIGQUIT);

	*(hArgs->state) = QUITTING;
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		(hArgs->runningBools)[i] = 0;
	}
	pthread_cond_broadcast(hArgs->wheelCond);

	return NULL;
}
