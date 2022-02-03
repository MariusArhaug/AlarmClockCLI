#ifndef CLOCK_H
#define CLOCK_H

#define __USE_XOPEN
#define __GNU_SOURCE
#include "time.h"

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

#endif