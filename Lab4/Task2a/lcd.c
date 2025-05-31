/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/30/25

* The purpose of this file is to provide function definitions for functions that change the traffic light colors on the
* LCD used in Lab 4 task 2a.
*/

#include "SSD2119_Display2a.h"
#include "lab4t2a.h"

void LCD_off() {
    LCD_DrawFilledCircle(90, 50, 30, Color4[4]); // red light off 
    LCD_DrawFilledCircle(230, 50, 30, Color4[2]); // green light off
    LCD_DrawFilledCircle(160, 50, 30, 0xBA8E23); // yellow light off
}

void LCD_red() {
    LCD_DrawFilledCircle(230, 50, 30, Color4[2]); // green light off
    LCD_DrawFilledCircle(160, 50, 30, 0xBA8E23); // yellow light off
    LCD_DrawFilledCircle(90, 50, 30, Color4[12]); // red light on
}

void LCD_green() {
    LCD_DrawFilledCircle(90, 50, 30, Color4[4]); // red light off
    LCD_DrawFilledCircle(160, 50, 30, 0xBA8E23); // yellow light off
    LCD_DrawFilledCircle(230, 50, 30, Color4[10]); // green light on
}

void LCD_yellow() {
    LCD_DrawFilledCircle(90, 50, 30, Color4[4]); // red light off
    LCD_DrawFilledCircle(230, 50, 30, Color4[2]); // green light off
    LCD_DrawFilledCircle(160, 50, 30, Color4[14]); // yellow light on
}