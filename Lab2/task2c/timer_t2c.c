#include <stdint.h>
#include "lab2t2c.h"





void timer0_init(void) {
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x01; // activate timer 0
  
  delay++;
  delay++;
  
  GPTMCTL_0 &= ~(0x1); // disable timer
  
  // configures bit, timer mode, and count down/up
  GPTMCFG_0 |= 0x0; // 32 bit mode
  GPTMTAMR_0 |= 0x2; // set mode = periodic
  GPTMTAMR_0 &= ~(0x10); // set to count down 
  GPTMTAILR_0 = 16000000; // set threshold
  
  GPTMCTL_0 |= 0x1; // enable timer
}

void timer1_init(void) {
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x02; // activate timer 1
  
  delay++;
  delay++;
  
  //disables timer
  GPTMCTL_1 &= ~(0x1);
  // configures bit, timer mode, and count down/up
  GPTMCFG_1 |= 0x0;
  GPTMTAMR_1 |= 0x2;
  GPTMTAMR_1 &= ~(0x10);
  GPTMTAILR_1 = 16000000;
  
  //enables timer
  GPTMCTL_1 |= 0x1;
}












void timer_init(void) {
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x01; // activate timer 0
  
  delay++;
  delay++;
  
  //disables timer
  GPTMCTL_0 &= ~(0x1);
  // configures bit, timer mode, and count down/up
  GPTMCFG_0 |= 0x0;
  GPTMTAMR_0 |= 0x2;
  GPTMTAMR_0 &= ~(0x10);
  GPTMTAILR_0 = 16000000;
  GPTMICR_0 = 0x1; // clear pending interrupt timer 0A timeout flag

  GPTMIMR_0 |= 0x1; // interrupt mask - enables interrupt for Timer 0
  EN0 |= 0x80000; // enable interrupt 19, the timer0A interrupt

  //enables timer
  GPTMCTL_0 |= 0x1;
}

void timer_on(void) {
  GPTMCTL_0 |= 0x1;
}

void timer_off(void) {
  GPTMCTL_0 &= ~(0x1);
}

// initializes timer
void timer_sec_repeat(int n) {
  timer_off();
  GPTMTAILR_0 = n * 16000000;
  GPTMICR_0 = 0x1;
  timer_on();
}

// polling to see if timer expired. 1 if timer expired, 0 otherwise
int timer_expired(void) {
  if(GPTMRIS_0 & 0x1) {
    GPTMICR_0 = 0x1;
    return 1;
  }
  return 0;
}