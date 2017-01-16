#ifndef _WHEEL_H_
#define _WHEEL_H_
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include "const.h"
#include "unistd.h"

typedef struct wheel_st {
    pthread_cond_t* cond;
    pthread_mutex_t* mutex;
    unsigned int speed;
    State* state;
    unsigned int* value;
	int* running;
} Wheel;

void* turn(void* arg);

#endif /* end of include guard: _WHEEL_H_ */
