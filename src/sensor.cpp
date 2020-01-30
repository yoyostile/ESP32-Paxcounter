// Basic Config
#include "globals.h"

#if (USE_DHT)
  DHT dht(DHT_PIN, DHT_TYPE);
#endif
// Local logging tag
static const char TAG[] = __FILE__;

#define SENSORBUFFER                                                           \
  10 // max. size of user sensor data buffer in bytes [default=20]

void sensor_init(void) {
  #if (USE_DHT)
    dht.begin();
  #endif
  #if (USE_SWITCH)
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), SwitchIRQ, RISING);
  #endif

  // this function is called during device startup
  // put your user sensor initialization routines here
}

uint8_t sensor_mask(uint8_t sensor_no) {
  switch (sensor_no) {
  case 0:
    return (uint8_t)COUNT_DATA;
  case 1:
    return (uint8_t)SENSOR1_DATA;
  case 2:
    return (uint8_t)SENSOR2_DATA;
  case 3:
    return (uint8_t)SENSOR3_DATA;
  case 4:
    return (uint8_t)BATT_DATA;
  case 5:
    return (uint8_t)GPS_DATA;
  case 6:
    return (uint8_t)MEMS_DATA;
  case 7:
    return (uint8_t)ALARM_DATA;
  default:
    return 0;
  }
}

uint8_t *sensor_read(uint8_t sensor) {

  static uint8_t buf[SENSORBUFFER] = {0};
  uint8_t length = 3;
  uint8_t h;
  int16_t t;
  int8_t buttonState;
  switch (sensor) {

  #if (USE_DHT)
  case 1:
    h = dht.readHumidity();
    t = 10 * dht.readTemperature();

    buf[0] = length;
    buf[1] = t >> 8;
    buf[2] = t;
    buf[3] = h;
    break;
  #endif
  #if (USE_SWITCH)
  case 2:
    buttonState = digitalRead(SWITCH_PIN);
    if (buttonState == HIGH) {
      buf[0] = 1;
      buf[1] = 0x01;
    }
    break;
  #endif
  case 3:

    buf[0] = length;
    buf[1] = 0x01;
    buf[2] = 0x02;
    buf[3] = 0x03;
    break;
  }

  return buf;
}