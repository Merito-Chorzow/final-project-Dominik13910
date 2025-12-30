#include "FanController.h"
#include <Arduino.h>
#include "Config.h"

void FanController::init() {
  ledcSetup(Config::PWM_CH, Config::PWM_FREQ, Config::PWM_RES);
  ledcAttachPin(Config::FAN_PIN, Config::PWM_CH);
  ledcWrite(Config::PWM_CH, 0);
}

bool FanController::isTempValid(int tempRaw) const {
  return tempRaw > 0 && tempRaw <= 4095;
}

void FanController::update(int tempRaw) {

  if (state == State::FAULT) {
    if (isTempValid(tempRaw)) {
      state = State::IDLE;
    } else {
      lastPwm = 0;
      ledcWrite(Config::PWM_CH, 0);
      return;
    }
  }

  if (!isTempValid(tempRaw)) {
    state = State::FAULT;
    lastPwm = 0;
    ledcWrite(Config::PWM_CH, 0);
    return;
  }

  switch (state) {

    case State::INIT:
      ledcWrite(Config::PWM_CH, 0);
      state = State::IDLE;
      break;

    case State::IDLE:
      ledcWrite(Config::PWM_CH, 0);
      if (tempRaw >= Config::START_THRESHOLD) {
        state = State::RUN;
      }
      break;

    case State::RUN:
      if (tempRaw < Config::STOP_THRESHOLD) {
        ledcWrite(Config::PWM_CH, 0);
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

      lastPwm = constrain(
        lastPwm,
        Config::MIN_PWM,
        Config::MAX_PWM
      );

      ledcWrite(Config::PWM_CH, lastPwm);
      break;

    case State::FAULT:

      lastPwm = 0;
      ledcWrite(Config::PWM_CH, 0);
      break;
  }
}


FanController::State FanController::getState() const {
  return state;
}

int FanController::getLastPwm() const {
  return lastPwm;
}
