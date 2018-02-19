#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HD44780.h"
#include "dht.h"

void LCD_WriteDataArray(const char *buffer)
{
	while(*buffer)
	{
		LCD_WriteData(*buffer);
		buffer++;
	}
}

int main (void)
{
	
	board_init();
	LCD_Initalize();
	
	char lcd_cache[100];

	#if DHT_FLOAT == 0
	int8_t temperature = 0;
	int8_t humidity = 0;
	#elif DHT_FLOAT == 1
	float temperature = 0;
	float humidity = 0;
	#endif

	for (;;) {
		
		if(dht_gettemperaturehumidity(&temperature, &humidity) != -1) {

			LCD_Clear();
			LCD_GoTo(0,0);

			#if DHT_FLOAT == 0
			itoa(temperature, lcd_cache, 10);
			#elif DHT_FLOAT == 1
			dtostrf(temperature, 3, 1, lcd_cache);
			#endif
			
			LCD_WriteText("Temp: ");
			LCD_WriteDataArray(lcd_cache);
			LCD_WriteText(" C");
			LCD_GoTo(0,1);
			
			#if DHT_FLOAT == 0
			itoa(humidity, lcd_cache, 10);
			#elif DHT_FLOAT == 1
			dtostrf(humidity, 3, 1, lcd_cache);
			#endif
			
			LCD_WriteText("Hum : ");
			LCD_WriteDataArray(lcd_cache);
			LCD_WriteText(" %RH");
			LCD_GoTo(1,0);

			} else {
			LCD_GoTo(0,1);
			LCD_WriteText("Error");
		}
		_delay_ms(1500);
	}

	return 0;
}