/*
	DHTino.cpp - Arduino library for the DHT22 temperature and humidity sensor
	Created by Matheus Amazonas Cabral de Andrade on July 15th, 2018
*/

#include <Arduino.h>
#include <stdint.h>
#include "DHTino.h"

DHTino::DHTino (uint8_t pin)
{
	_pin = pin;
}

struct DHTinfo DHTino::getInfo()
{
	
}

double DHTino::getTemp()
{
	return 0;
}

double DHTino::getHumid()
{
	return 0;
}