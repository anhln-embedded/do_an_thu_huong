//
//    FILE: ML8511_determine_DUV_factor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ML8511 UV sensor - to determine DUV factor
//    DATE: 2021-06-19
//     URL: https://github.com/RobTillaart/ML8511
//
//        BREAKOUT
//      +-------+--+
//  VIN |o      +-+| mounting hole
//  3V3 |o      +-+|
//  GND |o         |
//  OUT |o         |
//   EN |o       S |  Sensor
//      +----------+
//
//   EN = ENABLE


#define RH_MESH_MAX_MESSAGE_LEN 50
#include <Arduino.h>
#include <RHMesh.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <ML8511.h>

#define ANALOGPIN     33
#define ENABLEPIN     17

ML8511 light(ANALOGPIN, ENABLEPIN);

// for calculating the average
float    sum   = 0;
uint32_t count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("UV UltraViolet ML8511");

  // manually enable / disable the sensor.
  light.enable();

  Serial.print("\tmW cm^2");
  Serial.print("\tDUV index");
  Serial.println();
}


void loop()
{
  Serial.print("enter reference DUV:\t");
  // flush all
  while (Serial.available() > 0) Serial.read();
  while (Serial.available() == 0);
  float DUV = Serial.parseFloat();
  Serial.println(DUV);

  float UV = light.getUV();
  Serial.print("UV mW cm^2:\t\t");
  Serial.println(UV, 4);

  Serial.print("DUV factor:\t\t");
  float factor = DUV / UV;
  Serial.println(factor, 2);

  // calculate the average
  count++;
  sum += factor;
  Serial.print("DUV factor average:\t");
  Serial.println(sum / count);
  Serial.println();
  Serial.println();
}


// -- END OF FILE --

