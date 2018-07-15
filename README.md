# DHTino
Arduino library for the DHT22 temperature and humidity sensor

Linux: : [![Build Status](https://travis-ci.com/matheusamazonas/DHTino.svg?branch=master)](https://travis-ci.com/matheusamazonas/DHTino)

Installation
-------------
For a simple, easy installation download the repository as a zip file and follow the instructions on [how to install an Arduino library from a zip file](https://www.arduino.cc/en/Guide/Libraries#toc4).

Example
-------------
The example below is also in the `examples` folder. 

```cpp
#include <DHTino.h>

DHTino dht(4);

void setup()
{
	Serial.begin(9600);
  while (!Serial) 
  {
  }
  Serial.println("Setup is done");
}

void loop()
{
  delay(2000);
  struct DHTinfo info = dht.getInfo();
  Serial.print("Humidity: ");
  Serial.println(info.humid);
  Serial.print("Temperature: ");
  Serial.println(info.temp);
}

```

