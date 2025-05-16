/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab3t2b_Inits.h"
#include "lab3t2b.h"

void LED_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.

  // YOUR CODE HERE
  RCGCGPIO |= 0x1000 | 0x20; // Enable PortN & PortF GPIO
  
  volatile int delay = 0;
  delay++;
  delay++;
  
  GPIODIR_F = 0x11; // Set PF0 and PF4 to output
  GPIODEN_F = 0x11; // Set PF0 and PF4 to digital port
  GPIODATA_F = 0x0; 
   
  GPIODIR_N = 0x3; // Set PN0 and PN1 to output
  GPIODEN_N = 0x3; // Set PN0 and PN1 to digital port
  GPIODATA_N = 0x0; // Set Port N to 0s
}
   
   
void UART_Init(void) {
  volatile unsigned short delay = 0;
  RCGCUART |= 0x4; // Clock gating for UART2
  RCGCGPIO |= 0x1; // Clock gating for port A;
  
  delay++;
  delay++;
  
  GPIOAFSEL_A |= 0xC0; // PA6 (U2Rx) and PA7 (U2Tx) alternate function
  // GPIOPCTL_A &= ~(0xFF);
  GPIOPCTL_A |= 0x11000000; // PA6 and PA7 are using their first alternate function (U2Rx and U2Tx respectively)
  GPIODEN_A |= 0xC0; // set PA6 and PA7 to digital pins
  
  UARTCTL_2 &= ~(0x1); // disable UART while configuring
  UARTCC_2 = 0x5; // select alternate clock (PIOSC) 

  UARTIBRD_2 = 104; // integer baud rate divisor
  UARTFBRD_2 = 11; // fractional baud rate divisor

  UARTLCRH_2 = 0x60; // 8 bit word length, no parity, one stop bit
  UARTCTL_2 |= 0x301; // enable transmit, recieve section of UART, and enable UART
  
  UARTIM_2 |= 0x30; // set TXIM, RXIM bit to cause interrupt to be sent to NVIC when transmit, recieve is finished

  UARTICR_2 = 0x30; // use this in interrupt handler for interrupt clear
  EN1 |= 0x2; // enable interrupt 33 (UART2)
}