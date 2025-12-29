#pragma once

class Sensor {
public:
  void init();
  int readRaw() const;
};
