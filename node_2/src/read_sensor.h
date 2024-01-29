#ifndef _READ_SENSOR_H_
#define _READ_SENSOR_H_

#include "Arduino.h"
#include "DHT.h"

#define THRESHOLD 1000

void  read_sensor_setup_all(void);
String read_sensor_all(void);
bool isFire(void);

#endif