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


#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hd44780/HD44780_extensions.h"
#include "dht/dht.h"
#include "ds18b20/ds18b20.h"
#include "dewpoint/dewpoint.h"

static int const INT_CONVERTION_BASE = 10;
static int const FLOAT_WIDTH = 3;
static int const FLOAT_PRECISION = 1;

static int const LCD_CACHE_SIZE = 16;

int main (void)
{
	char lcd_cache[LCD_CACHE_SIZE];
	int sensorTemperature;

	#if DHT_TYPE == DHT_DHT11
	int8_t temperature = 0;
	int8_t humidity = 0;
	#elif DHT_TYPE == DHT_DHT22
	float temperature = 0;
	float humidity = 0;
	#endif
	
	LCD_Initalize();

	for (;;) {
		
		// Get temperature and humidity from DHT sensor
		if(dht_gettemperaturehumidity(&temperature, &humidity) == -1) {
			LCD_GoTo(0,1);
			LCD_WriteText("Error reading DHT state");
		}
		
		// Get temperature from DS18B20 sensor
		ds18b20convert( &PORTB, &DDRB, &PINB, ( 1 << 0 ), NULL );
		_delay_ms( 1000 );
		ds18b20read( &PORTB, &DDRB, &PINB, ( 1 << 0 ), NULL, &sensorTemperature );
		
		// Display data
		LCD_Clear();
		LCD_GoTo(0,0);
		
		#if DHT_TYPE == DHT_DHT11
		itoa(temperature, lcd_cache, INT_CONVERTION_BASE);
		#elif DHT_TYPE == DHT_DHT22
		dtostrf(temperature, FLOAT_WIDTH, FLOAT_PRECISION, lcd_cache);
		#endif
		
		LCD_WriteText("Temp:");
		LCD_WriteDataArray(lcd_cache);

		#if DHT_TYPE == DHT_DHT11
		itoa(humidity, lcd_cache, INT_CONVERTION_BASE);
		#elif DHT_TYPE == DHT_DHT22
		dtostrf(humidity, FLOAT_WIDTH, FLOAT_PRECISION, lcd_cache);
		#endif
		
		LCD_WriteText(",H:");
		LCD_WriteDataArray(lcd_cache);
		
		float sensorRealTemperature = (float) sensorTemperature / DS18B20_MUL;
		dtostrf(sensorRealTemperature, FLOAT_WIDTH, FLOAT_PRECISION, lcd_cache);

		LCD_GoTo(0,1);
		LCD_WriteText("DT:");
		LCD_WriteDataArray(lcd_cache);
		
		float dewpoint = dewpoint_calculate(temperature, humidity);
		dtostrf(dewpoint, FLOAT_WIDTH, FLOAT_PRECISION, lcd_cache);
		
		LCD_WriteText(",DP:");
		LCD_WriteDataArray(lcd_cache);

		_delay_ms(1500);
	}

	return 0;
}