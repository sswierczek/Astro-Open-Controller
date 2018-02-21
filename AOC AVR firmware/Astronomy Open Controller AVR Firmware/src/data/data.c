/*
* Astronomy Open Controller
* Copyright (C) 2018  Sebastian Swierczek

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "data.h"

static int const FLOAT_WIDTH = 3;
static int const FLOAT_PRECISION = 1;

static int const LCD_LINE_LENGHT = 16;

static int lcd_characters_displayed = 0;
static bool is_in_second_line = false;

char LCD_CACHE[16];

void skip_to_second_line_if_needed(const char* name);

/**
* Initialize data communication/displaying. Should be called only once.
**/
void data_init()
{
	LCD_Initalize();
}

/**
* Prepare port/display for data communication/display. Should be called at main loop start.
**/
void data_pushing_start()
{
	LCD_Clear();
	LCD_GoTo(0,0);
	lcd_characters_displayed = 0;
	is_in_second_line = false;
}

/**
* Send or display error message
**/
void data_push_error(const char* name)
{
	LCD_Clear();
	LCD_WriteText(name);
}

/**
* Send or display number value with given name.
**/
void data_push(const char* name, float data)
{
	dtostrf(data, FLOAT_WIDTH, FLOAT_PRECISION, LCD_CACHE);
	skip_to_second_line_if_needed(name);
	LCD_WriteText(name);
	LCD_WriteText(":");
	LCD_WriteDataArray(LCD_CACHE);
	LCD_WriteText(" ");
}

void skip_to_second_line_if_needed(const char* name) {
	lcd_characters_displayed += strlen(name) + strlen(LCD_CACHE);
	if (lcd_characters_displayed >= LCD_LINE_LENGHT && !is_in_second_line) {
		is_in_second_line = true;
		LCD_GoTo(0,1);
	}
}