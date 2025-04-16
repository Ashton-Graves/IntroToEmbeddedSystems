#include <stdint.h>
#include "lab1.h"
int main(void)
{
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x1000 | 0x100; // Enable PortN and Port J GPIO
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   GPIODIR_J = ~0x3; // Set PJ0 and PJ1 to input w/o affecting others
   GPIODEN_J = 0x3; // Set PJ0 to digital port
   GPIOPUR_J = 0x3; // Set PJ0 and PJ1 pull-up resistor
   
   GPIODIR_N = 0x3; // Set PN1 & PN0 to output
   GPIODEN_N = 0x3; // Set PN1 & PN0 to digital port
   
   while (1) {
     
     if ((GPIODATA_J & 0x03) == 0x0) { 
        GPIODATA_N = 0x3;  // Turn on both LEDs (PN1 and PN0)
     }
     // check port + mask when SW1 is pressed
     else if((GPIODATA_J & 0x03) == 0x2) { 
        GPIODATA_N = 0x2;
     }
     
     // check port + mask when SW2 is pressed
     else if((GPIODATA_J & 0x03) == 0x1) {
        GPIODATA_N = 0x1;
     }
     else {
        GPIODATA_N = 0x0;
     }
   }
   return 0;
}