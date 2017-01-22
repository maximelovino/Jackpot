/**
 * @file timer.c
 * @brief Source file that contains a timer implementation
 *
 * @authors Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date January 22, 2017
 * @version 1.0
 */

#include "timer.h"

/**
 * Function that the timer thread will run
 * @param args A pointer to the arguments of the thread
 * @return NULL
 */
void* timeRun(void* args){
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	TimerArgs* tArgs = (TimerArgs*) args;
	while (*tArgs->st != QUITTING) {
		pthread_mutex_lock(tArgs->mutex);
		pthread_cond_wait(tArgs->timerCond, tArgs->mutex);
		pthread_mutex_unlock(tArgs->mutex);
		while (*tArgs->st == RUNNING) {
			sleep(1);
			kill(getpid(), SIGUSR1);
		}
	}
	return NULL;
}
