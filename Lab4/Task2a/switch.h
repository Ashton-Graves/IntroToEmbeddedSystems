/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25

* The purpose of this file is to provide function declarations to allow use of external pushbuttons with the TIVA LaunchPad board.
*/

#ifndef SWITCH_H_
#define SWITCH_H_

// Initializes the proper registers to enable PE0 and PE1 to connect to pushbuttons.
void extern_switch_init(void);

// Gets the value of the pushutton input (pressed or unpressed).
// parameters - an integer called func that specifies which of the pushbuttons to get.
//              0 - gets the value of the power pushbutton.
//              1 - gets the value of the pedestrian pusbutton.
unsigned long switch_input(int func);

#endif //SWITCH_H_