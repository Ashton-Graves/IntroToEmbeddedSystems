/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25
* This file defines an FSM for the traffic light described in the Lab 2 specifications. The system
* has an on/off button called PWR, and a "pedestrian wants to cross" button called PED. 
*/

# include <stdint.h>
# include "lcd.h"

enum TL_States { TL_SMStart, TL_Off, TL_Stop, TL_Go, TL_Warn } TL_State = TL_Off; // set start

void TickFct_TrafficLight(unsigned long PWR, unsigned long PED)
{
  
  switch(TL_State) {   // Transitions
     // Case transitions
     case TL_Off: 
        if (!PWR) {
           TL_State = TL_Off;
        }
        else if (PWR) {
           TL_State = TL_Stop;
        }
        break;

     case TL_Stop:
        if (PWR) {
          TL_State = TL_Off;
        }
        else if (!PWR && !PED ) {
          TL_State = TL_Go;
        }
        break;
    
    case TL_Go:
        if (PWR) {
           TL_State = TL_Off;
        }
        else if (PED) {
           TL_State = TL_Warn;
        }
        else if (!PWR && !PED) {
            TL_State = TL_Stop;
        }
        break;

     case TL_Warn:
        if (PWR) {
           TL_State = TL_Off;
        }
        else {
           TL_State = TL_Stop;
        }
        break;

     default:
        TL_State = TL_SMStart;
        break;
  } // Transitions

  switch(TL_State) {   // State actions
     case TL_Stop:
        //LED_on(1); 
        LCD_red();
        timer_sec_repeat(5, 0);  // Starts 5 sec timer
        break;

     case TL_Go:
        //LED_on(3);
        LCD_green();
        timer_sec_repeat(5, 0); //Resets 5 sec timer
        break;

     case TL_Warn:
        //LED_on(2);
        //timer_sec_repeat(5, 0);  
        LCD_yellow();
        timer_sec_repeat(5, 0);  // Resets 5 sec timer
        break;
        
     case TL_Off: 
        //LED_off();
        LCD_off();
        timer_off(0);  // Turns off timer
        break;
        
     default:
        break;
   }
}