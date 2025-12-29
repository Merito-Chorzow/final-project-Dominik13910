#include "CommandHandler.h"
#include <Arduino.h>
#include "Config.h"

void handleCommand(const String& cmd) {

  if (cmd.startsWith("SET START ")) {
    Config::START_THRESHOLD = cmd.substring(10).toInt();
    Serial.println("OK START updated");
  }
  else if (cmd.startsWith("SET STOP ")) {
    Config::STOP_THRESHOLD = cmd.substring(9).toInt();
    Serial.println("OK STOP updated");
  }
  else if (cmd.startsWith("SET MINPWM ")) {
    Config::MIN_PWM = cmd.substring(11).toInt();
    Serial.println("OK MINPWM updated");
  }
  else if (cmd.startsWith("SET MAXPWM ")) {
    Config::MAX_PWM = cmd.substring(11).toInt();
    Serial.println("OK MAXPWM updated");
  }
  else if (cmd == "GET MAP") {
    Serial.println("=== MAP ===");
    Serial.print("START=");  Serial.println(Config::START_THRESHOLD);
    Serial.print("STOP=");   Serial.println(Config::STOP_THRESHOLD);
    Serial.print("MINPWM="); Serial.println(Config::MIN_PWM);
    Serial.print("MAXPWM="); Serial.println(Config::MAX_PWM);
  }
  else {
    Serial.println("ERR Unknown command");
  }
}
