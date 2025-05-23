/**
 * EE/CSE 474: Lab3 Task1b main function
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab4t1b_Inits.h"
#include "lab4t1b.h"
#include "SSD2119_Display1b.h"

float temperatureC, temperatureF;
char str[100], str2[100];
uint32_t ADC_value = 0;
int ADC_NewSamp = 0;
int currFreq;

int main(void) {
  // Select system clock frequency preset
  
  enum frequency freq1 = PRESET2;
  
  currFreq = PLL_Init(freq1);        // Set system clock frequency to 60 MHz
  Switch_Init();    // Initialize the 2 onboard Switches (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  LED_Init();
  LCD_Init();
  
  while(1) {
    if(ADC_NewSamp) {
      LCD_Goto(0,0);
      // Convert ADC_value to temp in Celsius
      temperatureC = 147.5 - ((247.5 * ADC_value) / 4096.0);
      temperatureF = temperatureC * 9.0/5.0 + 32;
      ADC_NewSamp = 0;
      //LCD_PrintString(emptystr);
      snprintf(str, sizeof(str), "The current temperature is %.2f C, %.2f F.   \r\n", temperatureC, temperatureF);
      snprintf(str2, sizeof(str2), "The current clock frequency is %d MHz.   \r", currFreq);
      //The current temperature is {temp_C} C, {temp_F} F.
      //LCD_SetTextColor(255, 255, 255);
      //LCD_DrawFilledRect(0, 0, 280, 20, 0xF80000);
      LCD_PrintString(str);
      LCD_PrintString(str2);
    }
  }
  return 0;
}

#pragma call_graph_root = "interrupt"
__weak void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC_0 |= 0x8; 

  ADC_value = ADCSSFIFO3_0; // get 12 ADC result bits
  ADC_NewSamp = 1;
  
}

#pragma call_graph_root = "interrupt"
__weak void SW_Handler(void) {
  GPIOICR_J = 0x3; // clears the flag
  // check port + mask when SW1 (PJ0) is pressed
  if((GPIODATA_J & 0x03) == 0x2) { // active low SWs
    currFreq = PLL_Init(PRESET3); // switches to 12 MHz
  }
  // check port + mask when SW2 (PJ1) is pressed
  else if((GPIODATA_J & 0x03) == 0x1) { 
    currFreq = PLL_Init(PRESET1); // switches to 120 MHz
  }
  
}