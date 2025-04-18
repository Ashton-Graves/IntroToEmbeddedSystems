#include <stdint.h>
#include "led.h"
#include "switch.h"
#include "TickFct_TrafficLight.h"
int main()
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= ;
  delay++;
  delay++;
  LED_init();
  extern_switch_init();
  GPIODATA_E = ;
  
  while(1) {
    unsigned long pow = switch_input();
    unsigned long ped = switch_input();
    TickFct_TrafficLight(pow, ped);
  }
  return 0;
}
