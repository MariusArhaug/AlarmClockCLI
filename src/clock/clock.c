#include "clock.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

alarm_clock_t* initialize()
{
  
  alarm_clock_t* clock = malloc(sizeof(alarm_clock_t));

  clock->capacity = INIT_SIZE;
  clock->length = 0;
  clock->alarms = malloc(clock->length * sizeof(alarm_t));
  return clock;
}


void push(alarm_clock_t* clock, alarm_t alarm)
{
  // Need to reallocate memory if array has reached max capcaity. 
  if (clock->length == clock->capacity)
  {
    clock->capacity *= 2;
    clock->alarms = realloc(clock->alarms, sizeof(alarm_t) * clock->capacity);
  }

  clock->alarms[clock->length++] = alarm;
}

void free_clock(alarm_clock_t* clock) 
{
  free(clock->alarms);
  clock->alarms = NULL;
  clock->length = clock->capacity = 0;
  free(clock);
}

alarm_t create_alarm(time_t time, int difference)
{
  alarm_t alarm;
  alarm.time = time;

  pid_t pid = fork();  
  alarm.pid = pid;
  if (pid == 0) {
    /* child process */
    sleep(difference);
    printf("RING! \n");
    exit(EXIT_SUCCESS);
  }

  return alarm;

}

alarm_t remove_alarm(alarm_clock_t* clock, int index) 
{
  alarm_t alarm = clock->alarms[index];


  alarm_t * updated_array = malloc(clock->capacity * sizeof(alarm_t));

  memmove(
    updated_array,
    clock->alarms,
    (index+1)*sizeof(alarm_t)
  );

  memmove(
    updated_array+index,
    clock->alarms+(index+1),
    (clock->capacity - index)*sizeof(alarm_t)
  );

  free(clock->alarms);
  clock->alarms = updated_array;
  clock->length -= 1;
  kill(alarm.pid, SIGKILL);
  return alarm;
}