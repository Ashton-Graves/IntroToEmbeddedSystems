/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 06/3/25

* The purpose of this file is to implement a traffic light system on an LCD as specified for Lab 4.
*/

#include <stdint.h>
#include "lab5.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "PLL_Init.h"
int main()
{
  LCD_Init();
  Touch_Init();
  PLL_Init(PRESET2);
  LCD_ColorFill(Color4[7]);
  
  LCD_DrawFilledRect(27, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(82, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(137, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(192, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(247, 70, 45, 170, Color4[15]); // white key
 /* LCD_DrawFilledRect(105, 80, 150, 200, Color4[15]); // white key
  LCD_DrawFilledRect(155, 80, 200, 200, Color4[15]); // white key

*/
  while (1) {

  }
  return 0;
}
