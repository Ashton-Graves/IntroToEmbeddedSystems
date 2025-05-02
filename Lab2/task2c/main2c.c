#include <stdint.h>
#include "lab2t2c.h
#include "led.h"
#include "switch.h"
#include "TickFct_TrafficLight.h"
int main()
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10; // Enable port E
  delay++;
  delay++;
  LED_init();
  extern_switch_init();
  timerN_init(0);
  timerN_init(1);
  timerN_init(2);
  GPIODATA_E = 0x0; // turn all lights initially off
  
  
  while (1) {
    
  }
  return 0;
}

#pragma call_graph_root = "interrupt"
__weak void Timer0A_Handler(void) {
  TickFct_TrafficLight(0, 0); // calls tick function to the next state with no input.
}

#pragma call_graph_root = "interrupt"
__weak void Timer1A_Pow_Handler(void) {
  if((GPIODATA_E & 0x03) == 0x1) {
    TickFct_TrafficLight(1, 0); //runs power input to the tick funtion (PE0)
  }
}

#pragma call_graph_root = "interrupt"
__weak void Timer2A_Ped_Handler(void) {
  if((GPIODATA_E & 0x03) == 0x1) {
    TickFct_TrafficLight(0, 1); //runs power input to the tick funtion (PE1)
  }
}

#pragma call_graph_root = "interrupt"
__weak void SW_Handler(void) {
  if((GPIODATA_E & 0x03) == 0x1) { // Detect pow button, starts 2 sec timer
    timer_sec_repeat(2, 1);
  } else if ((GPIODATA_E & 0x03) == 0x2) {  // Detect ped button, starts 2 sec timer
    timer_sec_repeat(2, 2);
  }
}
