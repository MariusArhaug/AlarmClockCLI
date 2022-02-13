#ifndef TEST_H
#define TEST_h

#define __POSIX_C_SOURCE
#define _POSIX_SOURCE
#define __USE_XOPEN
#define __USE_POSIX
#define __GNU_SOURCE
#define __USE_MISC

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define FAIL(_x, _e, _g) printf(ANSI_COLOR_RED _x " EXPECTED: %d, GOT: %d %s \n", _e, _g, ANSI_COLOR_RESET)
#define SUCCESS(_x) printf(ANSI_COLOR_GREEN "%s %s \n", _x, ANSI_COLOR_RESET)
#define SUITE(_x) printf(ANSI_COLOR_YELLOW _x  "%d" "\n" ANSI_COLOR_RESET, (__COUNTER__ + 1));

#include "../src/clock/clock.h"
#include "../src/menu/menu.h"

/**
 * 
 * @brief test the time from show_time() and get_current_time() form menu.c 
*/
void test_time();

/**
 * @brief test the set_alarm function in alarm.c
 *  
*/
void test_create_alarm(struct clock_t* clock);

/**
 * @brief test the list menu function and that the alarm is correctly set
 * 
*/
void test_list_menu(struct clock_t *clock);

/**
 * @brief test the remove_alarm function in clock.c
 * 
*/
void test_remove_alarm(struct clock_t* clock);

#endif