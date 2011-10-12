#ifndef _the_button
#define _the_button

#include <WProgram.h>

// TODO make these class/namespaced based
extern int button_down_time;
extern int button_up_time;
extern boolean button_down;
extern int last_button_value;

void setup_the_button();
void read_side_button();

#endif
