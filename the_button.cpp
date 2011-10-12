#include "the_button.h"

int button_down_time;
int button_up_time;
boolean button_down;
int last_button_value;

void setup_the_button() {
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);       // turn on pullup resistors

  button_down_time = millis();
  button_up_time = millis();
  button_down = false;
};

void read_side_button() {
  int button_value = digitalRead(2);

  boolean value_changed = false;

  if(last_button_value != button_value) {
    value_changed = true;
  }

  if(button_value == LOW) {
    if(value_changed) {
      button_down_time = millis();
      button_down = true;
      button_up_time = 0;
    }
  }
  else {
    if(value_changed) {
      button_up_time = millis();
      button_down = false; 
      button_down_time = 0;
    }
  }

  last_button_value = button_value;
}
