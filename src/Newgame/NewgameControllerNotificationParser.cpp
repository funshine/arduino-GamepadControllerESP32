#include "NewgameControllerNotificationParser.h"

#define NEWGAME_CONTROLLER_INDEX_BUTTONS_DIR 4
#define NEWGAME_CONTROLLER_INDEX_BUTTONS_MAIN 5
#define NEWGAME_CONTROLLER_INDEX_BUTTONS_CENTER 6
#define NEWGAME_CONTROLLER_INDEX_BUTTONS_SHARE 6

namespace GamepadControllerESP32 {

NewgameControllerNotificationParser::NewgameControllerNotificationParser() {
  btnA = btnB = btnX = btnY = false;
  btnShare = btnStart = btnSelect = btnHome = false;
  btnLB = btnRB = btnLS = btnRS = false;
  btnDirUp = btnDirLeft = btnDirRight = btnDirDown = false;
  joyLHori = joyLVert = joyRHori = joyRVert = maxJoy / 2;
  trigLT = trigRT = 0;
}

uint8_t NewgameControllerNotificationParser::update(uint8_t* data, size_t length) {
  if (length != expectedDataLen) {
    return GAMEPAD_CONTROLLER_ERROR_INVALID_LENGTH;
  }
  uint8_t btnBits;
  btnBits = data[NEWGAME_CONTROLLER_INDEX_BUTTONS_MAIN];
  btnA = btnBits & 0b00000001;
  btnB = btnBits & 0b00000010;
  btnX = btnBits & 0b00001000;
  btnY = btnBits & 0b00010000;
  btnLB = btnBits & 0b01000000;
  btnRB = btnBits & 0b10000000;

  btnBits = data[NEWGAME_CONTROLLER_INDEX_BUTTONS_CENTER];
  // btnSelect = btnBits & 0b00000100;
  btnStart = btnBits & 0b00001000;
  // btnHome = btnBits & 0b00010000;
  btnLS = btnBits & 0b00000001;
  btnRS = btnBits & 0b00000010;

  btnBits = data[NEWGAME_CONTROLLER_INDEX_BUTTONS_SHARE];
  // btnShare = btnBits & 0b00000001;

  btnBits = data[NEWGAME_CONTROLLER_INDEX_BUTTONS_DIR];
  btnDirUp = (btnBits <= 1 || btnBits == 7);
  btnDirRight = (1 <= btnBits && btnBits <= 3);
  btnDirDown = (3 <= btnBits && btnBits <= 5);
  btnDirLeft = (5 <= btnBits && btnBits <= 7);

  joyLHori = data[0];
  joyLVert = data[1];
  joyRHori = data[2];
  joyRVert = data[3];
  trigLT = data[7];
  trigRT = data[8];
  return 0;
}

void NewgameControllerNotificationParser::convertU16TU8Arr(uint16_t vU16,
                                                        uint8_t* data) {
  data[0] = vU16 & 0xff;
  data[1] = vU16 >> 8;
}

uint8_t NewgameControllerNotificationParser::toArr(uint8_t* data, size_t length) {
  if (length < expectedDataLen) {
    return GAMEPAD_CONTROLLER_ERROR_INVALID_LENGTH;
  }
  // convertU16TU8Arr(joyLHori, &data[0]);
  // convertU16TU8Arr(joyLVert, &data[2]);
  // convertU16TU8Arr(joyRHori, &data[4]);
  // convertU16TU8Arr(joyRVert, &data[6]);
  // convertU16TU8Arr(trigLT, &data[8]);
  // convertU16TU8Arr(trigRT, &data[10]);
  data[0] = joyLHori;
  data[1] = joyLVert;
  data[2] = joyRHori;
  data[3] = joyRVert;
  data[7] = trigLT;
  data[8] = trigRT;
  {
    uint8_t btnBits = 0;
    if (btnA) btnBits |= 0b00000001;
    if (btnB) btnBits |= 0b00000010;
    if (btnX) btnBits |= 0b00001000;
    if (btnY) btnBits |= 0b00010000;
    if (btnLB) btnBits |= 0b01000000;
    if (btnRB) btnBits |= 0b10000000;
    data[NEWGAME_CONTROLLER_INDEX_BUTTONS_MAIN] = btnBits;
  }
  {
    uint8_t btnBits = 0;
    // if (btnSelect) btnBits |= 0b00000100;
    if (btnStart) btnBits |= 0b00001000;
    // if (btnHome) btnBits |= 0b00010000;
    if (btnLS) btnBits |= 0b00000001;
    if (btnRS) btnBits |= 0b00000010;
    data[NEWGAME_CONTROLLER_INDEX_BUTTONS_CENTER] = btnBits;
  }
  {
    uint8_t btnBits = 0;
    // if (btnShare) btnBits |= 0b00000001;
    data[NEWGAME_CONTROLLER_INDEX_BUTTONS_SHARE] = btnBits;
  }
  {
    uint8_t btnBits = 0;
    if (btnDirUp) {
      if (btnDirRight) {
        btnBits = 1;
      } else if (btnDirLeft) {
        btnBits = 7;
      } else {
        btnBits = 0;
      }
    } else if (btnDirDown) {
      if (btnDirRight) {
        btnBits = 3;
      } else if (btnDirLeft) {
        btnBits = 5;
      } else {
        btnBits = 4;
      }
    } else {
      if (btnDirRight) {
        btnBits = 2;
      } else if (btnDirLeft) {
        btnBits = 6;
      } else {
        btnBits = 0xf;
      }
    }
    data[NEWGAME_CONTROLLER_INDEX_BUTTONS_DIR] = btnBits;
  }
  return 0;
}

String NewgameControllerNotificationParser::toString() {
  // clang-format off
  String str = String("") +
    "btnY: " + String(btnY) + " " +
    "btnX: " + String(btnX) + " " +
    "btnB: " + String(btnB) + " " +
    "btnA: " + String(btnA) + " " +
    "btnLB: " + String(btnLB) + " " +
    "btnRB: " + String(btnRB) + "\n" +
    "btnSelect: " + String(btnSelect) + " " +
    "btnStart: " + String(btnStart) + " " +
    "btnHome: " + String(btnHome) + " " +
    "btnShare: " + String(btnShare) + " " +
    "btnLS: " + String(btnLS) + " " +
    "btnRS: " + String(btnRS) + "\n" +
    "btnDirUp: " + String(btnDirUp) + " " +
    "btnDirRight: " + String(btnDirRight) + " " +
    "btnDirDown: " + String(btnDirDown) + " " +
    "btnDirLeft: " + String(btnDirLeft) + "\n"
    "joyLHori: " + String(joyLHori) + "\n" +
    "joyLVert: " + String(joyLVert) + "\n" +
    "joyRHori: " + String(joyRHori) + "\n" +
    "joyRVert: " + String(joyRVert) + "\n" +
    "trigLT: " + String(trigLT) + "\n" +
    "trigRT: " + String(trigRT) + "\n";
  // clang-format on
  return str;
}

};  // namespace GamepadControllerESP32
