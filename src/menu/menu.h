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
int menu_loop(alarm_clock_t*);

/**
 * @briefprint out current time to stdout. 
 * 
 * @param time time to be printed. 
 */
void show_time(struct tm*);

/**
 * @brief Schedule alarm clock. Prompt user to input in the following format "%Y-%m-%d %H:%M:%S"
 * 
 * After setting alarm a child process waits until the alarm reaches its deadline. 
 * Then it will either print "RING" or make a noise
 * 
 * @param clock take in clock struct pointer
 * @param current_time current_time when program started
 */
void schedule_menu(alarm_clock_t*, struct tm*);

/**
 * @brief Function that lets user choose wich ringtone it wants on each of the alarms.
 * 
 * @param takes in the alarm_clock struct pointer
*/
void choose_ringtone(alarm_clock_t* clock);


/**
 * @brief list out all alarms set by user 
 * 
 * @param clock alarm clock we want to read alarms from. 
 */
void list_menu(alarm_clock_t*);

/**
 * @brief Open menu to cancel alarms for a given clock.
 * 
 * Input is the corresponding index in the clock's alarm array. 
 * If index < 0 or index > clock.alarms.length, ask for new user input.
 * 
 * @param clock clock that we want to cancel alarms for  
 */
void cancel_menu(alarm_clock_t*);


/**
 * @brief Get the current time object
 * 
 * @return tm_t* time object
 **/
struct tm* get_current_time();

#endif