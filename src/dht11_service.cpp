#include "dht11_service.h"
#include "state.h"
#include <lib/dht/DHT.h>

#define DHT_PIN 3
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

bool configure_dht_sensor() {
    dht.begin();
    return dht.read();
}

void read_dht_sensor() {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
}