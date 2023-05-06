#include "main.h"

void Put4bits (int put_data);
void LCD_put (int put_data);
void LCD_init ();
void LCD_print(uint8_t* str);
void LCD_Goto_XY (int x, int y);
void LCD_Clear();
void LCD_ReturnHome ();
void LCD_Create_Special_Character (uint8_t* special_character, uint8_t pattern_position);