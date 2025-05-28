/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25

* The purpose of this file is to provide the function declaration for the TickFct_TrafficLight function.
*/

#ifndef TICKFCT_TRAFFICLIGHT_H_
#define TICKFCT_TRAFFICLIGHT_H_

// this function is an FSM to control the behavior of the traffic light (LEDs) when the system is in certain states, and when the pushbutton inputs occur.
// parameters - an unsigned long called PWR that corresponds to the input of the power pushbutton, and an unsigned long called PED that corresponds to the
// pedestrian pushbutton.
void TickFct_TrafficLight(unsigned long PWR, unsigned long PED);

#endif //TICKFCT_TRAFFICLIGHT_H_