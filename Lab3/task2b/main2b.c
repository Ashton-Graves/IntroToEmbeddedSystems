
// TODO - header comment


#include <stdint.h>
#include <stdio.h>
#include "Lab3t2b_Inits.h"
#include "lab3t2b.h"

// GLOBAL VARIABLES
char c;

int main()
{
  LED_Init();
  UART_Init();

  while(1) {
  }
  return 0;
}


#pragma call_graph_root = "interrupt"
__weak void UART2_Handler( void ) {
  if ((UARTMIS_2 & 0x30) == 0x10) {       // Receive Interrupt
    GPIODATA_F ^= 0x1;
    UARTICR_2 = 0x10; // Clear receive interrupt bit
    c = UARTDR_2 & 0xFF;
    while ((UARTFR_2 & 0x20)); // while until the last frame is done transmitting
    UARTDR_2 = c;
    printf("receive interrupt");
  } else if ((UARTMIS_2 & 0x30) == 0x20) {        // Transmit Interrupt
    UARTICR_2 = 0x20; // Clear recieve interrupt bit
    printf("transmit interrupt");
  } else {
    printf("neither");
  }
}