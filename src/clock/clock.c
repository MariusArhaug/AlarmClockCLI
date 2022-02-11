#include "clock.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>


void clock_init(struct clock_t *self)
{ 
  memset(self, 0, sizeof(struct clock_t));
  self->capacity = INIT_SIZE;
  self->length = 0;
  self->alarms = malloc(self->capacity * sizeof(struct alarm_t));
}

void push(struct clock_t* self, struct alarm_t alarm)
{
  // Need to reallocate memory if array has reached max capcaity. 
  if (self->length == self->capacity)
  {
    self->capacity *= 2;
    self->alarms = realloc(self->alarms, self->capacity * sizeof(struct alarm_t));
  }

  self->alarms[self->length++] = alarm;
}

void destroy(struct clock_t* self) 
{
  free(self->alarms);
  self->alarms = NULL;
  self->length = self->capacity = 0;
  free(self);
}

struct alarm_t remove_alarm(struct clock_t* self, int index) 
{
  struct alarm_t alarm = self->alarms[index]; // get alarm we want to remove


  // create temp array with same size as before
  struct alarm_t * updated_array = malloc(self->capacity * sizeof(struct alarm_t));

  // move the old array from start (clock->alamrs pointer starts at begining of array)
  // until it reaches the index.
  memmove(
    updated_array,
    self->alarms,
    (index+1)*sizeof(struct alarm_t)
  );

  // oppsite here, move last part of array into updated array.
  memmove(
    updated_array+index,
    self->alarms+(index+1),
    (self->capacity - index)*sizeof(struct alarm_t)
  );

  free(self->alarms);           // free old array.
  self->alarms = updated_array; // assign new array.
  self->length -= 1;
  kill(alarm.pid, SIGKILL);     // kill alarm process of the child.
  return alarm;
}

int find_index(struct clock_t *self, pid_t pid)
{
  for (int i = 0; i < self->length; i++) 
  {
    if (self->alarms[i].pid == pid)
      return i;
  }
  return NOT_FOUND;
}

int update_clock(struct clock_t *self) 
{
  int signal;
  pid_t pid = waitpid(-1, &signal, WNOHANG); // check terminated signal without blocking, avoids zombie processes.
  if (WIFEXITED(signal) && pid > 0) 
  {
    int index = find_index(self, pid);
    remove_alarm(self, index);
    return CHILD_TERMINATED;
  }
  return CHILD_NOT_TERMINATED;
}