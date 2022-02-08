#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "clock.h"

#define FAKE_SIGNAL 0
#define NOT_FOUND -1

/**
 * @brief initialize clock structure
 * 
 * @return alarm_clock_t* pointer to clock structure 
 */
alarm_clock_t* initialize()
{
  
  alarm_clock_t* clock = malloc(sizeof(alarm_clock_t));

  clock->capacity = INIT_SIZE;
  clock->length = 0;
  clock->alarms = malloc(clock->capacity * sizeof(alarm_t));
  return clock;
}

/**
 * @brief Push alarm to clock  
 * 
 * @param clock clock to add alarm to 
 * @param alarm alarm to be added.
 */
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

/**
 * @brief free clock struct from memory 
 * Frees first its alarms, then sets is length/capacity to 0 
 * finally frees the pointer.
 * @param clock clock to be freed from memory.
 */
void free_clock(alarm_clock_t* clock) 
{
  free(clock->alarms);
  clock->alarms = NULL;
  clock->length = clock->capacity = 0;
  free(clock);
}

/**
 * @brief Create a alarm to be added to clock
 * 
 * @param clock clock we want to add a
 * @param time 
 * @param difference 
 * @return alarm_t 
 */
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

/**
 * @brief removes alarm from clock at given index
 * 
 * @param clock clock to remove alarm from
 * @param index index of the given alarm.
 * @return alarm_t 
 */
alarm_t remove_alarm(alarm_clock_t* clock, int index) 
{
  if(index >= 0){
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
    printf("%s\n", "hi");
    printf("%d\n", clock->length);
    return alarm;
  }
  printf("%s\n", "hello");
  alarm_t alarm = clock->alarms[0];
  return alarm;
}

/**
 * @brief find index of alarm given its pid. 
 * 
 * @param clock clock to search through 
 * @param pid pid for alarm we want to find
 * @return int index of found alarm or NOT_FOUND (-1).
 */
int find_index(alarm_clock_t * clock, pid_t pid)
{
  for (int i = 0; i < clock->length; i++) 
  {
    if (clock->alarms[i].pid == pid)
      return i;
  }
  return NOT_FOUND;
}

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