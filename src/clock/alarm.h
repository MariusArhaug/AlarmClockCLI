#ifndef ALARM_H
#define ALARM_H

#define _POSIX_SOURCE
#define __USE_XOPEN
#define __USE_POSIX
#define __GNU_SOURCE
#include <time.h>
#include <sys/types.h>
#include <string.h>
 
#define ALARMS (char const*[]){\
    "JusticeAlarm.mp3",\
    "MarioGalaxyAlarm.mp3",\
    "MarioElevatormusic.mp3",\
    "WiiSportsTitle.mp3"\
  }

struct alarm_t {
  time_t time;
  pid_t pid;
  char* ringtone;
};

/**
 * @brief init alamr at given time, make process sleep for a duration and ring with ringtone,  
 * 
 */
void alarm_init(struct alarm_t*); 


/**
 *  
 * @brief function to set alarm
 * 
 * @param time to set the alarm
 * @param duration of ringtone
 * @param char pointer to an array of set ringtones
 * 
*/
void set_alarm(struct alarm_t*, time_t, int, char*);

#endif