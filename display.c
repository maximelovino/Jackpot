#include "display.h"

void initDisplay(DisplayArgs* args)
{

}

void displayWheels(DisplayArgs* args)
{
	for(int i = 0 ; i < WHEEL_COUNT ; i++)
	{
		printf("%d ", *((args->wheelsValue)[i]);
	}
}

void work(DisplayArgs* args)
{
	struct timespec start, finish;
	while(*(args->state) != QUITTING)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		printf("\e[2J");
		if(*(args->state) == WAITING))
		{
			printf("Insert a coin to start the game...\n");
		}
		else if(*(args->state) == DONE))
		{
			printf("Game finished!\n\n");
			displayWheels(args);
		}
		else
		{
			printf("Game started!\n\n");
			displayWheels(args);
		}

		clock_gettime(CLOCK_MONOTONIC, &finish);
		double seconds_elapsed = finish.tv_sec-start.tv_sec;
		seconds_elapsed += (finish.tv_nsec-start.tv_nsec)/1000000000.0;
	}
}
