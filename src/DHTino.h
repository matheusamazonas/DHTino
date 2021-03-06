/*
	DHTino.h - Arduino library for the DHT22 temperature and humidity sensor
	Created by Matheus Amazonas Cabral de Andrade on July 15th, 2018
*/

#ifndef DHTino_H
#define DHTino_H

#include <stdint.h> 

struct DHTinfo
{
	bool valid = false;
	float temp;
	float humid;
};

class DHTino
{
public:
	DHTino(uint8_t pin);
	void begin();
	struct DHTinfo getInfo();
	float getTemp();
	float getHumid();
private:
	uint8_t _pin;
	void initTransmission();
	byte* readData();
};

#endif