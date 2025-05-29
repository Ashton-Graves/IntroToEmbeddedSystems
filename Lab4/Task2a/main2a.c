/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25

* The purpose of this file is to handle operations for lab 2 with the other files.
*/

#include <stdint.h>
#include "lab4t2a.h"
#include "led.h"
#include "switch.h"
#include "TickFct_TrafficLight.h"
#include "timer_t2a.h"
#include "SSD2119_Display2a.h"
#include "SSD2119_Touch2a.h"
int main()
{
  timerN_init(0); // timer 0, 1, and 2
  timerN_init(1);
  timerN_init(2);
  LCD_Init();
  Touch_Init();
  LCD_ColorFill(Color4[7]);
  
  LCD_DrawFilledRect(50, 10, 220, 80, Color4[0]); // black traffic light frame
  LCD_DrawFilledCircle(90, 50, 30, Color4[4]); // red light
  LCD_DrawFilledCircle(160, 50, 30, 0xBA8E23); // yellow light
  LCD_DrawFilledCircle(230, 50, 30, Color4[2]); // green light
  
  LCD_DrawFilledCircle(80, 180, 30, Color4[8]);
  LCD_DrawFilledCircle(240, 180, 30, Color4[8]);
  LCD_Goto(11, 24);
  LCD_PrintString("POWER");
  LCD_Goto(35, 24);
  LCD_PrintString("PEDESTRIAN");
  while (1) {
    // Checks button 1 (blue) for 12Mhz
    if(((Touch_ReadX() >= 950) && (Touch_ReadX() < 1450)) && ((Touch_ReadY() >= 750) && (Touch_ReadY() < 950))) {
      GPIODATA_N |= 0x01; // LED2 on
      timer_on(1);
      timer_off(2);
    }  
    // Checks button 2 (red) for 120 Mhz
    if(((Touch_ReadX() >= 1700) && (Touch_ReadX() < 1900)) && ((Touch_ReadY() >= 750) && (Touch_ReadY() < 950))){
      GPIODATA_N |= 0x2; // LED1 on
      timer_on(2);
      timer_off(1);
    } else {
      timer_off(2);
      timer_off(1);
    }
    
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
  TickFct_TrafficLight(switch_input(0), 0); // runs pow timer, if still held, switch_input is read into switch func.
}

#pragma call_graph_root = "interrupt"
__weak void Timer2A_Handler(void) { // pedestrian switch
  GPTMICR_2 = 0x1; // clears the flag
  TickFct_TrafficLight(0, switch_input(1)); // runs ped timer, if still held, switch_input is read into switch func.
}

/*
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
    timer_off(1); // turns off timer 1
    GPTMTAILR_1 = GPTMTAILR_1; // refreshes timer 1 count
    timer_off(2);  // turns off timer 2
    GPTMTAILR_2 = GPTMTAILR_2; // refreshes timer 2 count
  }
}
  */
