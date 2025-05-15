/**
 * EE/CSE 474: Lab3 Task1b main function
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab3t2a_Inits.h"
#include "lab3t2a.h"
// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE


float temperature;
char str[32];
uint32_t index = 0;
uint32_t ADC_value = 0;
int ADC_NewSamp = 0;

int main(void) {
  // Select system clock frequency preset
  
  enum frequency freq1 = PRESET3;
  
  PLL_Init(freq1);        // Set system clock frequency to 60 MHz
  UART_Init(); // Initialize UART
  // Switch_Init();    // Initialize the 2 onboard Switches (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  LED_Init();
  
  while(1) {
    if(ADC_NewSamp) {
      // Convert ADC_value to temp in Celsius
      temperature = (147.5 - (247.5 * ADC_value) / 4096.0);
      ADC_NewSamp = 0;
      snprintf(str, sizeof(str), "Temp in C: %.2f\r\n", temperature);
      index = 0;
      UARTDR_0 = str[index];
    }
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
  ADC_NewSamp = 1;
  
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


#pragma call_graph_root = "interrupt"
__weak void UART0_Handler(void) {
  UARTICR_0 = 0x20;// clear interrupt caused by TXIC (transmit interrupt clear) bit
  GPIODATA_F ^= 0x01;
  if (str[index] != '\0') {
    UARTDR_0 = str[index];
    index++;
  } else {
    index = 0;
  }

}