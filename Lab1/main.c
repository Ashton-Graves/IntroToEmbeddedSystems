#include <stdint.h>
#include "lab1.h"
int main(void)
{
    volatile unsigned short delay = 0;

    RCGCGPIO |= 0x1020; // Enable Ports N and F GPIO

    /*
    We need to wait a bit between initializing the port and doing anything with that port - essentially
    waiting 2 clock cycles
    */

    delay++; // Delay 2 more cycles before access Timer registers
    delay++; // Refer to Page. 756 of Datasheet for info


    GPIODIR_F = 0x1; // Set PF0 to output
    GPIODEN_F = 0x1; // Set PF0 to digital port

    GPIODIR_N = 0x1; // Set PF0 to output
    GPIODEN_N = 0x1; // Set PF0 to digital port

    GPIODATA_F = 0x1; // Set PF0 to 1

    while (1) {

        
    }

    return 0;
}
