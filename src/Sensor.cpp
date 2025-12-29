#include "Sensor.h"
#include <Arduino.h>
#include "Config.h"

void Sensor::init() {
  
}

int Sensor::readRaw() const {
  return analogRead(Config::TEMP_PIN);
}
