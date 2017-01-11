#ifndef NUCLEAR_DISPLAY_SHELTER
#define NUCLEAR_DISPLAY_SHELTER

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "const.h"

typedef struct DispalyArgs_t
{
	int** wheelsValue = NULL;
	State* state = NULL;
} DisplayArgs;

void initDisplay(DisplayArgs* args);
void displayWheels(DisplayArgs* args);
void work(DisplayArgs* args);

#endif /* end of include guard: _DISPLAY_H_ */
