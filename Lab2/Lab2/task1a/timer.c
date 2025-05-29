/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25

* The purpose of this file is to provide function declarations to allow use of onboard timers
* for lab2, providing the ability to initiate, start, and stop timer 0
*/

#include <stdint.h>
#include "lab2t1.h"

// Initializes timer 0
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

// Initiallizes timer 1
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

void timer_on(int timerN) {
  if(timerN == 0) {
    GPTMCTL_0 |= 0x1; // Sets timer control bit to 1/on
  } else if (timerN == 1) {
    GPTMCTL_1 |= 0x1;
  }
}

void timer_off(int timerN) {
  if(timerN == 0) {
    GPTMCTL_0 &= ~(0x1);
  } else if (timerN == 1){
    GPTMCTL_1 &= ~(0x1);
  }
}

// activates timer for n seconds, clearing flags and
// restarting everytime reaching 0.
void timer_n_secs(int n) {
  timer_off(0);
  GPTMTAILR_0 = n * 16000000;
  GPTMICR_0 = 0x1; // clears the flag 
  timer_on(0);
  
  while((GPTMRIS_0 & 0x1) == 0); // checks for when the timer runs out. GPTMRIS is 0 until the timer runs out, then 1.
  
  GPTMICR_0 = 0x1; // clears the flag
  
}

// Sets timer for n seconds then activates it
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
  }
}

// checks if timer count has expired
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
    
  }
}
