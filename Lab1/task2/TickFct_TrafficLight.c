/*
* Ashton Graves, Quan Hoang
* Student ID
* Date
* This file defines an FSM for the traffic light described in the Lab 1 specifications. The system
* has an on/off button called PWR, and a "pedestrian wants to cross" button called PED. 
*/

# include "lab1.h"

enum TL_States { TL_SMStart, TL_Off, TL_Stop, TL_go, TL_Warn } TL_State;

void TickFct_TrafficLight()
{
  switch(TL_State) {   // Transitions
     case TL_SMStart:  // Initial transition
        TL_State = TL_Off;
        break;

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
        else if (PED) {
           TL_State = TL_Stop;
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
        // turn on red LED
        break;

     case TL_Go:
        // turn on green LED
        break;

    case TL_Warn:
        // turn on yellow LED
        break;

     default:
        break;
   } // State actions
}