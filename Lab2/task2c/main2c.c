#include <stdint.h>
#include "lab2t2c.h"
#include "led.h"
#include "switch.h"
#include "TickFct_TrafficLight.h"
#include "timer_t2c.h"
int main()
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10; // Enable port E
  RCGCGPIO |= 0x1000; // Enable port N - for testing with onboard leds
  delay++;
  delay++;
  LED_init();
  extern_switch_init();
  timerN_init(0);
  timerN_init(1);
  timerN_init(2);
  GPIODATA_E = 0x0; // turn all lights initially off
  
  
   // configure leds - condider making this a function
   GPIODIR_N = 0x3; // Set PN0 and PN1 to output
   GPIODEN_N = 0x3; // Set PN0 and PN1 to digital port
   GPIODATA_N = 0x0; // initialize port N to off
  
  
  while (1) {
    
  }
  return 0;
}

#pragma call_graph_root = "interrupt"
__weak void Timer0A_Handler(void) {
  GPTMICR_0 = 0x1; // clears the flag
  TickFct_TrafficLight(0, 0); // calls tick function to the next state with no input.
}

#pragma call_graph_root = "interrupt"
__weak void Timer1A_Handler(void) { // power switch
  GPTMICR_1 = 0x1; // clears the flag
  GPIODATA_N |= 0x2; // LED1 on
  TickFct_TrafficLight(switch_input(0), 0); // runs pow timer, if still held, switch_input is read into switch func.
}

#pragma call_graph_root = "interrupt"
__weak void Timer2A_Handler(void) { // pedestrian switch
  GPTMICR_2 = 0x1; // clears the flag
 // GPIODATA_N |= 0x02; // LED2 on
  TickFct_TrafficLight(0, switch_input(1)); // runs ped timer, if still held, switch_input is read into switch func.
}

#pragma call_graph_root = "interrupt"
__weak void PortE_Handler(void) {
  
  if((GPIODATA_E & 0x03) == 0x1) { // Detect pow button, starts 2 sec timer
    GPIODATA_N |= 0x01; // LED2 on
    GPIOICR_E = 0x1; // clears the flag for PE0
    timer_on(1);
    timer_off(2);
  } 
  
  else if ((GPIODATA_E & 0x03) == 0x2) {  // Detect ped button, starts 2 sec timer
    GPIOICR_E = 0x2; // clears the flag for PE1
    GPIODATA_N |= 0x2; // LED1 on
    timer_on(2);
    timer_off(1);
  }
  
  else if ((GPIODATA_E & 0x03) == 0x3) {
    GPIOICR_E = 0x3; // clears the flag for PE1 and PE0
    timer_on(1);
    timer_on(2);
  }
  else if ((GPIODATA_E & 0x03) == 0x0) {
    GPIOICR_E = 0x3; // clears the flag for PE1 and PE0
    GPIODATA_N = 0x0; // LED2 off
    timer_off(1);
    GPTMTAILR_1 = GPTMTAILR_1;
    timer_off(2);
    GPTMTAILR_2 = GPTMTAILR_2;
  }
/*
if((GPIODATA_E & 0x03) == 0x1) {
  GPIOICR_E = 0x1;
  timer_sec_repeat(2,1);
} else if ((GPIODATA_E & 0x03) == 0x2) {
  GPIOICR_E = 0x3;
  timer_sec_repeat(2,2); 
}
  */
}
