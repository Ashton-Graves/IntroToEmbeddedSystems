/**
 * EE/CSE 474: Lab3 Task1b main function
*/

#include <stdint.h>
#include "Lab3tb_Inits.h"
#include "lab3t1b.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq1 = PRESET3;
  PLL_Init(freq1);        // Set system clock frequency to 60 MHz
  Switch_Init();    // Initialize the 2 onboard Switches (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float temperature;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1b: Convert ADC_value to temp in Celsius
    temperature = (147.5 - (247.5 * ADC_value) / 4096.0);
    // 5.2: Change the pattern of LEDs based on the resistance
    /*
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
    */
    printf("The temperature is %.1f Celsius\n", temperature); // prints the temp
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

#pragma call_graph_root = "interrupt"
__weak void SW_Handler(void) {

  // check port + mask when SW1 (PJ0) is pressed
  if((GPIODATA_J & 0x03) == 0x1) { // active low SWs
    GPIOICR_J = 0x1; // clears the flag
    PLL_Init(PRESET3); // switches to 12 MHz
  }
  // check port + mask when SW2 (PJ1) is pressed
  else if((GPIODATA_J & 0x03) == 0x2) { 
    GPIOICR_J = 0x2; // clears the flag
    PLL_Init(PRESET1); // switches to 120 MHz
  }
}
// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler

