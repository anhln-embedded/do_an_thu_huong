#ifndef _MQTT_H_
#define _MQTT_H_

#include <WiFi.h>
#include <PubSubClient.h>

// #define ssid            "Embedded AIoT Lab(2G)"
// #define password        "embeddedlab"
// #define ssid            "Tang 4 "
// #define password        "0971126846"

#define ssid            "Ai-Photonic 2G"
#define password        "ptitlab@123"

#define MQTT_SERVER     "Mqtt.mysignage.vn"
// #define MQTT_SERVER     "broker.hivemq.com"
// #define MQTT_SERVER     "test.mosquitto.org"
#define MQTT_PORT       1883
#define MQTT_TOPIC_PUB  "huong"

#define MQTT_TOPIC_SUB  ""



void mqtt_init();
void mqtt_pub(String _topic, String _payload);
void mqtt_sub();
void mqtt_loop();

#endif