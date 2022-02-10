#include "alarm.h"
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void alarm_init(struct alarm_t *self, time_t time, int difference) {
  memset(self, 0, sizeof(struct alarm_t));
  self->time = time;
  pid_t pid = fork();
  
  if (pid == 0) {
    /* child process */
    sleep(difference);
    execl("/bin/mpg123", "/bin/mpg123", "-q" ,"./audio/alarm.mp3", NULL); 
    exit(EXIT_SUCCESS);
  }
  self->pid = pid;
}