#include "../clock/clock.h"
#include "menu.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int menu_loop(alarm_clock_t *clock) {
  struct tm* current_time = get_current_time();
  show_time(current_time);

  while(1) {
    if (update_clock(clock)) {
      continue;
    }
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

struct tm* get_current_time()
{
  struct tm* current_time = malloc(sizeof(struct tm));
  time_t rawtime;
  time (&rawtime);
  current_time = localtime( &rawtime );
  return current_time;
}

void schedule_menu(alarm_clock_t* clock, struct tm* current_time)
{
  char input[MAX_INPUT_SIZE];
  printf("Schedule alarm at which data and time? ");
  scanf(" %255[^\n]", input); 

  struct tm tm;
  strptime(input, "%F %T", &tm); 
  
  tm.tm_hour -= 1;
  time_t time = timegm(&tm); 

  int difference = difftime(mktime(current_time), time) * (-1);

  create_alarm(clock, time, difference);
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
      wchar_t buff[MAX_INPUT_SIZE];

      wcsftime(buff, sizeof buff, L"%F %T", localtime(&(clock->alarms[i].time)));

      printf("Alarm %d at %ls\n", i+1, buff);

    }
  }
}

void cancel_menu(alarm_clock_t* clock) {
  if (clock->length == 0) {
    printf("You have not set any alarms yet! \n");
    printf("You cannot cancel any alarms! \n");
  } else {
    while (1) {
      int index;
      char term;
      printf("Cancel which alarm? ");
      if(
        scanf(" %d%c", &index, &term) != 2 
        || term != '\n' 
        || index <= 0 
        || index >= clock->length+1
      ) {
        printf("Not valid number, try again \n");
        continue;
      }
      // alarm_t alarm = clock->alarms[index-1];
      alarm_t alarm = remove_alarm(clock, index-1);
      printf("Alarm %d with pid: %d canceled\n", index, alarm.pid);
      break;
    }
  }
}