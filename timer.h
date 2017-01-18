#ifndef _TIMER_H_
#define _TIMER_H_
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "const.h"

typedef struct TimerArgs {
	State* st;
	pthread_cond_t* timerCond;
	pthread_mutex_t* mutex;
} TimerArgs;

void* timeRun(void* args);

#endif /* end of include guard: _TIMER_H_ */
