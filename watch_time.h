#ifndef _watch_time
#define _watch_time

#include <WProgram.h>

void time_to_buffer();
void increment_time(int by_sec = 1, int by_min = 1, int by_hour = 1);

extern int time_array[4];
extern boolean second_mark;
extern int hours;
extern int minutes;
extern int seconds;

#endif 
