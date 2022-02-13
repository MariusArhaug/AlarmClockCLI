#ifndef CLOCK_H
#define CLOCK_H

#define INIT_SIZE 10
#define FAKE_SIGNAL 0
#define NOT_FOUND -1
#define CHILD_TERMINATED 1 
#define CHILD_NOT_TERMINATED 0

#include "alarm.h"

struct clock_t {
  struct alarm_t **alarms; //can be upgraded to be array of pointers 
  int capacity;
  int length;
};

/**
 * @brief initialize clock structure
 * 
 */
void clock_init(struct clock_t*);

/**
 * @brief Push alarm to clock  
 * 
 * @param clock clock to add alarm to 
 * @param alarm alarm to be added.
 */
void push(struct clock_t *, struct alarm_t*);

/**
 * @brief free clock struct from memory 
 * Frees first its alarms, then sets is length/capacity to 0 
 * finally frees the pointer.
 * @param clock clock to be freed from memory.
 */
void destroy(struct clock_t *);

/**
 * @brief Create a alarm to be added to clock
 * 
 * @param clock clock we want to add a
 * @param time 
 * @param difference 
 * @return alarm_t 
 */
//struct alarm_t add_alarm(struct clock_t*, struct alarm_t*);

/**
 * @brief removes alarm from clock at given index
 * 
 * @param clock clock to remove alarm from
 * @param index index of the given alarm.
 * @return alarm_t 
 */
struct alarm_t* remove_alarm(struct clock_t*, int);

/**
 * @brief find index of alarm given its pid. 
 * 
 * @param clock clock to search through 
 * @param pid pid for alarm we want to find
 * @return int index of found alarm or NOT_FOUND (-1).
 */
int find_index(struct clock_t*, pid_t);

/**
 * @brief check if any child process has terminated without blocking. 
 * 
 * If found terminated child process it will be removed from clock array. and freed from memory.
 * 
 * @return 1 if found terminated process and updated clock accordingly, else 0
 */
int update_clock(struct clock_t*);

#endif