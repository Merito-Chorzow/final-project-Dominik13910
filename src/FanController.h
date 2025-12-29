#pragma once

enum class State {
  INIT,
  IDLE,
  RUN,
  FAULT
};

class FanController {
public:
  void init();
  void update(int tempRaw);
  State getState() const;

private:
  State state = State::INIT;
  int lastPwm = 0;
};
