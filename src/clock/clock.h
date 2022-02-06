#ifndef CLOCK_H
#define CLOCK_H

#define _POSIX_SOURCE
#define __USE_XOPEN
#define __GNU_SOURCE
#include <time.h>
#include <sys/types.h>

#define INIT_SIZE 10
#define FAKE_SIGNAL 0
#define NOT_FOUND -1

typedef struct {
  time_t time;
  pid_t pid;
} alarm_t ;

typedef struct  {
  alarm_t *alarms;
  int capacity;
  int length;
} alarm_clock_t;

/**
 * @brief initialize clock structure
 * 
 * @returna alarm_clock_t* pointer to clock structure 
 */
alarm_clock_t* initialize(void);

/**
 * @brief Push alarm to clock  
 * 
 * @param clock clock to add alarm to 
 * @param alarm alarm to be added.
 */
void push(alarm_clock_t *, alarm_t);

/**
 * @brief free clock struct from memory 
 * Frees first its alarms, then sets is length/capacity to 0 
 * finally frees the pointer.
 * @param clock clock to be freed from memory.
 */
void free_clock(alarm_clock_t *);

/**
 * @brief Create a alarm to be added to clock
 * 
 * @param clock clock we want to add a
 * @param time 
 * @param difference 
 * @return alarm_t 
 */
alarm_t create_alarm(alarm_clock_t*, time_t, int);

/**
 * @brief removes alarm from clock at given index
 * 
 * @param clock clock to remove alarm from
 * @param index index of the given alarm.
 * @return alarm_t 
 */
alarm_t remove_alarm(alarm_clock_t*, int);

/**
 * @brief find index of alarm given its pid. 
 * 
 * @param clock clock to search through 
 * @param pid pid for alarm we want to find
 * @return int index of found alarm or NOT_FOUND (-1).
 */
int find_index(alarm_clock_t*, pid_t);

/**
 * @brief handler (callback) to be ran after parent process notices child process is terminated
 * 
 * This is intially run with clock pointer and a fake signal. It then stores the pointer internally. 
 * And then finally manipulates data at that given pointer. 
 * In this case, removes alarm from clock when the alarm process has terminated
 * 
 * Really hacky solution, personally feels wierd...
 * 
 * @param signal signal from signal listener
 * @param ptr ptr to clock.
 * @return i
 */

int handler(int, alarm_clock_t*);

#endif