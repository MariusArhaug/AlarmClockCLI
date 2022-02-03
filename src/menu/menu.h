#ifndef MENU_H
#define MENU_H

#include "../clock/clock.h"
#include "time.h"

#define _POSIX_SOURCE

int menu_loop(alarm_clock_t*);

typedef struct tm tm_t;

static void show_time(tm_t*);
static void schedule_menu(alarm_clock_t*, tm_t*);
static void list_menu(alarm_clock_t*);
static void cancel_menu(alarm_clock_t*);
static tm_t* get_current_time();

#endif