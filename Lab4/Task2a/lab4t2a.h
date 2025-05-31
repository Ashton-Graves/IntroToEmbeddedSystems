/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/30/25

* The purpose of this file is to define registers tailored to the functions we want for lab4
*/

#ifndef __HEADER2_H__
#define __HEADER2_H__

// GPIO Clock Gating
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
// Timer Clock Gating
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

// GPIO Port F
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// GPIO Port N
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// GPIO Port E
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))
// PORT E input
#define GPIOIEV_E (*((volatile uint32_t *)0x4005C40C))  // Interrupt on falling edges or low levels for 0, rising edges or high edges for 1 ...
#define GPIOIS_E (*((volatile uint32_t *)0x4005C404))  //  Selects between interrupt on edge (0) or level (1)
#define GPIOIM_E (*((volatile uint32_t *)0x4005C410)) // Enable interrupts for port E. Enabling a bit 0-7 corresponds to enabling that port.
#define GPIOICR_E (*((volatile uint32_t *)0x4005C41C)) // Clearing port E interrupt. Enabling a bit corresponds to clearing the interrupt for that port
#define GPIOIBE_E (*((volatile uint32_t *)0x4005C408)) // detects interrupts on both edges

// GPIO Port J
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOIEV_J (*((volatile uint32_t *)0x4006040C)) // Interrupt on falling edges or low levels for 0, rising edges or high edges for 1 ...
#define GPIOIS_J (*((volatile uint32_t *)0x40060404)) //  Selects between interrupt on edge (0) or level (1)
#define GPIOIM_J (*((volatile uint32_t *)0x40060410)) // Enable interrupts for port J. Enabling a bit 0-7 corresponds to enabling that port.
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C)) // Clearing port J interrupt. Enabling a bit corresponds to clearing the interrupt for that port

// Timer 0A Registers
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C)) // Enable/disable timer
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000)) // 32 bit mode
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004)) // Set mode (periodic, countdown)
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028)) // Set threshold
#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018)) // GPTM interrupt mask
    // Flag polling
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024)) // GPTM Timer0 interrupt clear
#define GPTMCC_0 (*((volatile uint32_t *)0x40030FC8)) // gptm clock control

#define GPTMSYNC (*((volatile uint32_t *)0x40030010))  // GPTM Timer sync

// Timer 1A Registers
#define GPTMCTL_1 (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_1 (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_1 (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))
#define GPTMIMR_1 (*((volatile uint32_t *)0x40031018)) // GPTM 1 interrupt mask
    // Flag polling
#define GPTMRIS_1 (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_1 (*((volatile uint32_t *)0x40031024))  // GPTM Timer1 interrupt clear
#define GPTMCC_1 (*((volatile uint32_t *)0x40031FC8)) // gptm clock control


// Timer 2A Registers
#define GPTMCTL_2 (*((volatile uint32_t *)0x4003200C))
#define GPTMCFG_2 (*((volatile uint32_t *)0x40032000))
#define GPTMTAMR_2 (*((volatile uint32_t *)0x40032004))
#define GPTMTAILR_2 (*((volatile uint32_t *)0x40032028))
#define GPTMIMR_2 (*((volatile uint32_t *)0x40032018)) // GPTM 2 interrupt mask
    // Flag polling
#define GPTMRIS_2 (*((volatile uint32_t *)0x4003201C))
#define GPTMICR_2 (*((volatile uint32_t *)0x40032024))  // GPTM Timer2 interrupt clear
#define GPTMCC_2 (*((volatile uint32_t *)0x40032FC8)) // gptm clock control


// Interrupts
#define EN0 (*((volatile uint32_t *)0xE000E100)) // Enable interrupt (0-31)
#define EN1 (*((volatile uint32_t *)0xE000E104)) // Enable interrupt (32-63)

#endif //__HEADER2_H__

