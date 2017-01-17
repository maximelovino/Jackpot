#ifndef _HANDLER_H_
#define _HANDLER_H_
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include "const.h"

typedef struct HandlerArgs {
	State* state;
	pthread_cond_t* runningConds;
	int* runningBools;
} HandlerArgs;

void* handle(void* args);

#endif /* end of include guard: _HANDLER_H_ */
