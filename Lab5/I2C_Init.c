#include <stdint.h>
#include <stdio.h>
#include "I2C_Init.h"
#include "tm4c1294ncpdt.h"

I2C_Init() {
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
  SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;
  GPIO_PORTB_DEN_R |= 0xC;
  GPIO_PORTB_AFSEL_R |= 0xC;
  GPIO_PORTB_PCTL_R |= 0x2200;
  GPIO_PORTB_ODR_R |= 0x8;
  I2C0_MCR_R |= 0x10;
  I2C0_MSA_R = 0x10; // slave address: 0x08, transmit bit: 0 --> 00010000
  I2C0_MTPR_R = 0x7;
}

I2C_Send() {

}