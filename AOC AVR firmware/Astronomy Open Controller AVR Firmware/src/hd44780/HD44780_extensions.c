/*
 * HD44780_extensions.c
 *
 * Created: 2018-02-21 22:37:56
 *  Author: Sebastian
 */ 

#include "HD44780_extensions.h"

void LCD_WriteDataArray(const char *buffer)
{
	while(*buffer)
	{
		LCD_WriteData(*buffer);
		buffer++;
	}
}