/**
 * @file const.h
 * @brief A file to define constants used by our program
 *
 * @authors Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date January 22, 2017
 * @version 1.0
 */

#ifndef _CONST_H_
#define _CONST_H_

#ifndef WHEEL_COUNT
#define WHEEL_COUNT 3
#endif

#ifndef WHEEL_SPEED
#define WHEEL_SPEED {120, 60, 30}
#endif

#ifndef INITIAL_MONEY
#define INITIAL_MONEY 12
#endif

static const char WHEELS_SYMBOLS[] = {'#','$','%','+','-','=','?'};
typedef enum State {QUITTING, RUNNING, DONE, WAITING} State;
#endif /* end of include guard: _CONST_H_ */
