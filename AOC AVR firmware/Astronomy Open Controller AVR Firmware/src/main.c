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
#include "dht/dht.h"
#include "ds18b20/ds18b20.h"
#include "dewpoint/dewpoint.h"
#include "pwm/pwm.h"
#include "data/data.h"

int main (void)
{

	int sensorTemperature;

	#if DHT_TYPE == DHT_DHT11
	int8_t temperature = 0;
	int8_t humidity = 0;
	#elif DHT_TYPE == DHT_DHT22
	float temperature = 0;
	float humidity = 0;
	#endif
	
	data_init();
	PWM_init();

	for (;;) {
		
		// Get temperature and humidity from DHT sensor
		if(dht_gettemperaturehumidity(&temperature, &humidity) == -1) {
			data_push_error("Error reading DHT state");
		}
		
		// Get temperature from DS18B20 sensor
		ds18b20convert( &PORTB, &DDRB, &PINB, ( 1 << 0 ), NULL );
		_delay_ms( 1000 );
		ds18b20read( &PORTB, &DDRB, &PINB, ( 1 << 0 ), NULL, &sensorTemperature );
		
		// Display data
		data_pushing_start();
		data_push("Temp", temperature);
		data_push("Hum", humidity);
		data_push("DT", (float) sensorTemperature / DS18B20_MUL);
		data_push("DP", dewpoint_calculate(temperature, humidity));

		_delay_ms(1500);
	}

	return 0;
}