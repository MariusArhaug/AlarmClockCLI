#ifndef MENU_H
#define MENU_H

#include "../clock/clock.h"
#include "time.h"


int menu_loop(alarm_clock_t*);


static void show_time(struct tm*);
static void schedule_menu(alarm_clock_t*, struct tm*);
static void list_menu(alarm_clock_t*);
static void cancel_menu(alarm_clock_t*);
static struct tm* get_current_time();

#endif