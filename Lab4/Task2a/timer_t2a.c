/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/30/25

* The purpose of this file is to provide function declarations to allow use of onboard timers
* for lab4, providing the ability to initiate, start, and stop timers 0, 1 and 2.
*/

#include <stdint.h>
#include "lab4t2a.h"

void timerN_init(int n) { // int n specifies which timer to init
  if (n == 0) {
    volatile unsigned short delay = 0;
    RCGCTIMER |= 0x01; // activate timer 0
    
    delay++;
    delay++;
    
    GPTMCTL_0 &= ~(0x1); // disable timer
    GPTMCC_0 |= 0x1;
    // configures bit, timer mode, and count down/up
    GPTMCFG_0 = 0x0; // 32 bit mode
    GPTMTAMR_0 |= 0x2; // set mode = periodic
    GPTMTAMR_0 &= ~(0x10); // set to count down 
    GPTMTAILR_0 = 5 * 16000000; // set threshold
    
    //GPTMCTL_0 |= 0x1; // enable timer
    
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
    GPTMCC_1 |= 0x1;
    // configures bit, timer mode, and count down/up
    GPTMCFG_1 |= 0x0;
    GPTMTAMR_1 |= 0x1;
    GPTMTAMR_1 &= ~(0x10);
    GPTMTAILR_1 = 2 * 16000000;
    
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
    GPTMCC_2 |= 0x1;
    // configures bit, timer mode, and count down/up
    GPTMCFG_2 |= 0x0;
    GPTMTAMR_2 |= 0x1;
    GPTMTAMR_2 &= ~(0x10);
    GPTMTAILR_2 = 2 * 16000000;
    
    GPTMIMR_2 |= 0x1; // interrupt mask - enables interrupt for Timer 2
    EN0 |= 0x800000; // enable interrupt 23, timer2A interrupt
  }
  
}

// Turns on Timer N
void timer_on(int timerN) {
  if(timerN == 0) {
    GPTMCTL_0 |= 0x1;
  } else if(timerN == 1) {
    GPTMCTL_1 |= 0x1;
  } else if(timerN == 2) {
    GPTMCTL_2 |= 0x1;
  }
}

// Pauses / Turns of timer N
void timer_off(int timerN) {
  if (timerN == 0) {
    GPTMCTL_0 &= ~(0x1);
    GPTMTAILR_0 = 5 * 16000000; // set threshold
  } else if (timerN == 1) {
    GPTMCTL_1 &= ~(0x1);
    GPTMTAILR_1 = 2 * 16000000;
  } else if (timerN == 2) {
    GPTMCTL_2 &= ~(0x1);
    GPTMTAILR_2 = 2 * 16000000;
  }
}

// initializes timer start
void timer_sec_repeat(int n, int timerN) {
  if(timerN == 0) {     
    timer_off(0);  // Turns off timer
    GPTMCFG_0 = 0x0; // 32 bit mode
    GPTMTAILR_0 = n * 16000000; // sets durration
    GPTMICR_0 |= 0x1; // clears flag
    timer_on(0); // Start timer
  } else if (timerN == 1){
    timer_off(1);
    GPTMICR_1 |= 0x1;
    GPTMTAILR_1 = n * 16000000;
    timer_on(1);
  } else if (timerN == 2){
    timer_off(2);
    GPTMICR_2 |= 0x1;
    GPTMTAILR_2 = n * 16000000;
    timer_on(2);
  }
}

// polling to see if timer expired. 1 if timer expired, 0 otherwise
int timer_expired(int timerN) {
  if(timerN == 0) {  
    if(GPTMRIS_0 & 0x1) { //checks if timer has finish
      GPTMICR_0 = 0x1;  // clears and returns 1 if finished, 0 if otherwise
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