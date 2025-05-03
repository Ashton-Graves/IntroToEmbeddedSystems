/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/01/25

* The purpose of this file is to provide function declarations to allow use of external LEDs with the TIVA LaunchPad board.
*/

#ifndef LED_H_
#define LED_H_

// Initializes the proper registers to enable PE2, PE3, and PE5 to connect to LEDs.
void LED_init(void);

// Turns on one of three LEDs (red (PE2), yellow (PE3), or green (PE5)). Turns off all other LEDs.
// parameters: an integer called color that designates which of the LEDs to turn on.
//              1 - turns on the red LED (PE2)
//              2 - turns on the yellow LED (PE3)
//              3 - turns on the green LED (PE5)
void LED_on(int color);

// Turns off all of the LEDs.
void LED_off();

#endif //LED_H_