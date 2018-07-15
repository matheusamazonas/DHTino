/*
	DHTino.cpp - Arduino library for the DHT22 temperature and humidity sensor
	Created by Matheus Amazonas Cabral de Andrade on July 15th, 2018
*/

#include <Arduino.h>
#include <stdint.h>
#include "DHTino.h"

void DHTino::init()
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	// Specification says at least 1ms
	delay(2);
	digitalWrite(_pin, HIGH);
	// Specification says 20~40us
	delayMicroseconds(30);
	pinMode(_pin, INPUT);
	// Specification says 80ms on low, 80ms on high
	unsigned long delay = pulseIn(_pin, HIGH);
}


DHTino::DHTino (uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}


byte* DHTino::readData()
{
	init();

	unsigned long delay;
	byte value = 0;
	byte b;
	byte *data = (byte*) malloc(5 * sizeof(byte));

	for (int i=0; i < 5; i++)
	{
		b = 0;
		for(int j=0; j < 8; j++)
		{
			b = b << 1;
			delay = pulseIn(_pin, HIGH);
			delay > 28 ? value = 1 : value = 0;
			b = b | value;
			
		}
		data[i] = b;
	}
	return data;
}

struct DHTinfo DHTino::getInfo()
{
	struct DHTinfo info;
	byte* data = readData();

	if (data[4] == data[0] + data[1] + data[2] + data[3])
	{
		info.valid = true;
		info.humid = (data[0] * 265 + data[1]) / 10.0;
		info.temp = (data[2] * 256 + data[3]) / 10.0;
	}

	return info;
}

float DHTino::getTemp()
{
	struct DHTinfo info = getInfo();
	return info.temp;
}

float DHTino::getHumid()
{
	struct DHTinfo info = getInfo();
	return info.humid;
}
