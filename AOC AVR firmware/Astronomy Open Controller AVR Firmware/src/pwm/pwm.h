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

#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

#define PWM_CHANNEL_0			PB1
#define PWM_CHANNEL_0_DIR		DDRB
#define PWM_CHANNEL_0_PORT		PORTB
#define PWM_CHANNEL_0_PIN		PINB
#define PWM_CHANNEL_0_REGISTER	TCCR1A
#define PWM_CHANNEL_0_MODE		WGM10
#define PWM_CHANNEL_0_CYCLE		OCR1A

#define PWM_CHANNEL_1			PB2
#define PWM_CHANNEL_1_DIR		DDRB
#define PWM_CHANNEL_1_PORT		PORTB
#define PWM_CHANNEL_1_PIN		PINB
#define PWM_CHANNEL_1_REGISTER	TCCR1B
#define PWM_CHANNEL_1_MODE		WGM10
#define PWM_CHANNEL_1_CYCLE		OCR1B

#define PWM_CHANNEL_2			PB3
#define PWM_CHANNEL_2_DIR		DDRB
#define PWM_CHANNEL_2_PORT		PORTB
#define PWM_CHANNEL_2_PIN		PINB
#define PWM_CHANNEL_2_REGISTER	TCCR2A
#define PWM_CHANNEL_2_MODE		WGM20
#define PWM_CHANNEL_2_CYCLE		OCR2A

void PWM_init();

#endif /* PWM_H_ */