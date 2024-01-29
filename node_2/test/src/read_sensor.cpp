#include "read_sensor.h"
#include <MQUnifiedsensor.h>
#include <ML8511.h>

/*Cau hình cảm biến DHT22*/
#define DHTPIN 32
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
/*---------end----------*/

/*Cấu hình cảm biến bụi*/
int measurePin = 26;   // Connect dust sensor analog measure pin to Arduino A0 pin
int ledPin     = 27;    // Connect dust sensor LED pin to Arduino pin 2
GP2Y1010AU0F dustSensor(ledPin, measurePin); // Construct dust sensor global object
float dustDensity = 0;
/*---------end----------*/


/*Cấu hình cảm biến MQ135*/
#define placa "ESP-32"
#define Voltage_Resolution 5
#define pin 25 //Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 12 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
double CO2 = 0;
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
void MQ135_config(void);
/*---------end----------*/

/*Cấu hình cảm biến UV*/
#define ANALOGPIN     33
#define ENABLEPIN     17
ML8511 light(ANALOGPIN, ENABLEPIN);
float    sum   = 0;
uint32_t count = 0;
/*---------end----------*/

void  read_sensor_setup_all(void){
    dht.begin();
    dustSensor.begin();
    MQ135_config();
    light.enable();
}
String read_sensor_all() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    dustDensity = dustSensor.read();
    // Dust Density = 2173.58 ug/m3
    MQ135.update(); // Update data, the Arduino will read the voltage on the analog pin
    MQ135.setA(110.47); MQ135.setB(-2.862);
    CO2 = MQ135.readSensor();

    float DUV = Serial.parseFloat();
    float UV = light.getUV();
    float factor = DUV / UV;
    // calculate the average
    count++;
    sum += factor;
    // Chuyển đổi dữ liệu thành chuỗi JSON
    String JSON = "{";
    JSON += "\"humi\":\"" + String(h) + "\",";
    JSON += "\"temp\":\"" + String(t) + "\",";
    JSON += "\"Dust\":\"" + String(dustDensity) + "\",";
    JSON += "\"Co2\":\"" + String(CO2) + "\",";
    JSON += "\"Uv\":\"" + String(sum / count) + "\"";
    JSON += "}";
    return JSON;
}

void MQ135_config(void){
  if (Serial) Serial.println("Serial is open");

  // Set math model to calculate the PPM concentration and the value of constants
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b

  MQ135.init(); 
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++)
  {
    MQ135.update(); // Update data, the arduino will read the voltage on the analog pin
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0 / 10);
  Serial.println("  done!.");

  if (isinf(calcR0)) { Serial.println("Warning: Connection issue found, R0 is infinite (Open circuit detected) please check your wiring and supply"); while (1); }
  if (calcR0 == 0) { Serial.println("Warning: Connection issue found, R0 is zero (Analog pin with a short circuit to ground) please check your wiring and supply"); while (1); }
  /*****************************  MQ Calibration ********************************************/
  MQ135.serialDebug(false);
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