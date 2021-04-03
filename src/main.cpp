#include <Arduino.h>
#include <lib/dht/DHT.h>

#include "state.h"
#include "ccs811_service.h"
#include "dht11_service.h"

#define INITIALIZING_TIMEOUT 5000
#define MEASUREMENT_TIMEOUT 1000

#define DHT_PIN 3
#define DHT_TYPE DHT11

[[noreturn]] void freeze() { while (true); }

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing...");
    delay(INITIALIZING_TIMEOUT);

    if (!configure_ccs_sensor()) {
        Serial.print("CCS811 error. Please check wiring. Freezing...");
        freeze();
    }

    if (!configure_dht_sensor()) {
        Serial.print("DHT11 error. Please check wiring. Freezing...");
        freeze();
    }
}

void report_state() {
    static char screen_buffer[64];

    sprintf(screen_buffer, "tvoc: %d; co2: %d; temperature: %s; humidity: %s;\n",
            tvoc,
            co2,
            String(temperature).c_str(),
            String(humidity).c_str());

    Serial.print(screen_buffer);
}

void loop() {
    read_ccs_sensor();
    read_dht_sensor();

    set_ccs_sensor_environment_data();

    report_state();

    delay(MEASUREMENT_TIMEOUT);
}