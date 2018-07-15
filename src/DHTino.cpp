/*
	DHTino.cpp - Arduino library for the DHT22 temperature and humidity sensor
	Created by Matheus Amazonas Cabral de Andrade on July 15th, 2018
*/

#include <Arduino.h>
#include <stdint.h>
#include "DHTino.h"

void DHTino::init()
{
	digitalWrite(_pin, LOW);
	// Specification says at least 1ms
	delay(2);
	digitalWrite(_pin, HIGH);
	// Specification says 20~40us
	delayMicroseconds(30);
	pinMode(_pin, INPUT);
	// Specification says 80ms on low, 80ms on high
	unsigned long delay = pulseIn(_pin, HIGH);
	Serial.println(delay);
}

double DHTino::readTemp()
{

}

double DHTino::readHumid()
{
	return 0;
}

double DHTino::readCheck()
{
	return 0;
}

DHTino::DHTino (uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

struct DHTinfo DHTino::getInfo()
{
	init();
	double t = readTemp();
	double h = readHumid();
	double c = readCheck();
}

double DHTino::getTemp()
{
	struct DHTinfo info = getInfo();
	return info.temp;
}

double DHTino::getHumid()
{
	struct DHTinfo info = getInfo();
	return info.humid;
}
