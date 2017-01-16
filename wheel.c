#include "wheel.h"

void* turn(void* arg) {
	Wheel* wheel = (Wheel*) arg;
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	while (*wheel->state != QUITTING) {
		pthread_mutex_lock(wheel->mutex);
		pthread_cond_wait(wheel->cond, wheel->mutex);
		pthread_mutex_unlock(wheel->mutex);
		*wheel->value = 0;
		while (*wheel->running) {
			*wheel->value = (*wheel->value + 1) % 10;
			usleep(wheel->speed * 1000);
		}
	}
	return NULL;
}
