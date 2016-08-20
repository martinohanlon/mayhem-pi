#ifndef MAPPING_JOY_H
#define MAPPING_JOY_H

#include "xc.h"

enum class JoyButton {
  LEFT_STICK_X_LEFT,
  LEFT_STICK_X_RIGHT,
  LEFT_STICK_Y_UP,
  LEFT_STICK_Y_DOWN,
  LEFT_TRIGGER,
  RIGHT_STICK_X_LEFT,
  RIGHT_STICK_X_RIGHT,
  RIGHT_STICK_Y_UP,
  RIGHT_STICK_Y_DOWN,
  RIGHT_TRIGGER,
  DPAD_X_LEFT,
  DPAD_X_RIGHT,
  DPAD_Y_UP,
  DPAD_Y_DOWN,
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  BUTTON_LEFT_STICK,
  BUTTON_RIGHT_STICK,
  BUTTON_LEFT_SHOULDER,
  BUTTON_RIGHT_SHOULDER,
  BUTTON_START,
  BUTTON_BACK,
  BUTTON_XBOX
};

struct mapping_joy {
  JoyButton left = JoyButton::LEFT_STICK_X_LEFT;
  JoyButton right = JoyButton::LEFT_STICK_X_RIGHT;
  JoyButton thrust = JoyButton::BUTTON_A;
  JoyButton shield = JoyButton::BUTTON_B;
  JoyButton fire = JoyButton::BUTTON_RIGHT_SHOULDER;

  static JoyButton btn_sets[4][5];
};

bool is_pressed(XC_STATE *joystick, JoyButton button);

char *button_to_str(JoyButton button);

void init_mapping_joy(struct mapping_joy *joymap, int keysetno);

#endif // MAPPING_JOY_H
