#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "handler.h"
#include "wheel.h"
#include "display.h"
#include <signal.h>
#include "const.h"
#include "timer.h"
#include <time.h>

int main() {
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	int runningWheels[WHEEL_COUNT] = {0};
	pthread_cond_t conditions[WHEEL_COUNT];
	unsigned int values[WHEEL_COUNT] = {0};
	unsigned int speeds[WHEEL_COUNT] = WHEEL_SPEED;
	unsigned int money = INITIAL_MONEY;
	unsigned int score = 0;
	unsigned int lastGain = 0;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	State st = WAITING;
	pthread_t wheelThreads[WHEEL_COUNT];
	pthread_cond_t timerCond;

	pthread_t timerThread;
	TimerArgs timerArgs;
	timerArgs.st = &st;
	timerArgs.mutex = &mutex;
	timerArgs.timerCond = &timerCond;
	pthread_create(&timerThread, NULL, timeRun, &timerArgs);

	HandlerArgs handleArgs;
	handleArgs.state = &st;
	handleArgs.runningConds = conditions;
	handleArgs.runningBools = runningWheels;
	handleArgs.values = values;
	handleArgs.money = &money;
	handleArgs.score = &score;
	handleArgs.lastGain = &lastGain;
	handleArgs.timerCond = &timerCond;
	pthread_t handleThread;
	if (pthread_create(&handleThread, NULL, handle, &handleArgs) != 0) {
		fprintf(stderr, "There was a problem creating a thread\n");
		_exit(EXIT_FAILURE);
	}

	DisplayArgs dArgs;
	dArgs.state = &st;
	dArgs.wheelsValue = values;
	dArgs.money = &money;
	dArgs.score = &score;
	dArgs.lastGain = &lastGain;
	pthread_t displayThread;
	if (pthread_create(&displayThread, NULL, work, &dArgs) != 0) {
		fprintf(stderr, "There was a problem creating a thread\n");
		_exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		pthread_cond_init(&(conditions[i]), NULL);
		Wheel* args = malloc(sizeof(Wheel));
		if (!args) {
			fprintf(stderr, "There was a problem with a malloc\n");
			_exit(EXIT_FAILURE);
		}
		args->cond = &(conditions[i]);
		args->mutex = &mutex;
		args->running = &(runningWheels[i]);
		args->speed = speeds[i];
		args->state = &st;
		args->value = &(values[i]);
		if (pthread_create(&(wheelThreads[i]), NULL, turn, args) != 0) {
			fprintf(stderr, "There was a problem creating a thread\n");
			_exit(EXIT_FAILURE);
		};
	}
	pthread_join(timerThread, NULL);
	pthread_join(displayThread, NULL);
	pthread_join(handleThread, NULL);
	for (size_t i = 0; i < WHEEL_COUNT; i++) {
		pthread_join(wheelThreads[i], NULL);
	}
	return 0;
}
