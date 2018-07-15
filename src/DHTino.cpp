/*
	DHTino.cpp - Arduino library for the DHT22 temperature and humidity sensor
	Created by Matheus Amazonas Cabral de Andrade on July 15th, 2018
*/

#include <Arduino.h>
#include <stdint.h>
#include "DHTino.h"

union floatData
{
	float f;
	int data[2];
};

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
	// Serial.println(delay);
	Serial.println("Done with init");
}


DHTino::DHTino (uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

int DHTino::readInt()
{
	unsigned long delay;
	int value = 0;
	int data = 0;

	for (int i=0; i<16; i++)
	{
		delay = pulseIn(_pin, HIGH);
		delay > 28 ? value = 1 : value = 0;
		data = data | value;
		data = data << 1;
	}
	return data;
}

struct DHTinfo DHTino::getInfo()
{
	init();
	
	struct DHTinfo info;
	int data = readInt();

	floatData f;
	info.humid = data >> 8;
	info.humid += (data & 255) / 1000.0;
	info.humid = 1;
	Serial.print("Data: ");
	Serial.println(data);

	data = readInt();
	info.temp = data >> 8;
	info.temp += (data & 255) / 1000.0;
	Serial.print("Data: ");
	Serial.println(data);
	f.data[1] = 0;
	// info.temp = f.f;

	// Serial.println(data);

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
