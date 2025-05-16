/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/13/25

* This file builds the system specified for Lab3 Task 2b. Creating a "Return-to-Sender"
  function UART communication Tx and Rx to PuTTY
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab3t2b_Inits.h"
#include "lab3t2b.h"

// GLOBAL VARIABLES
char c;

int main()
{
  LED_Init();  // Init LED for reading indication
  UART_Init();  // Init UART2

  while(1) {}
  return 0;
}

#pragma call_graph_root = "interrupt"
__weak void UART2_Handler( void ) {
  if ((UARTMIS_2 & 0x30) == 0x10) {       // Receive Interrupt
    while ((UARTFR_2 & 0x10) == 0) {  // While RX FIFO not empty
      UARTICR_2 = 0x10; // Clear receive interrupt bit
      c = UARTDR_2 & 0xFF;
      while ((UARTFR_2 & 0x20)); // while until the last frame is done transmitting
      UARTDR_2 = c; // Transmit data via UART
    }
  } else {
    UARTICR_2 = 0x30; // Clear receive interrupt bit
  }
}