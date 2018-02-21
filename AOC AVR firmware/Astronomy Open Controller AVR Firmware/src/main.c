#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hd44780/HD44780_extensions.h"
#include "dht/dht.h"
#include "ds18b20/ds18b20.h"

int main (void)
{
	
	LCD_Initalize();
	
	char lcd_cache[100];

	#if DHT_FLOAT == 0
	int8_t temperature = 0;
	int8_t humidity = 0;
	#elif DHT_FLOAT == 1
	float temperature = 0;
	float humidity = 0;
	#endif
	
	int sensorTemperature;

	for (;;) {
		
		// Get temp and hum from DHT sensor
		if(dht_gettemperaturehumidity(&temperature, &humidity) == -1) {
			LCD_GoTo(0,1);
			LCD_WriteText("Error reading DHT state");
		}
		
		// Get temp from DS18B20 sensor
		ds18b20convert( &PORTB, &DDRB, &PINB, ( 1 << 0 ), NULL );

		//Delay (sensor needs time to perform conversion)
		_delay_ms( 1000 );

		//Read temperature (without ROM matching)
		ds18b20read( &PORTB, &DDRB, &PINB, ( 1 << 0 ), NULL, &sensorTemperature );
		
		LCD_Clear();
		LCD_GoTo(0,0);
		
		#if DHT_FLOAT == 0
		itoa(temperature, lcd_cache, 10);
		#elif DHT_FLOAT == 1
		dtostrf(temperature, 3, 1, lcd_cache);
		#endif
		
		LCD_WriteText("T:");
		LCD_WriteDataArray(lcd_cache);

		#if DHT_FLOAT == 0
		itoa(humidity, lcd_cache, 10);
		#elif DHT_FLOAT == 1
		dtostrf(humidity, 3, 1, lcd_cache);
		#endif
		
		LCD_WriteText(", H:");
		LCD_WriteDataArray(lcd_cache);
		
		float sensorRealTemperature = (float) sensorTemperature / DS18B20_MUL;
		dtostrf(sensorRealTemperature, 3, 1, lcd_cache);

		LCD_GoTo(0,1);
		LCD_WriteText("T2:");
		LCD_WriteDataArray(lcd_cache);
		
		_delay_ms(1500);
	}

	return 0;
}