#ifndef _DHTSENSOR_H
#define _DHTSENSOR_H

#include "globals.h"
#include <Wire.h>

#ifdef HAS_DHT
#include "DHT.h"
#endif 

extern DHT dht;

extern Ticker dhtcycler;

extern dhtStatus_t
    dht_status; // Make struct for storing dht data globally available

// Helper functions declarations
int dht_init();
void dhtcycle(void);
void dht_storedata(dhtStatus_t *dht_store);
void loadState(void);
void updateState(void);

#endif