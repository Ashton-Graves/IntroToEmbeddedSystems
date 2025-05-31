
#include "SSD2119_Display1a.h"
#include "SSD2119_Touch1a.h"
#include "tm4c1294ncpdt1a.h"

int main()
{
  LCD_Init();
  LCD_ColorFill(0xF800);
  while (1) { }
  return 0;
  
}
