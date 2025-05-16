/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/13/25

* The purpose of this file is to initialize drivers for functions utilized in Lab3 t2b
*/

#include "PLL_Header.h"
#include "Lab3t2b_Inits.h"
#include "lab3t2b.h"
   
   
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
  
  UARTIM_2 |= 0x10; // set TXIM, RXIM bit to cause interrupt to be sent to NVIC when transmit, recieve is finished
  
  // Flush RX FIFO
  while ((UARTFR_2 & 0x10) == 0) {
    volatile char _ = UARTDR_2;
  }

  UARTICR_2 = 0x30; // use this in interrupt handler for interrupt clear
  EN1 |= 0x2; // enable interrupt 33 (UART2)
  
  UARTCTL_2 |= 0x301; // enable transmit, recieve section of UART, and enable UART
}