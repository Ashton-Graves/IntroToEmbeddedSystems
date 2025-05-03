/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 04/29/25

* This file builds the system specified in lab 1 task1a. The 4 onboard LEDs are turned on one at a time in sequence.
*/

#include <stdint.h>
#include "lab2t1.h"
int main(void)
{
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x1000 | 0x20; // Enable PortN& PortF GPIO
   timer0_init();
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   GPIODIR_F = 0x11; // Set PF0 and PF4 to output
   GPIODEN_F = 0x11; // Set PF0 and PF4 to digital port
   GPIODATA_F = 0x0; 
   
   GPIODIR_N = 0x3; // Set PN0 and PN1 to output
   GPIODEN_N = 0x3; // Set PN0 and PN1 to digital port
   GPIODATA_N = 0x0; // Set PN1 to 0
   
   while (1) {
     // Set PF0 to on/1 then off
     
     GPIODATA_F = 0x1; // Set PF0 to 1
     
     timer_n_secs(1); // delay
     
     GPIODATA_F = 0x10; // set PF4 to 1, PF0 to 0
     
     timer_n_secs(1); // delay
        
     GPIODATA_F = 0x0; // set PF4 to 0
     GPIODATA_N = 0x1; // set PN0 to 1
         
     timer_n_secs(1); // delay
     
     GPIODATA_N = 0x2; // Set PN1 to 1, PN0 to 0
     
     timer_n_secs(1); // delay
    
     GPIODATA_N = 0x0; // Set PN1 to 0
        
   }
   return 0;
}
