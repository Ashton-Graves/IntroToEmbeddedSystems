/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/30/25
* This file defines an FSM for the traffic light described in the Lab 4 specifications (task2a). The system
* has an on/off button called PWR, and a "pedestrian wants to cross" button called PED. 
*/

# include <stdint.h>
# include "Task2b/lcd.h"

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
        LCD_red();
        break;

     case TL_Go:
        LCD_green();
        break;

     case TL_Warn:
        LCD_yellow();
        break;
        
     case TL_Off: 
        LCD_off();
        break;
        
     default:
        break;
   }
}