#if (HAS_DHT)

#include "dhtsensor.h"

// Local logging tag
static const char TAG[] = __FILE__;

dhtStatus_t dht_status = {0};
DHT dht(DHT_PIN, DHT_TYPE);

Ticker dhtcycler;

void dhtcycle() { xTaskNotify(irqHandlerTask, DHT_IRQ, eSetBits); }

int dht_init(void) {
  dht.begin();
  dhtcycler.attach(DHTCYCLE, dhtcycle);
  dht_storedata(&dht_status);
  return 1;
} // dht_init()

// store current DHT sensor data in struct
void dht_storedata(dhtStatus_t *dht_store) {
  if (cfg.payloadmask & MEMS_DATA) { // block i2c bus access
    dht_store->temperature = dht.readTemperature();
    dht_store->humidity = dht.readHumidity();
    //   updateState();
  }
} // dht_storedata()

#endif // HAS_BME
