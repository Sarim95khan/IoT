#include <DHT.h>
#define DHT_pin 4
#define DHT_type DHT11

float T;
float H;
DHT my_dht(DHT_pin, DHT_type);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
my_dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
T = my_dht.readTemperature();
Serial.print("Temperature: ");
Serial.print(T);

H = my_dht.readHumidity();
Serial.print("Humidity: ");
Serial.println(H);

}
