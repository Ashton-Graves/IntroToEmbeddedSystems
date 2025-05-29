/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25

* The purpose of this file is to define functions to properly initialize certain registers on the TIVA board to enable system integration
  with external pushbuttons, and to get the signal from one of the two pushbutton inputs for lab 1.
*/

# include <stdint.h>
# include "lab2t2c.h"
# include "timer_t2c.h"

void extern_switch_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10; // Enable Port E Gating Clock
  delay++;
  delay++;
  
  GPIOAMSEL_E &= ~0x3; // Disable PE0 & PE1 analog function
  GPIOAFSEL_E &= ~0x3; // Select PE0 & PE1 regular port function
  GPIODIR_E &= ~0x3; // Set PE0 & PE1 to input direction
  GPIODEN_E |= 0x3; // Enable PE0 & PE1 digital function
  GPIOIBE_E |= 0x3; // both edges trigger an interrupt
  GPIOIS_E &= ~(0x3); // Interrupts on edges
  GPIOIM_E |= 0x3; // enables interrupts for PE0 and PE1
  GPIOICR_E |= 0x3; // clears interrupt flags for PE0 and PE1
  
  EN0 |= 0x10; // Enable port E interrupt;
  
}

// Reads input from the switch port E
unsigned long switch_input(int fnc) {  
  if(fnc == 0) {
    if(GPIODATA_E & 0x01) {
      return 1;
    } 
  }
  
  if(fnc == 1) {
    if(GPIODATA_E & 0x02) {
      return 1; 
    }
  }
}
