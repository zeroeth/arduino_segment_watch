#include "watch_time.h"
#include "sparkfun_segment.h"
#include "sleepy.h"
#include "the_button.h"


void setup() {                
  delay(5000); // Safety re-programming time :)

  input_floaties();
  segment_setup();
 
  setup_the_button();
  
  sleepy_time();
  have_a_heart();

  //EICRA = (1<<ISC01); //Interrupt on falling edge
  //EIMSK = (1<<INT0); //Enable INT0 interrupt
}


ISR(TIMER2_OVF_vect)
{
  increment_time();
}


void loop() {
  sei();
  sleep_mode();

  /*
  read_side_button(); 
  
  if(button_down) {
    display_active = true;
  } 
  else {
    display_active = false;
  }

  if(button_down && button_up_time == 0 && (millis() - button_down_time > 2000)) {
    //increment_time(20);
  }

  if(!button_down && button_down_time == 0 && (millis() - button_up_time > 2000)) {
    //display_active = false;
  }
*/
  if(display_active) {
    time_to_buffer();
    displayBuffer();
  }
}
