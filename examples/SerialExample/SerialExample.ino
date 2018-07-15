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
