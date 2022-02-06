#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "clock.h"


alarm_clock_t* initialize()
{
  
  alarm_clock_t* clock = malloc(sizeof(alarm_clock_t));

  clock->capacity = INIT_SIZE;
  clock->length = 0;
  clock->alarms = malloc(clock->capacity * sizeof(alarm_t));
  return clock;
}

void push(alarm_clock_t* clock, alarm_t alarm)
{
  // Need to reallocate memory if array has reached max capcaity. 
  if (clock->length == clock->capacity)
  {
    clock->capacity *= 2;
    clock->alarms = realloc(clock->alarms, clock->capacity * sizeof(alarm_t));
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

alarm_t create_alarm(alarm_clock_t* clock, time_t time, int difference)
{
  alarm_t alarm;
  alarm.time = time;

  signal(SIGCHLD, (void (*)(int))handler);
  handler(FAKE_SIGNAL, clock);

  pid_t pid = fork();  
  
  if (pid == 0) {
    /* child process */
    sleep(difference);
    execl("/bin/mpg123", "/bin/mpg123", "-q" ,"./audio/alarm.mp3", NULL); //TODO make user choose alarm sound.
    exit(EXIT_SUCCESS);
  } 

  alarm.pid = pid;
  push(clock, alarm);
  
 
  return alarm;
}

alarm_t remove_alarm(alarm_clock_t* clock, int index) 
{
  alarm_t alarm = clock->alarms[index]; // get alarm we want to remove


  // create temp array with same size as before
  alarm_t * updated_array = malloc(clock->capacity * sizeof(alarm_t));

  // move the old array from start (clock->alamrs pointer starts at begining of array)
  // until it reaches the index.
  memmove(
    updated_array,
    clock->alarms,
    (index+1)*sizeof(alarm_t)
  );

  // oppsite here, move last part of array into updated array.
  memmove(
    updated_array+index,
    clock->alarms+(index+1),
    (clock->capacity - index)*sizeof(alarm_t)
  );

  free(clock->alarms);  // free old array.
  clock->alarms = updated_array; // assign new array.
  clock->length -= 1;
  kill(alarm.pid, SIGKILL);     // kill alarm process of the child we removed.
  return alarm;
}

int find_index(alarm_clock_t * clock, pid_t pid)
{
  for (int i = 0; i < clock->length; i++) 
  {
    if (clock->alarms[i].pid == pid)
      return i;
  }
  return NOT_FOUND;
}

int handler(const int signal, alarm_clock_t* ptr) {
  pid_t pid = wait(NULL);
  static alarm_clock_t * saved = NULL;

  if (saved == NULL)
     saved = ptr;
  if (signal == SIGCHLD) {
    int index = find_index(saved, pid);
    remove_alarm(saved, index);
  }
      
  return 0;
}