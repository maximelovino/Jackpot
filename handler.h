/**
 * @file handler.h
 * @brief Header file that contains our signal handler and game controller definition
 *
 * @authors Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date January 22, 2017
 * @version 1.0
 */

#ifndef _HANDLER_H_
#define _HANDLER_H_
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include "const.h"

typedef struct HandlerArgs {
	State* state;
	pthread_cond_t* wheelCond;
	pthread_cond_t* timerCond;
	int* runningBools;
	unsigned int* values;
	unsigned int* money;
	unsigned int* score;
	unsigned int* lastGain;
} HandlerArgs;

void* handle(void* args);

#endif /* end of include guard: _HANDLER_H_ */
