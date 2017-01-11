#include "handler.h"

void* handle(void* args){
	HandlerArgs* hArgs = (HandlerArgs*) args;
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	int sig;
	int currentWheel = 0;
	do {
		if (currentWheel == hArgs->threadCnt) {
			/* Game is done */
		}
		sigwait(&mask, &sig);
		if (sig == SIGTSTP) {
			// notify the running at index of currentWheel
			/* we inserted a coin */
		}
		if (sig == SIGINT) {
			/* we blocked a wheel */
		}
	} while(sig != SIGQUIT);
	return NULL;
}
