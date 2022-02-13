
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "menu/menu.h"
#include "clock/clock.h"


void init() {
  struct clock_t* clock = malloc(sizeof(struct clock_t));
  clock_init(clock);
  menu_loop(clock);
  clock_destroy(clock);
}

int main(int argc, char* argv[]) {
  init();
}