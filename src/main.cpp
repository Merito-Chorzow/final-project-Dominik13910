#include <Arduino.h>
#include "FanController.h"
#include "Sensor.h"
#include "CommandHandler.h"
#include "Config.h"
#include "Telemetry.h"

Sensor sensor;
FanController controller;
Telemetry telemetry;

unsigned long lastControlTick = 0;
constexpr unsigned long CONTROL_INTERVAL_MS = 200;

void setup() {
  Serial.begin(115200);
  sensor.init();
  controller.init();
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    handleCommand(cmd);
  }

  unsigned long now = millis();
  if (now - lastControlTick >= CONTROL_INTERVAL_MS) {
    lastControlTick = now;

    int temp = sensor.readRaw();
    telemetry.lastTempRaw = temp;

    if (temp == 0) {
      telemetry.sensorErrors++;
    }

    controller.update(temp);
    telemetry.lastPwm = controller.getLastPwm();

    static FanController::State prevState = FanController::State::INIT;
    FanController::State currentState = controller.getState();

    if (currentState == FanController::State::FAULT &&
        prevState != FanController::State::FAULT) {
      telemetry.faultCount++;
    }

    prevState = currentState;
  }
}
