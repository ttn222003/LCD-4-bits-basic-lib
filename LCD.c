#include "main.h"

void Put4bits (int put_data){
	HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,put_data & 0x80);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,put_data & 0x40);
	HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,put_data & 0x20);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,put_data & 0x10);
	HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin,GPIO_PIN_RESET);
}

void LCD_put (int put_data){
	Put4bits(put_data);
	Put4bits(put_data << 4);
	HAL_Delay(1);
}

void LCD_init (){
	HAL_Delay(15);
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET);
	Put4bits(0x30);
	HAL_Delay(5);
	Put4bits(0x30);
	HAL_Delay(1);
	Put4bits(0x30);
	HAL_Delay(1);
	Put4bits(0x20);
	
	LCD_put(0x28);
	LCD_put(0x08);
	LCD_put(0x01);
	LCD_put(0x06);
	LCD_put(0x0D);
}

void LCD_print(uint8_t* str){
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_SET);
	int i = 0;
	while(*(str + i) != '\0'){
		LCD_put(*(str + i));
		i++;
	}
}

void LCD_Goto_XY (int x, int y){
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET);
	int location = 0x80 + 0x40*y + x;
	LCD_put(location);
}

void LCD_Clear(){
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET);
	LCD_put(0x01);
}

void LCD_ReturnHome (){
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET);
	LCD_put(0x02);
	HAL_Delay(2);
}

void LCD_Create_Special_Character (uint8_t* special_character, uint8_t pattern_position){
	HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET);
	for (uint8_t row = 0; row<8; row++){
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_RESET);
		LCD_put(0x40 + (pattern_position << 3) + row);
		HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_SET);
		LCD_put(*(special_character + row));
	}
}