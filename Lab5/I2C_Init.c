#include <stdint.h>
#include <stdio.h>
#include "I2C_Init.h"
#include "tm4c1294ncpdt.h"

void I2C_Init() {
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; // Clockgating port B
  SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;  // Clockgating I2C module 0
  GPIO_PORTB_DEN_R |= 0xC;
  GPIO_PORTB_AFSEL_R |= 0xC;
  GPIO_PORTB_PCTL_R |= 0x2200;
  GPIO_PORTB_ODR_R |= 0x8;
  I2C0_MCR_R |= 0x10;
  I2C0_MSA_R = 0x10; // slave address: 0x08, transmit bit: 0 --> 00010000
  I2C0_MTPR_R = 0x7;
}

void I2C_Send(uint8_t data) {
   I2C0_MDR_R = data;  // writes data to i2c0 register
   I2C0_MCS_R = 0x07;  // sets but for 1 byte transmission (start, stop, run)
   // I2C0_MCS_R = I2C_MCS_RUN | I2C_MCS_START | I2C_MCS_STOP;
   I2C0_MSA_R = 0x10;
   while((I2C0_MCS_R & 0x40));  // wait will data finishes transmitting
}