#ifndef _LORA_MESH_H_
#define _LORA_MESH_H_

#define RH_MESH_MAX_MESSAGE_LEN 50
#include <Arduino.h>
#include <RHMesh.h>
#include <RH_RF95.h>
#include <SPI.h>

// In this small artifical network of 4 nodes,
#define BRIDGE_ADDRESS 1  // address of the bridge ( we send our data to, hopefully the bridge knows what to do with our data )
#define NODE_ADDRESS 2    // address of this node
// lilygo T3 v2.1.6
// lora SX1276/8
#define LLG_SCK 18
#define LLG_MISO 19
#define LLG_MOSI 23
#define LLG_CS  5
#define LLG_RST 14
#define LLG_DI0 13

void lora_node_setup();
void lora_node_loop();
void lora_node_send(String payload, uint16_t Adress_sink);

#endif