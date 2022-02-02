#include <time.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "clock.h"
#include "menu.h"


int show_menu() {
  show_time();
  while(1) {
  
    printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit) \n");

    char input;
    scanf(" %c", &input);
    
    switch (input)
    {
      case 's':
        schedule_menu();
      case 'l':
        list_menu();
      case 'c':
        cancel_menu();
      case 'x':
        return 0;
      default: 
        printf("Unknown command! Please make sure to use one of the four listed commands \n\n");

    }
  }
}

void show_time() 
{
  struct tm* current_time;
  time_t rawtime;
  time ( &rawtime );
  current_time = localtime ( &rawtime );

  wchar_t buff[40];

  wcsftime(buff, sizeof buff, L"%F %T", current_time);

  printf("Welcome to the alarm clock cli! It is currently %ls\n", buff);
}


void schedule_menu()
{
  char input;
  scanf("%c", &input);
  schedule(input);

}

void list_menu() {
  list();
}

void cancel_menu() {
  cancel();
}