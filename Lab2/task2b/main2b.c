/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 04/30/25

* This file builds the system specified in lab 2 task2a. The 4 onboard LEDs are turned on one at a time in sequence.
*/

#include <stdint.h>
#include "lab2t2b.h"
#include "timer_t2b.h"

int main(void)
{
   volatile unsigned short delay = 0;
   // clock gating
   RCGCGPIO = 0x1000 | 0x20 | 0x100; // Enable PortN, PortF & Port J GPIO clock gating
   timer_init();
   
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   // configure leds - condider making this a function
   GPIODIR_N = 0x3; // Set PN0 and PN1 to output
   GPIODEN_N = 0x3; // Set PN0 and PN1 to digital port
   GPIODATA_N = 0x0; // initialize port N to off

   GPIODIR_J = ~(0x3); // Set PJ0 and PJ1 to input w/o affecting others
   GPIODEN_J = 0x3; // Set PJ0 to digital port
   GPIOPUR_J = 0x3; // Set PJ0 and PJ1 pull-up resistor
   GPIOIEV_J &= ~(0x3); // Interrupts on falling ...
   GPIOIS_J &= ~(0x3); //                        ... edges
   GPIOIM_J |= 0x3; // enables interrupts for PJ0 and PJ1
   GPIOICR_J |= 0x3; // clears interrupt flags for PJ0 and PJ1
   EN1 |= 0x80000; // enable interrupt 51 for port J
    
   while (1) {
   }
  return 0;
}

#pragma call_graph_root = "interrupt"
__weak void Timer0A_Handler(void) {
  GPTMICR_0 = 0x1; // clears the flag
  
  if (GPIODATA_N == 0x2) {
    GPIODATA_N = 0x0; // Set PN1 to 1
  }
  
  else if (GPIODATA_N == 0x0) {
    GPIODATA_N = 0x2; // Set PN1 to 1
  }
}

#pragma call_graph_root = "interrupt"
__weak void SW_Handler(void) {

  // check port + mask when SW1 (PJ0) is pressed
  if((GPIODATA_J & 0x03) == 0x2) { // active low LEDs
    GPIOICR_J = 0x1; // clears the flag
    GPTMCTL_0 &= ~(0x1); // turns off the timer (stopping the blinking)
    GPIODATA_N |= 0x1; // turns on LED2
  }
   
  // check port + mask when SW2 (PJ1) is pressed
  else if((GPIODATA_J & 0x03) == 0x1) { 
    GPIOICR_J = 0x2; // clears the flag
    GPTMCTL_0 |= 0x1; // enables timer, resuming blinking
    GPIODATA_N &= ~(0x1); // turns off LED2
  }
}