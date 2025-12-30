#pragma once
#include <stdint.h>

struct Telemetry {
  uint32_t sensorErrors = 0;
  uint32_t faultCount   = 0;

  int lastTempRaw = 0;
  int lastPwm     = 0;
};
