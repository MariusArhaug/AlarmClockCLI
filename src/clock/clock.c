#include "clock.h"
#include <stdlib.h>

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