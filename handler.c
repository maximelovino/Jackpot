#include "handler.h"

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

void* handle(void* args){
	HandlerArgs* hArgs = (HandlerArgs*) args;
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	int sig;
	int currentWheel = 0;
	int sigCount = 0;
	do {
		if (currentWheel == WHEEL_COUNT) {
			//Calculate score, pay up what's needed, and go in "show score" state and then after 5s in "waiting for coin"
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
			// notify the running at index of currentWheel
			/* we inserted a coin */
			*(hArgs->state) = RUNNING;
			pthread_cond_signal(hArgs->timerCond);
			*(hArgs->money) += 1;
			// We loop over WHEEL_COUNT and put all running to true, and then in the same loop we notify all conditions
			for (size_t i = 0; i < WHEEL_COUNT; i++) {
				(hArgs->runningBools)[i] = 1;
				pthread_cond_signal(&((hArgs->runningConds)[i]));
			}
		}
		if (sig == SIGINT) {
			/* we blocked a wheel */
			(hArgs->runningBools)[currentWheel] = 0;
			currentWheel++;
			sigCount = 0;
		}
		if (sig == SIGUSR1) {
			sigCount++;
			if (sigCount >= 3) {
				raise(SIGINT);
				sigCount = 0;
			}
		}
	} while(sig != SIGQUIT);

	*(hArgs->state) = QUITTING;
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		(hArgs->runningBools)[i] = 0;
		pthread_cond_signal(&((hArgs->runningConds)[i]));
	}

	return NULL;
}
