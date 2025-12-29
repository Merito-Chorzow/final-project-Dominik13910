#include "FanController.h"
#include <Arduino.h>
#include "Config.h"

void FanController::init() {
  ledcSetup(Config::PWM_CH, Config::PWM_FREQ, Config::PWM_RES);
  ledcAttachPin(Config::FAN_PIN, Config::PWM_CH);
}

void FanController::update(int tempRaw) {
  switch (state) {
    case State::INIT:
      ledcWrite(Config::PWM_CH, 0);
      state = State::IDLE;
      break;

    case State::IDLE:
      ledcWrite(Config::PWM_CH, 0);
      if (tempRaw > Config::START_THRESHOLD)
        state = State::RUN;
      break;

    case State::RUN:
      if (tempRaw < Config::STOP_THRESHOLD) {
        state = State::IDLE;
        break;
      }
      lastPwm = map(
        tempRaw,
        Config::START_THRESHOLD,
        4095,
        Config::MIN_PWM,
        Config::MAX_PWM
      );
      lastPwm = constrain(lastPwm, 0, 255);
      ledcWrite(Config::PWM_CH, lastPwm);
      break;

    case State::FAULT:
      ledcWrite(Config::PWM_CH, 0);
      break;
  }
}

State FanController::getState() const {
  return state;
}
