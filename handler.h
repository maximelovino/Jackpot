#ifndef _HANDLER_H_
#define _HANDLER_H_
#include <stdlib.h>
#include <signal.h>
#include "const.h"

void* handle(void* args){
	sigset_t mask;
	sigfillset(&mask);
	return NULL;
}

#endif /* end of include guard: _HANDLER_H_ */
