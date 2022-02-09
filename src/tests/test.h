#ifndef TEST_H
#define TEST_h

#define __POSIX_C_SOURCE
#define _POSIX_SOURCE
#define __USE_XOPEN
#define __USE_POSIX
#define __GNU_SOURCE

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define FAIL(_x, _e, _g) printf(ANSI_COLOR_RED "EXPECTED:  %d, GOT: %d %s \n", _x, _e, _g, ANSI_COLOR_RESET)
#define SUCCESS(_x) printf(ANSI_COLOR_GREEN "%s %s \n", _x, ANSI_COLOR_RESET)

#include "../clock/clock.h"
#include "../menu/menu.h"


#endif