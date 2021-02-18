#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
 
void setup() {
s.begin(9600);
}
 
void loop() {
 StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
  root["data1"] = random(1,10);
  Serial.println("data1");
  root["data2"] = random(11,20);
  root["data3"] = random(21,30);
if(s.available()>0)
{
 root.printTo(s);
}
}
