#include <stdint.h>
# include "lab1.h"

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
  if(fnc == 0) {  
    return (GPIODATA_E & 0x1); // 0x1 (pressed) or 0 (not pressed)
  }
  if(fnc == 1) {
    return (GPIODATA_E & 0x2); // 0x2 (pressed) or 0 (not pressed)
  }
}
