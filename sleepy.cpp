#include "sleepy.h"


void input_floaties() {
  // disable internal resistors to save power during sleep
  for(int x = 1 ; x < 18 ; x++){
    pinMode(x, INPUT);
    digitalWrite(x, LOW);
  }
}

void sleepy_time() {
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sleep_enable();

  // Disable analog systems
  ADCSRA &= ~(1<<ADEN); 
  ACSR = (1<<ACD); 
  DIDR0 = (1<<ADC0D)|(1<<ADC1D)|(1<<ADC2D)|(1<<ADC3D)|(1<<ADC4D)|(1<<ADC5D);
  DIDR1 = (1<<AIN1D)|(1<<AIN0D);

  // Disable communications and unused timer
  power_twi_disable();
  power_spi_disable();
  power_usart0_disable();
  power_timer1_disable();
}


void have_a_heart() {
  // Prescale 128 for 1Hz interrupt.
  TCCR2A = 0x00;
  TCCR2B = (1<<CS22)|(0<<CS21)|(1<<CS20);

  // Timer 2 interrupt using external crystal
  ASSR = (1<<AS2); 
  TIMSK2 = (1<<TOIE2);

  sei();
}
