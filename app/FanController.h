#pragma once

class FanController {
public:
  enum class State {
    INIT,
    IDLE,
    RUN,
    FAULT
  };

  void init();
  void update(int tempRaw);

  State getState() const;
  int getLastPwm() const;

private:
  State state = State::INIT;
  int lastPwm = 0;

  bool isTempValid(int tempRaw) const;
};
