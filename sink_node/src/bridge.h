#ifndef _BRIDGE_H_
#define _BRIDGE_H_


#include <RHMesh.h>
#include <RH_RF95.h>
#include <SPI.h>

#define RH_MESH_MAX_MESSAGE_LEN 90

#define BRIDGE_ADDRESS           1  
// lilygo T3 v2.1.6
// lora SX1276/8
#define LLG_SCK 18
#define LLG_MISO 19
#define LLG_MOSI 23
#define LLG_CS  5
#define LLG_RST 14
#define LLG_DI0 13
#define RXTIMEOUT 3000  // it is roughly the delay between successive transmissions


void bridge_setup();
void bridge_loop(void (*callBack)(uint8_t *_buf, uint8_t _length, uint8_t _from));


#endif