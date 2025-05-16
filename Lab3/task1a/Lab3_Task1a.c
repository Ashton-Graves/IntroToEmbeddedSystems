/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/13/25

* This file builds the system specified for Lab3 Task 1a. LED indicator
  for current potentiometer resistance
*/

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include "Lab3_Inits.h"
#include "lab3t1a.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    resistance = (ADC_value / 4095.0) * 10.0;
    // 5.2: Change the pattern of LEDs based on the resistance
    if (resistance < 2.5) {
      GPIODATA_N |= 0x2; // Set PN1 to 1
      GPIODATA_N &= ~0x1;
      GPIODATA_F &= ~(0x11);
      // GPIODATA_F = 0x0;
    } else if (resistance < 5.0) {
      GPIODATA_N |= 0x3; // Set PN1 and PN0 to 1
      GPIODATA_F &= ~(0x11);
      // GPIODATA_F = 0x0;
    } else if (resistance < 7.5) {
      GPIODATA_F |= 0x10; // Set PF4 to 1
      GPIODATA_F &= ~(0x1);
    } else {
      GPIODATA_F |= 0x11; // Set PF4 and PF0 to 1
    }
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC_0 |= 0x8; 
  
  // 4.2: Save the ADC value to global variable ADC_value
  ADCPSSI_0 |= 0x8; // Starts the conversion process
  
  while((ADCRIS_0 & 0x8) != 0x0) {} // waits for the conversion to finish
  ADC_value = ADCSSFIFO3_0; // get 12 ADC result bits
}
