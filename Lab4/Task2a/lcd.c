#include "SSD2119_Display2a.h"
#include "lab4t2a.h"

void LCD_off() {
    LCD_DrawFilledCircle(90, 50, 30, Color4[4]); // red light off 
    LCD_DrawFilledCircle(160, 50, 30, 0xBA8E23); // yellow light off
    LCD_DrawFilledCircle(230, 50, 30, Color4[2]); // green light off
}

void LCD_red() {
    LCD_DrawFilledCircle(90, 50, 30, Color4[12]); // red light on
    LCD_DrawFilledCircle(160, 50, 30, 0xBA8E23); // yellow light off
    LCD_DrawFilledCircle(230, 50, 30, Color4[2]); // green light off
}

void LCD_green() {
    LCD_DrawFilledCircle(90, 50, 30, Color4[4]); // red light off
    LCD_DrawFilledCircle(160, 50, 30, 0xBA8E23); // yellow light off
    LCD_DrawFilledCircle(230, 50, 30, Color4[10]); // green light on
}

void LCD_yellow() {
    LCD_DrawFilledCircle(90, 50, 30, Color4[4]); // red light off
    LCD_DrawFilledCircle(160, 50, 30, Color4[14]); // yellow light on
    LCD_DrawFilledCircle(230, 50, 30, Color4[2]); // green light off
}