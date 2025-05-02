/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 04/14/25

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
  GPIOIEV_E &= ~(0x3); // Interrupts on falling ...
  GPIOIS_E &= ~(0x3); //                        ... edges
  GPIOIM_E |= 0x3; // enables interrupts for PE0 and PE1
  GPIOICR_E |= 0x3; // clears interrupt flags for PE0 and PE1
  
  EN0 |= 0x10; // Enable port E interrupt;
  
  /*
   GPIOPUR_E = 0x3; // Set PE0 and PE1 pull-up resistor
   
  */
}


unsigned long switch_input(int fnc) {
  static unsigned char pwr_prev = 0;
  static unsigned char ped_prev = 0;

  if (fnc == 0) { // power button
    if ((GPIODATA_E & 0x1) && !pwr_prev) {  // New press detected
      timer_sec_repeat(2, 0); // start 2s timer only once
      pwr_prev = 1;
    } else if (!(GPIODATA_E & 0x1)) { // button released
      pwr_prev = 0;
    }
    if ((GPIODATA_E & 0x1) && timer_expired(0)) {
      return 1;
    }
    return 0;
  }
  
  if (fnc == 1) { // pedestrian button
    if ((GPIODATA_E & 0x2) && !ped_prev) { // New press detected
      timer_sec_repeat(2, 0); // start 2s timer only once
      ped_prev = 1;
    } else if (!(GPIODATA_E & 0x2)) { // button released
      ped_prev = 0;
    }
    if ((GPIODATA_E & 0x2) && timer_expired(0)) {
      return 1;
    }
    return 0;
  }
}
