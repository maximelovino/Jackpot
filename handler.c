#include "handler.h"


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
		}
		sigwait(&mask, &sig);
		if (sig == SIGTSTP) {
			// notify the running at index of currentWheel
			/* we inserted a coin */
			*(hArgs->state) = RUNNING;
			// We loop over WHEEL_COUNT and put all running to true, and then in the same loop we notify all conditions
			for (size_t i = 0; i < WHEEL_COUNT; i++) {
				(hArgs->runningBools)[i] = 1;
				pthread_cond_signal(&((hArgs->runningConds)[i]));
			}
		}
		if (sig == SIGINT) {
			/* we blocked a wheel */
		}
	} while(sig != SIGQUIT);

	*(hArgs->state) = QUITTING;
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		(hArgs->runningBools)[i] = 0;
		pthread_cond_signal(&((hArgs->runningConds)[i]));
	}

	return NULL;
}
