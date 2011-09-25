#include "watch_time.h"

int time_array[4] = {5,5,5,5};
boolean second_mark = HIGH;
int hours = 11;
int minutes = 30;
int seconds = 0;


void time_to_buffer() {
  time_array[0] =   hours / 10;
  time_array[1] =   hours % 10;
  time_array[2] = minutes / 10;
  time_array[3] = minutes % 10;
  if(seconds % 2 == 0) {
    second_mark = HIGH;
  }
  else {
    second_mark = LOW; 
  }
}

/* defaults = 1 for all 3 arguments */
void increment_time(int by_sec, int by_min, int by_hour) {
  seconds += by_sec;
  if(seconds > 59) {
    seconds = 0;
    
    minutes += by_min;
    if(minutes > 59) {
      minutes = 0;
      
      hours += by_hour;
      if(hours > 12) {
        hours = 1;
      }
    }
  } 
}
