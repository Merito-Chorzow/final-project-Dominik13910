#pragma once

namespace Config {
  inline int START_THRESHOLD = 1200;
  inline int STOP_THRESHOLD  = 1000;

  inline int MIN_PWM = 10;
  inline int MAX_PWM = 255;

  constexpr int TEMP_PIN = 34;
  constexpr int FAN_PIN  = 5;

  constexpr int PWM_FREQ = 1000;
  constexpr int PWM_RES  = 8;
  constexpr int PWM_CH   = 0;
}
