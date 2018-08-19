#include <DHTino.h>

DHTino dht(4);

void setup()
{
	Serial.begin(9600);
	while (!Serial) 
	{
	}
	dht.begin();
	Serial.println("Setup is done");
}

void loop()
{
	delay(2000);
	struct DHTinfo info = dht.getInfo();
	if (info.valid)
	{
		Serial.print("Humidity: ");
		Serial.println(info.humid);
		Serial.print("Temperature: ");
		Serial.println(info.temp);
	}
	else
	{
		Serial.println("Info is invalid");
	}
}
