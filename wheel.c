#include "wheel.h"

void* turn(void* arg) {
	Wheel* wheel = (Wheel*) arg;
	sigset_t mask;
	sigfillset(&mask);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	struct timespec start, finish;
	while (*wheel->state != QUITTING) {
		pthread_mutex_lock(wheel->mutex);
		pthread_cond_wait(wheel->cond, wheel->mutex);
		pthread_mutex_unlock(wheel->mutex);
		*wheel->value = 0;
		while (*wheel->running) {
			clock_gettime(CLOCK_MONOTONIC, &start);
			*wheel->value = (*wheel->value + 1) % sizeof(WHEELS_SYMBOLS);
			clock_gettime(CLOCK_MONOTONIC, &finish);
			double seconds_elapsed = finish.tv_sec-start.tv_sec;
			seconds_elapsed += (finish.tv_nsec-start.tv_nsec)/(double)1e9;
			if (seconds_elapsed < wheel->speed / 1e3) {
				usleep((wheel->speed / 1e3 - seconds_elapsed) * 1e6);
			}
		}
	}
	free(wheel);
	return NULL;
}
