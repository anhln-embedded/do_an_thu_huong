#include "read_sensor.h"

/*Cau hình cảm biến DHT22*/
#define DHTPIN 32
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
/*---------end----------*/


void  read_sensor_setup_all(void){
    pinMode(12, OUTPUT);
    dht.begin();
}
String read_sensor_all() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int Flame  = analogRead(26);
    int Gas = analogRead(25);
    // Dust Density = 2173.58 ug/m3
    if(Flame < THRESHOLD || Gas > 900){
        digitalWrite(12, HIGH);
    }
    else{
         digitalWrite(12, LOW);
    }
    // Chuyển đổi dữ liệu thành chuỗi JSON
    String JSON = "{";
    JSON += "\"humi\":\"" + String(h) + "\",";
    JSON += "\"temp\":\"" + String(t) + "\",";
    JSON += "\"flame\":\"" + String(Flame < THRESHOLD) + "\",";
     JSON += "\"gas\":\"" + String(Gas > 900) + "\"";
    JSON += "}";
    return JSON;
}

bool isFire(void){
    return analogRead(26) < THRESHOLD;
}

// {
//     "address" : "2",
//     "data":
//     {
//         "Humi" : "78.56",
//         "Temp" : "28.03",
//         "Dust": "10.62",
//         "Co2": "2.56",
//         "Uv": "10.56"
//     }
// }