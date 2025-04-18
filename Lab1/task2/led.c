# include <stdint.h>
# include "lab1.h"

void LED_init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10; // activate clock for Port E
  
  delay++;
  delay++;
  
  GPIOAMSEL_E &= ~0x2C; // disable analog function of PE2, PE3, PE5
  GPIOAFSEL_E &= ~0x2C; // set PC4 regular port function
  GPIODIR_E |= 0x2C; // set PE2, PE3, PE5 to output
  GPIODEN_E |= 0x2C; // enable digital output on PE2, PE3, PE5

}

// turn on LED connected to Port E
void LED_on(int color) {
  GPIODATA_E &= ~(0x04 | 0x08 | 0x20);
  
  if(color == 1) { // if color is 1, turn on red LED (PE2)
    GPIODATA_E |= 0x04;
  } else if(color == 2) { // if color is 2, turn on yellow LED (PE3)
    GPIODATA_E |= 0x08;
  } else if (color == 3) { // if color is 3, turn on green LED (PE5)
    GPIODATA_E |= 0x20;
  }
  
}

// turn off all LEDs connected to Port E
void LED_off() {
  GPIODATA_E &= ~(0x04 | 0x08 | 0x20);

}