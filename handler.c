#include "handler.h"

#include <stdio.h>

void* handle(void* args){
	HandlerArgs* hArgs = (HandlerArgs*) args;
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	puts("Everything blocked");
	int sig;
	int currentWheel = 0;
	do {
		sigwait(&mask, &sig);
		if (sig == SIGTSTP) {
			// notify the running at index of currentWheel
			/* we inserted a coin */
			puts("We've got a sigstp");
		}
		if (sig == SIGINT) {
			/* we blocked a wheel */
			puts("We've got a sigint");
		}
	} while(sig != SIGQUIT);
	printf("We've got a sigquit\n");
	return NULL;
}
