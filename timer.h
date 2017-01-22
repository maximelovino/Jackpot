/**
 * @file timer.h
 * @brief Header file that contains a timer definition
 *
 * @authors Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date January 22, 2017
 * @version 1.0
 */

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
