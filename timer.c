#include "Timer.h"

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
