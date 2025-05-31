/*
* Ashton Graves, Quan Hoang
* graveash, qhoang05
* 05/30/25

* The purpose of this file is to provide function declarations for functions that change the traffic light colors on the
* LCD used in Lab 4 task 2a.
*/

#ifndef LCD_H_
#define LCD_H_

// This function turns each light in the traffic light to a dull shade of its respective color (light off)
void LCD_off(void);

// This function turns the red light in the traffic light to a bright red, and sets the green and yellow light to dull shades.
void LCD_red(void);

// This function turns the green light in the traffic light to a bright green, and sets the red and yellow light to dull shades.
void LCD_green(void);

// This function turns the yellow light in the traffic light to a bright red, and sets the green and red light to dull shades.
void LCD_yellow(void);

#endif //LCD_H_