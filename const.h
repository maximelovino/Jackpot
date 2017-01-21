#ifndef _CONST_H_
#define _CONST_H_

#ifndef WHEEL_COUNT
#define WHEEL_COUNT 3
#endif

#ifndef WHEEL_SPEED
#define WHEEL_SPEED {120, 60, 30}
#endif

#ifndef WHEELS_SYMBOLS
#define WHEELS_SYMBOLS {'#','$','%','+','-','=','?'};
#endif

typedef enum State {QUITTING, RUNNING, DONE, WAITING} State;
#endif /* end of include guard: _CONST_H_ */
