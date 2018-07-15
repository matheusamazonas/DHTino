/*
	DHTino.h - Arduino library for the DHT22 temperature and humidity sensor
	Created by Matheus Amazonas Cabral de Andrade on July 15th, 2018
*/

#ifndef DHTino_H
#define DHTino_H

#include <stdint.h> 

struct DHTinfo
{
	double temp;
	double humid;
};

class DHTino
{
public:
	DHTino(uint8_t pin);
	struct DHTinfo getInfo();
	double getTemp();
	double getHumid();
private:
	uint8_t _pin;
	void init();
	double readTemp();
	double readHumid();
	double readCheck();
};

#endif