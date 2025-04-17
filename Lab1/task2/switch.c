void extern_switch_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1000; // Enable Port N Gating Clock
  delay++;
  delay++;
  GPIOAMSEL_N &= ~0x4; // Disable PN2 analog function
  GPIOAFSEL_N &= ~0x4; // Select PN2 regular port function
  GPIODIR_N &= ~0x4; // Set PN2 to input direction
  GPIODEN_N |= 0x4; // Enable PN2 digital function
}
  unsigned long switch_input(void)
{
  return (GPIODATA_N & 0x4); // 0x4 (pressed) or 0 (not pressed)
}