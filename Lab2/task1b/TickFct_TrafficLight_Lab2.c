/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 4/16/25
* This file defines an FSM for the traffic light described in the Lab 1 specifications. The system
* has an on/off button called PWR, and a "pedestrian wants to cross" button called PED. 
*/

# include <stdint.h>
# include "lab2t1.h"
# include "led.h"

enum TL_States { TL_SMStart, TL_Off, TL_Stop, TL_Go, TL_Warn } TL_State;

void TickFct_TrafficLight(unsigned long PWR, unsigned long PED)
{
  
  switch(TL_State) {   // Transitions
     case TL_SMStart:  // Initial transition
        TL_State = TL_Off;
        break;
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
        else if (!PWR && !PED) {
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
        LED_on(1);
        break;

     case TL_Go:
        LED_on(3);
        break;

     case TL_Warn:
        LED_on(2);
        break;
        
     case TL_Off: 
        LED_off();
        break;
        
     default:
        break;
   }
}