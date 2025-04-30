/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 04/30/25

* This file builds the system specified in lab 2 task2a. The 4 onboard LEDs are turned on one at a time in sequence.
*/

#include <stdint.h>
#include "lab2t1.h"
int main(void)
{
   volatile unsigned short delay = 0;
   
   // clock gating
   RCGCGPIO |= 0x1000 | 0x20; // Enable PortN & PortF GPIO clock gating
   timer_init();
   
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


void Timer0A_Handler(void) {
  GPTMICR(0) |= TATOI; // clear flag that caused interrupt
  GPTMICR_0 = 0x1; // clears the flag
}
