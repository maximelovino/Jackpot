#ifndef _WHEEL_H_
#define _WHEEL_H_
#include <pthread.h>
#include <stdlib.h>
#include "const.h"

typedef struct wheel_st {
    pthread_cond_t running;
    pthread_mutex_t mutex;
    unsigned int speed;
    State state;
    unsigned int* value;
} Wheel;

void* turn(void* arg);

#endif /* end of include guard: _WHEEL_H_ */
