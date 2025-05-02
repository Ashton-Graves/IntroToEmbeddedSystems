#include <stdint.h>
#include "lab2t2c.h"

void timerN_init(int n) { // int n specifies which timer to init
  if (n == 0) {
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
    
    GPTMIMR_0 |= 0x1; // interrupt mask - enables interrupt for Timer 0
    EN0 |= 0x80000; // enable interrupt 19, the timer0A interrupt
  }
  
  else if (n == 1) {
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
    
    GPTMIMR_1 |= 0x1; // interrupt mask - enables interrupt for Timer 1
    EN0 |= 0x200000; // enable interrupt 21, timer1A interrupt
  }
  
  else if (n == 2) {
    volatile unsigned short delay = 0;
    RCGCTIMER |= 0x04; // activate timer 2
    
    delay++;
    delay++;
    
    //disables timer
    GPTMCTL_2 &= ~(0x1);
    // configures bit, timer mode, and count down/up
    GPTMCFG_2 |= 0x0;
    GPTMTAMR_2 |= 0x2;
    GPTMTAMR_2 &= ~(0x10);
    GPTMTAILR_2 = 16000000;
    
    //enables timer
    GPTMCTL_2 |= 0x1;
    
    GPTMIMR_2 |= 0x1; // interrupt mask - enables interrupt for Timer 2
    EN0 |= 0x800000; // enable interrupt 23, timer2A interrupt
  }
  
  /*
  else if (n == 2) {
    volatile unsigned short delay = 0;
    RCGCTIMER |= 0x04; // activate timer 2
    
    delay++;
    delay++;
    
    //disables timer
    GPTMCTL_2 &= ~(0x1);
    // configures bit, timer mode, and count down/up
    GPTMCFG_2 |= 0x0;
    GPTMTAMR_2 |= 0x2;
    GPTMTAMR_2 &= ~(0x10);
    GPTMTAILR_2 = 16000000;
    
    //enables timer
    GPTMCTL_2 |= 0x1;
  }
  */
}
/*
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
*/

void timer_on(int timerN) {
  if(timerN == 0) {
    GPTMCTL_0 |= 0x1;
  } else if(timerN == 1) {
    GPTMCTL_1 |= 0x1;
  } else if(timerN == 2) {
    GPTMCTL_2 |= 0x1;
  }
}

void timer_off(int timerN) {
  if (timerN == 0) {
    GPTMCTL_0 &= ~(0x1);
  } else if (timerN == 1) {
    GPTMCTL_1 &= ~(0x1);
  } else if (timerN == 2) {
    GPTMCTL_2 &= ~(0x1);
  }
}

// initializes timer
void timer_sec_repeat(int n, int timerN) {
  if(timerN == 0) {
    timer_off(0);
    GPTMTAILR_0 = n * 16000000;
    GPTMICR_0 = 0x1;
    timer_on(0);
  } else if (timerN == 1){
    timer_off(1);
    GPTMTAILR_1 = n * 16000000;
    GPTMICR_1 = 0x1;
    timer_on(1);
  } else if (timerN == 2){
    timer_off(2);
    GPTMTAILR_2 = n * 16000000;
    GPTMICR_2 = 0x1;
    timer_on(2);
  }
}

// polling to see if timer expired. 1 if timer expired, 0 otherwise
int timer_expired(int timerN) {
  if(timerN == 0) {  
    if(GPTMRIS_0 & 0x1) {
      GPTMICR_0 = 0x1;
      return 1;
    }
    return 0;
  } else if (timerN == 1) {
    if(GPTMRIS_1 & 0x1) {
      GPTMICR_1 = 0x1;
      return 1;
    }
    return 0;
  } else if (timerN == 2) {
    if(GPTMRIS_2 & 0x1) {
      GPTMICR_2 = 0x1;
      return 1;
    }
    return 0; 
  }  
}