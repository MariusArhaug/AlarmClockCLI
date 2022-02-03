#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "clock.h"
#include "menu.h"

#define MAX_INPUT_SIZE 256

int menu_loop(alarm_clock_t *clock) {
  struct tm* current_time = get_current_time();
  show_time(current_time);

  while(1) {
  
    printf("\nPlease enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit) \n> ");

    char input;
    scanf(" %c", &input);

    switch (input)
    {
      case 's':
        schedule_menu(clock, current_time);
        break;
      case 'l':
        list_menu(clock);
        break;
      case 'c':
        cancel_menu(clock);
        break;
      case 'x':
        printf("Goodbye! \n");
        return 0;
      default: 
        printf("Unknown command! Please make sure to use one of the four listed commands \n\n");

    }
  }
}

void show_time(struct tm * time) 
{


  wchar_t buff[40];

  wcsftime(buff, sizeof buff, L"%F %T", time);

  printf("Welcome to the alarm clock cli! It is currently %ls\n", buff);
}

/**
 * @brief Get the current time object
 * 
 * @return tm_t* time object
 */
tm_t* get_current_time()
{
  tm_t* current_time = malloc(sizeof(struct tm));
  time_t rawtime;
  time (&rawtime);
  current_time = localtime( &rawtime );
  return current_time;
}

/**
 * @brief Schedule alarm clock. Prompt user to input in the following format "%Y-%m-%d %H:%M:%S"
 * 
 * After setting alarm a child process waits until the alarm reaches its deadline. 
 * Then it will either print "RING" or make a noise
 * 
 * @param clock take in clock struct pointer
 * @param current_time current_time when program started
 */
void schedule_menu(alarm_clock_t* clock, tm_t* current_time)
{
  char input[MAX_INPUT_SIZE];
  printf("Schedule alarm at which data and time? ");
  scanf(" %255[^\n]", input); // TODO make fgets 
  
  printf("input: %s \n", input);

  alarm_t alarm;
  struct tm tm;

  strptime(input, "%F %T", &tm);
  alarm.time = mktime(&tm); 
  

  int difference = difftime(mktime(current_time), alarm.time) * (-1);
  pid_t pid = fork();  

  if (pid == 0) {
    /* child process */

    sleep((int) difference);
    printf("RING! \n");
    exit(EXIT_SUCCESS);
  }

  alarm.pid = pid;
  push(clock, alarm);
  
  printf("Scheduling alarm in %d seconds \n", difference);

}

void list_menu(alarm_clock_t *clock) {
  if (clock->length == 0) 
  {
    printf("You have not set any alarms yet!\n");
    
  } else
  {
    for (int i = 0; i < clock->length; i++) 
    {
      wchar_t buff[40];

      wcsftime(buff, sizeof buff, L"%F %T", localtime(&(clock->alarms[i].time)));

      printf("Alarm %d at %ls\n", i+1, buff);

    }
  }
}

void cancel_menu(alarm_clock_t* clock) {
  while (1) {
    int index;
    char term;
    if(
      scanf("%d%c", &index, &term) != 2 
      || term != '\n' 
      || index <= 0 
      || index > clock->length+1
    ) {
      printf("Not valid number, try again \n");
      continue;
    }
    alarm_t alarm = clock->alarms[index-1];
    printf("Alarm %d with pid: %d canceled\n", index, alarm.pid);
    kill(alarm.pid, SIGKILL);
  }
}