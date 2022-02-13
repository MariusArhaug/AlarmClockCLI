#ifndef MENU_H
#define MENU_H

#define _POSIX_C_SOURCE
#define __USE_MISC
#define __USE_XOPEN
#define __GNU_SOURCE
#include <stdint.h>
#include <time.h>
#include "../clock/clock.h"


#define MAX_INPUT_SIZE 256

/**
 * @brief Main menu loop that keeps the program running 
 * 
 * @param clock clock that we want to mutate. 
 * @return int returns 0 if exited correctly.
 */
int menu_loop(struct clock_t*);


#endif