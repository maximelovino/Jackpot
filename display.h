#ifndef NUCLEAR_DISPLAY_SHELTER
#define NUCLEAR_DISPLAY_SHELTER

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "const.h"

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
