
#include <Arduino.h>
#include "bridge.h"
#include "mqtt.h"
#include "ArduinoJson.h"

#define BUZZER 32
bool fire = 0;
uint8_t state = 0;
uint32_t time_old = 0;

void callBackOnMessage(uint8_t *_buf, uint8_t _length, uint8_t _from);
void Buzzer_setup(void){
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);
}

void setup() 
{
  Buzzer_setup();
  Serial.begin(115200);
  mqtt_init();
  bridge_setup();
  time_old = millis();
}

void loop()
{ 
  mqtt_loop();
  bridge_loop(callBackOnMessage);
  if(millis() - time_old > 300){
    if(fire){
      state = !state;
    }
    else
    {
      state = 1;
    }
    digitalWrite(BUZZER, state);
    time_old = millis();
  }
}

void callBackOnMessage(uint8_t *_buf, uint8_t _length, uint8_t _from){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, (const char*)_buf);
  if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  }
  const char* flame = doc["flame"];
  const char* gas = doc["gas"];
  Serial.println("ANH" + String(flame) + String(gas));
  if(atoi(flame) == 1 || atoi(gas) == 1){
    fire = 1;
  }
  else{
     fire = 0;   
  }
  String JSON = "";
  JSON += "{";
  JSON += "\"address\":" + String(_from) + ",";
  JSON += "\"data\":" + String((char*)_buf); 
  JSON += "}";
  mqtt_pub(MQTT_TOPIC_PUB, JSON); 
  Serial.println(JSON); 
}