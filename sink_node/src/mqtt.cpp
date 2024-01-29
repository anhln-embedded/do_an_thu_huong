#include "mqtt.h"

// const char* ssid = "REPLACE_WITH_YOUR_SSID";
// const char* password = "REPLACE_WITH_YOUR_PASSWORD";
WiFiClient espClient;
PubSubClient client(espClient);
static void setup_wifi(); 
static void reconnect();
static void callback_on_message(char* topic, byte* message, unsigned int length);
void mqtt_init(){
    setup_wifi();
    client.setServer(MQTT_SERVER, 1883);
}

void mqtt_loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();    
}

void mqtt_pub(String _topic, String _payload){
    client.publish(_topic.c_str(), _payload.c_str());
}


static void setup_wifi(){
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());    
}

static void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("thu_huong")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

static void callback_on_message(char* topic, byte* message, unsigned int length) {

}

