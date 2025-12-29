#include <Arduino.h>
#include "Sensor.h"
#include "FanController.h"
#include "CommandHandler.h"

Sensor sensor;
FanController controller;

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

  int temp = sensor.readRaw();
  controller.update(temp);

  delay(200);
}
