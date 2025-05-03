/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 04/30/25

* This file creates a system that models a traffic light. The system has two pushbuttons, a power button and a pedestrian button. It also
* has three LEDs; a red (stop), yellow (warn), and green LED. The power button turns the traffic light on and off (the light is initially
* red when the system is turned on), and the pedestrian button turns the traffic light to yellow, and then green. Utilizes ports on the
* TIVA board to achieve this.
*/

#include <stdint.h>
#include "lab2t1.h"
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "TickFct_TrafficLight.h"
int main(void)
{
  volatile unsigned short delay = 0;
  LED_init();
  extern_switch_init();
  timer0_init();
  timer1_init();
  delay++;
  delay++;
  
  while(1) {
    // static unsigned int loopCounter = 0; // loopCounter provides some delay without using a timer.
    
    unsigned long pow = switch_input(0); // reads input from power button
    unsigned long ped = switch_input(1); // reads input from pedestrian button
    
    TickFct_TrafficLight(pow, ped); // FSM reading switch inputs to activate LED
  }  
  return 0;
}