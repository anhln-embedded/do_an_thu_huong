#include "lora_node.h"
#include "read_sensor.h"

uint32_t LAST_TIME = 0;

void setup(){
  Serial.begin(115200);
  lora_node_setup();
  read_sensor_setup_all();
  LAST_TIME = millis();
}

void loop(){
  if(millis() - LAST_TIME > 1000 || isFire()){
    String payload = read_sensor_all(); 
    Serial.println(payload);
    lora_node_send(payload , BRIDGE_ADDRESS);
    LAST_TIME = millis();
  }
  lora_node_loop();
}

