#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "Handler.h"
#include "Wheel.h"
#include "const.h"

int main(int argc, char const *argv[]) {
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	int runningWheels[WHEEL_COUNT] = {0,0,0};
	pthread_cond_t conditions[WHEEL_COUNT];
	unsigned int values[WHEEL_COUNT] = {0,0,0};
	unsigned int speeds[WHEEL_COUNT] = {120,60,30};
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	State st = WAITING;
	pthread_t wheelThreads[WHEEL_COUNT];

	HandlerArgs handleArgs;
	handleArgs.runningConds = conditions;
	handleArgs.threadCnt = WHEEL_COUNT;
	pthread_t handleThread;
	pthread_create(&handleThread, NULL, handle, &handleArgs);

	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		pthread_cond_init(&(conditions[i]), NULL);
		Wheel* args = malloc(sizeof(Wheel));
		args->cond = &(conditions[i]);
		args->mutex = &mutex;
		args->running = &(runningWheels[i]);
		args->speed = speeds[i];
		args->state = st;
		args->value = &(values[i]);
		if (pthread_create(&(wheelThreads[i]), NULL, turn, (void*) args) != 0) {
			fprintf(stderr, "There was a problem creating a thread\n");
			_exit(EXIT_FAILURE);
		};
	}
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		pthread_join(wheelThreads[i], NULL);
	}
	return 0;
}
