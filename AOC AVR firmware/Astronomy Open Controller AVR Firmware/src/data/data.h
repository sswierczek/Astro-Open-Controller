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


#ifndef DATA_H_
#define DATA_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hd44780/HD44780_extensions.h"

void data_init();
void data_pushing_start();

void data_push_error(const char* name);

void data_push(const char* name, float data);

#endif /* DATA_H_ */