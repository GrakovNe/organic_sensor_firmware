#include <Arduino.h>
#include <lib/ccs811/SparkFunCCS811.h>
#include "ccs811_service.h"
#include "state.h"

#define CCS811_ADDR 0x5B

CCS811 ccs811(CCS811_ADDR);

bool configure_ccs_sensor() {
    Wire.begin();

    bool is_started = ccs811.begin();
    ccs811.setDriveMode(1);

    return is_started;
}

void read_ccs_sensor() {
    while (!ccs811.dataAvailable()) {
        delay(100);
    }

    ccs811.readAlgorithmResults();
    co2 = ccs811.getCO2();
    tvoc = ccs811.getTVOC();
}

void set_ccs_sensor_environment_data() {
    if (temperature > 0 && humidity > 0 && temperature < 100 && humidity < 100) {
        ccs811.setEnvironmentalData(humidity, temperature);
    }
}