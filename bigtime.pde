#include "watch_time.h"
#include "sparkfun_segment.h"

boolean display_active = true;
int button_down_time;
int button_up_time;
boolean button_down = false;
int last_button_value;


void read_side_button() {
  int button_value = digitalRead(2);

  boolean value_changed = false;

  if(last_button_value != button_value) {
    value_changed = true;
  }

  if(button_value == LOW) {
    if(value_changed) {
      button_down_time = millis();
    }
    button_down = true;
  }
  else {
    if(value_changed) {
      button_up_time = millis();
    }
    button_down = false; 
  }

  last_button_value = button_value;
}


void setup() {                
  delay(5000);
  segment_setup();
  
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);       // turn on pullup resistors
  button_down_time = millis();
  button_up_time = millis();
  button_down = false;
  display_active = true;
  
  ASSR = 0x20;    //enable timer2 async mode with an external crystal
  delay(250);

  TCCR2B = 0x04;  //set the prescaler to 128: 32.768kHz / 128 = 1Hz overflow
  TIFR2 = 0x1;    //reset timer2 overflow interrupt flag
  TIMSK2 = 0x01;  //enable interrupt on overflow

  //SMCR = 0x03;    //use power-save mode when we sleep
  sei();          //enable all interrupts
}


ISR(TIMER2_OVF_vect)    //Timer 2 overflow interrupt handler
{
    //This executes every second.  Update real-time clocks,
    //  listen for/broadcast wireless packets, etc.
  increment_time();
}


void loop() {
  // TODO add real sleep routine
  
  read_side_button(); 
  
  if(button_down) {
    display_active = true;
  }

  if(button_down && millis() - button_down_time > 2000) {
    increment_time(20);
  }

  if(!button_down && millis() - button_up_time > 2000) {
    display_active = false;
  }

  if(display_active) {
    time_to_buffer();
    displayBuffer();
  }
}
