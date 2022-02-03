
#include "menu.h"
#include "clock.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  alarm_clock_t* clock = initialize();
  menu_loop(clock);
  free_clock(clock);
  return 0;
}