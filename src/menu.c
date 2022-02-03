#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
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
        cancel_menu();
        break;
      case 'x':
        return 0;
        break;
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

tm_t* get_current_time()
{
  tm_t* current_time = malloc(sizeof(struct tm));
  time_t rawtime;
  time (&rawtime);
  current_time = localtime( &rawtime );
  return current_time;
}

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
  
  push(clock, alarm);

  int difference = difftime(mktime(current_time), alarm.time);
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

void cancel_menu() {
  
}