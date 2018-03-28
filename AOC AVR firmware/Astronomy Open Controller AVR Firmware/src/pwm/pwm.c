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

#include "pwm.h"

// TODO Use constants from pwm.h
void PWM_init() {
	// Set PWM channels as outputs
	PWM_CHANNEL_0_DIR |= (1<< PWM_CHANNEL_0);
	PWM_CHANNEL_1_DIR |= (1<< PWM_CHANNEL_1);
	PWM_CHANNEL_2_DIR |= (1<< PWM_CHANNEL_2);
	
	// Set mode 
	TCCR1B |= (1<< PWM_CHANNEL_0_MODE);
	TCCR1B |= (1<< PWM_CHANNEL_1_MODE);
	TCCR2B |= (1<< PWM_CHANNEL_2_MODE);
	
	// Set prescaler 8
	PWM_CHANNEL_0_REGISTER |= (1<< CS11);
	PWM_CHANNEL_1_REGISTER |= (1<< CS12);
	PWM_CHANNEL_2_REGISTER |= (1<< CS21);
	
	// Set initial duty cycle
	PWM_CHANNEL_0_CYCLE = 255;
	PWM_CHANNEL_1_CYCLE = 100;	
	PWM_CHANNEL_2_CYCLE = 50;
}