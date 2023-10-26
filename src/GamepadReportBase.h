#pragma once

#include "Arduino.h"

namespace GamepadControllerESP32 {

struct ReportBeforeUnion {
  // InfoSelect select;
  // InfoPower power;
  // uint8_t timeActive;
  // uint8_t timeSilent;
  // uint8_t countRepeat;
};

class ReportBase {
 public:
  static const size_t arr8tLen = 8;   // default 8
  union {
    ReportBeforeUnion v;
    uint8_t arr8t[arr8tLen];
  };

  virtual ~ReportBase() {};

  virtual void setFullPowerFor1Sec() = 0;
  virtual void setAllOff() = 0;
};

};  // namespace GamepadControllerESP32
