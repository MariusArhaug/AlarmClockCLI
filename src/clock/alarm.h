#ifndef ALARM_H
#define ALARM_H

#define _POSIX_SOURCE
#define __USE_XOPEN
#define __USE_POSIX
#define __GNU_SOURCE
#include <time.h>
#include <sys/types.h>


struct alarm_t {
  time_t time;
  pid_t pid;
};


void alarm_init(struct alarm_t*, time_t, int); 



#endif