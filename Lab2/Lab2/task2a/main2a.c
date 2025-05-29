/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 04/30/25

* This file builds the system specified in lab 2 task2a. The 4 onboard LEDs are turned on one at a time in sequence.
*/

#include <stdint.h>
#include "lab2t2a.h"
#include "timer_t2a.h"

int main(void)
{
   volatile unsigned short delay = 0;
   // clock gating
   RCGCGPIO = 0x1000 | 0x20; // Enable PortN & PortF GPIO clock gating
   timer_init();
   
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   // conigure leds - condider making this a function
   GPIODIR_F = 0x11; // Set PF0 and PF4 to output
   GPIODEN_F = 0x11; // Set PF0 and PF4 to digital port
   GPIODATA_F = 0x0; // initialize port F to off
   
   GPIODIR_N = 0x3; // Set PN0 and PN1 to output
   GPIODEN_N = 0x3; // Set PN0 and PN1 to digital port
   GPIODATA_N = 0x0; // initialize port N to off
   
   while (1) {
   }
  return 0;
}

#pragma call_graph_root = "interrupt"
__weak void Timer0A_Handler(void) {
  GPTMICR_0 = 0x1; // clears the flag
    
  if ((GPIODATA_F == 0x0) && (GPIODATA_N == 0x0)) {
    GPIODATA_F = 0x1; // Set PF0 to 1
  }
  
  else if (GPIODATA_F == 0x1) {
    GPIODATA_F = 0x10; // set PF4 to 1, PF0 to 0 
  }
  
  else if (GPIODATA_F == 0x10) {
    GPIODATA_F = 0x0; // set PF4 to 0
    GPIODATA_N = 0x1; // set PN0 to 1
  }
  
  else if (GPIODATA_N == 0x1) {
    GPIODATA_N = 0x2; // Set PN1 to 1, PN0 to 0
  }
  
  else if (GPIODATA_N == 0x2) {
    GPIODATA_N = 0x0; // Set PN1 to 0 
  }
}
