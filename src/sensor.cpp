// Basic Config
#include "globals.h"

// Local logging tag
static const char TAG[] = __FILE__;


switchStatus_t switch_status = {0};

#define SENSORBUFFER                                                           \
  10 // max. size of user sensor data buffer in bytes [default=20]

void sensor_init(void) {
  #if (USE_SWITCH)
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), SwitchIRQ, RISING);
    if (RTC_runmode == RUNMODE_WAKEUP) {
      switch_storedata(&switch_status);
    }
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
  int8_t buttonState;
  switch (sensor) {

    case 1:
      buf[0] = length;
      buf[1] = 0x01;
      buf[2] = 0x02;
      buf[3] = 0x03;
      break;
    #if (USE_SWITCH)
    case 2:
      buf[0] = 1;
      buf[1] = switch_status.mail;
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

void switch_storedata(switchStatus_t *switch_store) {
  #if (USE_SWITCH)
    if (digitalRead(SWITCH_PIN) == HIGH) {
      switch_store->mail = HIGH;
    }
  #endif
}
