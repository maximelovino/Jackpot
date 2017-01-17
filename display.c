#include "display.h"

void displayWheels(unsigned int* vals)
{
	for(int i = 0 ; i < WHEEL_COUNT ; i++)
	{
		printf("%d ", vals[i]);
	}
	printf("\n");
}

void* work(void* arg)
{
	DisplayArgs* args = (DisplayArgs*) arg;
	unsigned int* vals = args->wheelsValue;
	struct timespec start, finish;
	while(*(args->state) != QUITTING)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		printf("\e[2J");
		if(*(args->state) == WAITING)
		{
			printf("Insert a coin to start the game...\n");
		}
		else if(*(args->state) == DONE)
		{
			printf("Game finished!\n\n");
			displayWheels(vals);
			printf("%i coins in the machine\n", *args->money);
		}
		else
		{
			printf("Game started!\n\n");
			displayWheels(vals);
		}

		clock_gettime(CLOCK_MONOTONIC, &finish);
		double seconds_elapsed = finish.tv_sec-start.tv_sec;
		seconds_elapsed += (finish.tv_nsec-start.tv_nsec)/1000000000.0;
		usleep(33333);
	}
	return NULL;
}
