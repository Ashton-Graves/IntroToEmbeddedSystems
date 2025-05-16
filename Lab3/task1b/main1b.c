/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/13/25

* This file builds the system specified for Lab3 Task 1b. Prints internal temperature
  based on current clock frequency switch, printing to Terminal IO
*/

#include <stdint.h>
#include "Lab3tb_Inits.h"
#include "lab3t1b.h"
#include <stdio.h>

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
    
    // Convert ADC_value to temp in Celsius
    temperature = (147.5 - (247.5 * ADC_value) / 4096.0);
    
    printf("The temperature is %.1f Celsius\n", temperature); // prints the temp to Terminal IO
  }
  return 0;
}

#pragma call_graph_root = "interrupt"
__weak void ADC0SS3_Handler(void) {
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
  if((GPIODATA_J & 0x03) == 0x2) { // active low SWs
    GPIOICR_J = 0x3; // clears the flag
    PLL_Init(PRESET3); // switches to 12 MHz
  }
  // check port + mask when SW2 (PJ1) is pressed
  else if((GPIODATA_J & 0x03) == 0x1) { 
    GPIOICR_J = 0x3; // clears the flag
    PLL_Init(PRESET1); // switches to 120 MHz
  }
  else {
    GPIOICR_J = 0x2; // clears the flag
    GPIOICR_J = 0xFF; // clears the flag
  }
}

