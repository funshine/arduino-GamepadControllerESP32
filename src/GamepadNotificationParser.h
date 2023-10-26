#pragma once

#include "Arduino.h"

#define GAMEPAD_CONTROLLER_ERROR_INVALID_LENGTH 1

namespace GamepadControllerESP32 {

class GamepadControllerNotificationParser {
 public:
  virtual ~GamepadControllerNotificationParser() {};

  bool btnA, btnB, btnX, btnY;
  bool btnShare, btnStart, btnSelect, btnHome;
  // side top button
  bool btnLB, btnRB;
  // button on joy stick
  bool btnLS, btnRS;
  bool btnDirUp, btnDirLeft, btnDirRight, btnDirDown;
  uint16_t joyLHori;
  uint16_t joyLVert;
  uint16_t joyRHori;
  uint16_t joyRVert;
  uint16_t trigLT, trigRT;

  virtual uint8_t update(uint8_t* data, size_t length) = 0;
  virtual uint8_t toArr(uint8_t* data, size_t length) = 0;
  virtual String toString() = 0;
};

};  // namespace GamepadControllerESP32
