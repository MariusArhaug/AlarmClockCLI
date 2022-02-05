#ifndef MENU_H
#define MENU_H

#define _POSIX_C_SOURCE
#include <time.h>
#include "../clock/clock.h"


int menu_loop(alarm_clock_t*);

void show_time(struct tm*);
void schedule_menu(alarm_clock_t*, struct tm*);
void list_menu(alarm_clock_t*);
void cancel_menu(alarm_clock_t*);
struct tm* get_current_time();

#endif