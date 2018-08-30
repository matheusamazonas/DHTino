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

void DHTino::begin()
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

void DHTino::initTransmission()
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

byte* DHTino::readData()
{
	unsigned long delay;
	byte value, b = 0;
	// The sensor sends 40 bits of data, 5 bytes
	byte *data = (byte*) malloc(5 * sizeof(byte));
	if (data == NULL)
	{
		return NULL;
	}
	else
	{
		initTransmission();
		for (int i=0; i < 5; i++)
		{
			b = 0;
			for(int j=0; j < 8; j++)
			{
				b = b << 1;
				delay = pulseIn(_pin, HIGH);
				// 26~28ms is a 0, 70ms is a 1
				delay > 28 ? value = 1 : value = 0;
				b = b | value;
				
			}
			data[i] = b;
		}
		return data;
	}
}

struct DHTinfo DHTino::getInfo()
{
	struct DHTinfo info;
	// Read all the data at once
	byte* data = readData();

	if (data == NULL)
	{
		info.valid = false;
	}
	else
	{
		// The last byte is the checksum
		if (data[4] == (byte) (data[0] + data[1] + data[2] + data[3]))
		{
			info.valid = true;
			info.humid = (data[0] * 255 + data[1]) / 10.0;
			info.temp = (data[2] * 255 + data[3]) / 10.0;
			// The first bit represents it signal
			if (data[2] & 128)
			{
				info.temp = - info.temp;
			}
		}
		free(data);
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
