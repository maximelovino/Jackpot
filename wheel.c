#include "wheel.h"

void* turn(void* arg) {
    Wheel* wheel = (Wheel*) arg;
    
    while(wheel->state != QUITTING) {
        while(wheel->state == RUNNING) {
            pthread_cond_wait(&(wheel->running), &(wheel->mutex));
            *(wheel->value) = *(wheel->value)+1 % 10;
        }
        wheel->value = 0;
    }
    return NULL;
}
