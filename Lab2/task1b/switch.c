/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 04/14/25

* The purpose of this file is to define functions to properly initialize certain registers on the TIVA board to enable system integration
  with external pushbuttons, and to get the signal from one of the two pushbutton inputs for lab 1.
*/

# include <stdint.h>
# include "lab2t1.h"
# include "timer.h"

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
}
unsigned long switch_input(int fnc) {
  // power button
  if(fnc == 0) {
    timer_init();
    if(GPIODATA_E & 0x1) {
      timer_n_secs(2);
      if(GPIODATA_E & 0x1) {
        return 1; 
      } else {
        return 0; 
      }
  }
  
  // pedestrian button
  if(fnc == 1) {
    timer_init();
    if(GPIODATA_E & 0x2) {  // 0x2 (pressed) or 0 (not pressed)
      timer_n_secs(2);
      if(GPIODATA_E & 0x2) {
        return 1; 
      } else {
        return 0; 
      }
    }
  }
}
