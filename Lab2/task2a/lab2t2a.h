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

// Timer 0
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C)) // enable/disable timer
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000)) // 32 bit mode
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004)) // set mode (periodic, countdown)
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028)) // set threshold

#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018)) // GPTM interrupt mask

// Flag polling
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

#define EN0 (*((volatile uint32_t *)0xE000E100)) // enable interrupt (0-31)

#endif //__HEADER2_H__




