/**
 * @file display.h
 * @brief Header file that contains our display definition
 *
 * @authors Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date January 22, 2017
 * @version 1.0
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "const.h"
#include <signal.h>
#include <pthread.h>

typedef struct DispalyArgs_t
{
	unsigned int* wheelsValue;
	State* state;
	unsigned int* money;
	unsigned int* score;
	unsigned int* lastGain;
} DisplayArgs;

void displayWheels(unsigned int* vals);
void* work(void* arg);

#endif /* end of include guard: _DISPLAY_H_ */
