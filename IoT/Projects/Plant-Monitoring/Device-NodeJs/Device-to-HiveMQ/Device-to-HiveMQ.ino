#include <PubSubClient.h>
#include <stdlib.h>
#include <ESP8266WiFi.h>

// #include <DHT.h>
// #define DHT_pin 4
// #define DHT_type DHT11

// float T;
// float H;

int moisture_pin = A0;  // moisture sensor
int pump_pin = 4; //pump 5v

// DHT my_dht(DHT_pin, DHT_type);

const char* ssid = "AreeeeeeeeB";
const char* password = "Positive";
const char* mqtt_server = "broker.mqtt-dashboard.com";

char pub_strT[100];
char pub_strH[100];
char pub_strMoist[100];


unsigned long previousMillis = 0;    

const long interval = 10*1000;  



WiFiClient espClient;
PubSubClient client(espClient);
void setup_wifi()
{

    delay(10);
    
    Serial.print("connecting to");
     Serial.println(ssid);
     WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED)
     {
         delay(500);
         Serial.print("-.");
     }
    
    Serial.println();
     Serial.println("WiFi Connected");
     Serial.println("WiFi got IP");
     Serial.println();
     Serial.println(WiFi.localIP());
}

void callback(String topic, byte* payload, unsigned int length)
{
     Serial.print("Message arrived : ");
     Serial.print(topic);
     Serial.print(" : ");
     String messageTemp;
     for (int i = 0; i < length; i++)
     {
//         Serial.println((char)payload[i]);
         messageTemp += (char)payload[i];
     }

     Serial.print(messageTemp);
     
     if(topic=="sarim/plant/pump"){
     
       if(messageTemp == "ON"){
          digitalWrite(pump_pin, HIGH);
       }
       else if (messageTemp == "OFF") {
          digitalWrite(pump_pin, LOW);
       }
     }
     Serial.println();
}

void reconnect()
{

    while(!client.connected()){
      Serial.println("Attempting MQTT connection");
      if(client.connect("ssuet imran"))  // add client name
      {
        Serial.println("Connected");
        client.publish("sarim/plant","Esp Connected!");
        //             topic              messagge
        client.subscribe("sarim/plant/pump");
        //                topic
        // client.subscribe("karachi/millis");
        // Serial.print("subscribed!");
      }
      else
      {
        Serial.print("Failed, rc = ");
        Serial.print(client.state());
        Serial.println("Waiting for 5 seconds to try again");
        delay(5000);
       }
     }
}

void setup()
{
 
  //  my_dht.begin();
   Serial.begin(115200);
   pinMode(moisture_pin,INPUT); 
   pinMode(pump_pin,OUTPUT);          
   setup_wifi();
   client.setServer(mqtt_server, 1883);
   //                server      port
   client.setCallback(callback);
   reconnect();
}

void loop()
{

    if(!client.connected())
    {
      reconnect();
      Serial.print("disconnected");
    }
    
    unsigned long currentMillis = millis();
    
    // float H = my_dht.readHumidity();
    // float T = my_dht.readTemperature();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

       int moisture = analogRead(moisture_pin);
    float moisture_Perc =   moisture*100/1023.;
    moisture_Perc = map(moisture_Perc,0,100,100,0);
    Serial.print("Moisture %: ");
    Serial.println(moisture_Perc);
    delay(1000);
    
    dtostrf(moisture_Perc, 2,2,pub_strMoist);
    client.publish("sarim/plant/moisture",pub_strMoist); 
    Serial.println(pub_strMoist);
      
    
      // sprintf(pub_str,"%11d",currentMillis);
      // dtostrf(H,2,2,pub_strH);
      // dtostrf(T,2,2,pub_strT);
//      sprintf(pub_str,"%s"," IMRAN");
    // Serial.print("Temperature: ");
    //  Serial.print(pub_strT);

    //  Serial.print("Humidity: ");
    //  Serial.println(pub_strH);
//      Serial.print(" ");
//      Serial.println(currentMillis);
      // client.publish("sarim/",pub_strH);
      // client.publish("sarim/esp8266/dht11/temperature",pub_strT);
      delay(1000);
    }
    client.loop();
}
