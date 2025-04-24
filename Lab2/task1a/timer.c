#include <stdint.h>
#include "lab2t1.h"

void timer_init(void) {
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x01; // activate clock for Port E
  
  delay++;
  delay++;
  
  //disables timer
  GPTMCTL_0 &= ~(0x1);
  // configures bit, timer mode, and count down/up
  GPTMCFG_0 |= 0x0;
  GPTMTAMR_0 |= 0x2;
  GPTMTAMR_0 &= ~(0x10);
  GPTMTAILR_0 = 16000000;
  
  //enables timer
  GPTMCTL_0 |= 0x1;
}

void timer_on(void) {
  GPTMCTL_0 |= 0x1;
}

void timer_off(void) {
  GPTMCTL_0 &= ~(0x1);
}

// activates timer for n seconds, clearing flags and
// restarting everytime reaching 0.
void timer_n_secs(int n) {
  GPTMTAILR_0 = n * 16000000;
  GPTMICR_0 = 0x1;
  timer_on();
  
  while((GPTMRIS_0 & 0x1) == 0);
  
  GPTMICR_0 = 0x1;
  
}