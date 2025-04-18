void extern_switch_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1000; // Enable Port N Gating Clock
  delay++;
  delay++;
  GPIOAMSEL_E &= ~0x3; // Disable PE0 & PE1 analog function
  GPIOAFSEL_E &= ~0x3; // Select PE0 & PE1 regular port function
  GPIODIR_E &= ~0x3; // Set PE0 & PE1 to input direction
  GPIODEN_E |= 0x3; // Enable PE0 & PE1 digital function
}
  unsigned long switch_input(void)
{
  return (GPIODATA_N & 0x4); // 0x4 (pressed) or 0 (not pressed)
}