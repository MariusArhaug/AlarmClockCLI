#ifndef CLOCK_H
#define CLOCK_H

#define _POSIX_SOURCE
#define __USE_XOPEN
#define __GNU_SOURCE
#include <time.h>
#include <sys/types.h>

#define INIT_SIZE 10

typedef struct {
  time_t time;
  pid_t pid;
} alarm_t ;

typedef struct  {
  alarm_t *alarms;
  int capacity;
  int length;
} alarm_clock_t;


alarm_clock_t* initialize(void);

void push(alarm_clock_t *, alarm_t);

void free_clock(alarm_clock_t *);

alarm_t create_alarm(alarm_clock_t*, time_t, int);

alarm_t remove_alarm(alarm_clock_t*, int);

int find_index(alarm_clock_t*, pid_t);

int handler(int, alarm_clock_t*);

#endif