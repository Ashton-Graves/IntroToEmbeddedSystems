#include <stdint.h>
#include "lab1.h"
#include "led.h"
#include "switch.h"
#include "TickFct_TrafficLight.h"
int main(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10;
  delay++;
  delay++;
  LED_init();
  extern_switch_init();
  GPIODATA_E = 0x0;
  
  while(1) {
    static unsigned int loopCounter = 0;
    
    unsigned long pow = switch_input(0); // reads input from power button
    unsigned long ped = switch_input(1); // reads input from pedestrian button
    
    if (loopCounter >= 7000) {
      TickFct_TrafficLight(pow, ped); // FSM reading switch inputs to activate LED
      loopCounter = 0;
    }
    
    loopCounter++;
  }
}
