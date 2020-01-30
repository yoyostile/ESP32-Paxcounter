#ifndef _SENSOR_H
#define _SENSOR_H


#if (USE_DHT)
  #include "DHT.h"
  extern DHT dht;
#endif


uint8_t sensor_mask(uint8_t sensor_no);
uint8_t * sensor_read(uint8_t sensor);
void sensor_init(void);

#endif