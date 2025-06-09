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
#include "I2C_Init.h"

char testStr[100];
char testchar[100];
int data_value;

int released = 0;
int main()
{
  LCD_Init();
  Touch_Init();
  PLL_Init(PRESET2);
  LCD_ColorFill(Color4[7]);
  I2C_Init();
  
  LCD_DrawFilledRect(27, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(82, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(137, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(192, 70, 45, 170, Color4[15]); // white key
  LCD_DrawFilledRect(247, 70, 45, 170, Color4[15]); // white key
 /* LCD_DrawFilledRect(105, 80, 150, 200, Color4[15]); // white key
  LCD_DrawFilledRect(155, 80, 200, 200, Color4[15]); // white key

*/
  while (1) {
   
    if(((Touch_ReadX() >= 800) && (Touch_ReadX() < 1200)) && 
       ((Touch_ReadY() >= 500) && (Touch_ReadY() < 1100))) { // if key 1 pressed, send value 1
        I2C_Send(0x01); // for sending actual value (which sound pitch we want)
        // I2C_Send(0x01);  for sending bit (if we go with sound based on bit placement idea)
          data_value = 0x01;
          released = 1;
         
    } 
    else if (((Touch_ReadX() >= 1250) && (Touch_ReadX() < 1500)) && 
               ((Touch_ReadY() >= 500) && (Touch_ReadY() < 1100))) {  // if key 2 pressed, send value 2
        I2C_Send(0x02); // for sending actual value (which sound pitch we want)
        // I2C_Send(0x02);  for sending bit (if we go with sound based on bit placement idea)
       data_value = 0x02;
       released = 1;
    } 
    else if (((Touch_ReadX() >= 1580) && (Touch_ReadX() < 1780)) && 
               ((Touch_ReadY() >= 500) && (Touch_ReadY() < 1100))) {  // if key 3 pressed, send value 3
        I2C_Send(0x03); // for sending actual value (which sound pitch we want)
        // I2C_Send(0x04);  for sending bit (if we go with sound based on bit placement idea)
         data_value = 0x03;
         released = 1;
    } 
    else if (((Touch_ReadX() >= 1800) && (Touch_ReadX() < 1950)) && 
               ((Touch_ReadY() >= 500) && (Touch_ReadY() < 1100))) {  // if key 4 pressed, send value 4
        I2C_Send(0x04); // for sending actual value (which sound pitch we want)
        // I2C_Send(0x08);  for sending bit (if we go with sound based on bit placement idea)
       data_value = 0x04;
       released = 1;
    } 
    else if (((Touch_ReadX() >= 2000) && (Touch_ReadX() < 2200)) && 
               ((Touch_ReadY() >= 500) && (Touch_ReadY() < 1100))) {  // if key 5 pressed, send value 5
        I2C_Send(0x05); // for sending actual value (which sound pitch we want)
        // I2C_Send(0x10);  for sending bit (if we go with sound based on bit placement idea)
        data_value = 0x05;
        released = 1;
      
    } 
    else { // else (~release key press) = turn off sound
      if (released == 1) {
        I2C_Send(0);  // not sure what value would turn off the sound
        data_value = 0x00;
      }
      released = 0;
      
    }
    
    // Test function for key placement & value
    LCD_Goto(0,0);
    snprintf(testStr, sizeof(testStr), "The current pos is x%lu, y%lu.        \n", Touch_ReadX(), Touch_ReadY());
    snprintf(testchar, sizeof(testchar), "The current val is %lu.        ", data_value);
    LCD_PrintString(testStr);
    LCD_PrintString(testchar);
  }
  return 0;
}
