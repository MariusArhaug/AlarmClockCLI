#include "alarm.h"
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../menu/menu.h"
#include <stdio.h>


void alarm_init(struct alarm_t* self)
{
  memset(self, 0, sizeof(struct alarm_t));
  self->ringtone = malloc(MAX_INPUT_SIZE * sizeof(char));
}

void alarm_destroy(struct alarm_t *self)
{
  self->pid = -1;
  free((char*) self->ringtone); // this might not be the total correct way to free
  free(self);
  self = NULL;
}

void set_alarm(struct alarm_t *self, time_t time, int duration, const char* ringetone) 
{
  self->time = time;
  self->ringtone = ringetone;
  
  pid_t pid = fork();
  if (pid == 0) {
    /* child process */
    sleep(duration);
    char path[9] = "./audio/";
    strcat(path, self->ringtone);
    execl("/bin/mpg123", "/bin/mpg123", "-q" , path, NULL); 
    exit(EXIT_SUCCESS);
  }
  self->pid = pid;
}
