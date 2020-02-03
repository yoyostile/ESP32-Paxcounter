#ifndef _SENSOR_H
#define _SENSOR_H

#include "globals.h"

extern switchStatus_t switch_status; 

uint8_t sensor_mask(uint8_t sensor_no);
uint8_t * sensor_read(uint8_t sensor);
void sensor_init(void);
void switch_storedata(switchStatus_t *switch_store);

#endif
