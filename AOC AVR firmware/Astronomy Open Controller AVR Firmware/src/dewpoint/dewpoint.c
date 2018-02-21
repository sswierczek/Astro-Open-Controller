/*
* dewpoint.c
*
* Created: 2018-02-21 22:51:41
*  Author: Sebastian
*/

#include "dewpoint.h"

/**
* Temperature should be in °C and humidity in % RH
* Returns dew point in °C
**/
float dewpoint_calculate(float temperature, float humidity)
{
	return temperature - (100. - humidity) / 5.;
}