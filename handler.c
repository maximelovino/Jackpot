#include "handler.h"

int checkVals(unsigned int* vals){
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		int cnt = 0;
		unsigned int temp = vals[i];
		for (size_t j = i+1; j < WHEEL_COUNT; j++) {
			if (vals[j] == temp) {
				cnt++;
			}
		}
		if (cnt >= 1) {
			return cnt;
		}
	}
	return 0;
}

void* handle(void* args){
	HandlerArgs* hArgs = (HandlerArgs*) args;
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	int sig;
	int currentWheel = 0;
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
		}
	} while(sig != SIGQUIT);

	*(hArgs->state) = QUITTING;
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		(hArgs->runningBools)[i] = 0;
		pthread_cond_signal(&((hArgs->runningConds)[i]));
	}

	return NULL;
}
