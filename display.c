#include "display.h"
void displayWheels(unsigned int* vals)
{
	for(int i = 0 ; i < WHEEL_COUNT ; i++)
	{
		printf("%c ", WHEELS_SYMBOLS[vals[i]]);
	}
	printf("\n");
}

void* work(void* arg)
{
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	DisplayArgs* args = (DisplayArgs*) arg;
	unsigned int* vals = args->wheelsValue;
	struct timespec start, finish;
	while(*(args->state) != QUITTING)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		printf("\e[2J");
		printf("\e[1;1H");
		if(*(args->state) == WAITING)
		{
			printf("Insert a coin to start the game...\n");
		}
		else if(*(args->state) == DONE)
		{
			printf("Game finished!\n\n");
			displayWheels(vals);
			switch (*args->score) {
				case 0:
					printf("YOU LOST!\n");
					break;
				case 1:
					printf("DOUBLE WIN\n");
					break;
				case 2:
					printf("JACKPOT\n");
					break;
				default:
					break;
			}
			printf("You won %d coins\n", *args->lastGain);
			printf("%i coins in the machine\n", *args->money);
		}
		else
		{
			printf("Game started!\n\n");
			displayWheels(vals);
		}

		clock_gettime(CLOCK_MONOTONIC, &finish);
		double seconds_elapsed = finish.tv_sec-start.tv_sec;
		seconds_elapsed += (finish.tv_nsec-start.tv_nsec)/(double)1e9;
		if (seconds_elapsed < 1.0/30.0) {
			usleep((1.0/30.0 - seconds_elapsed)*1e6);
		}
	}
	return NULL;
}
