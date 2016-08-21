#include "mapping_joy.h"

JoyButton mapping_joy::btn_sets[4][5] = {
    {JoyButton::LEFT_STICK_X_LEFT, JoyButton::LEFT_STICK_X_RIGHT,
     JoyButton::BUTTON_A, JoyButton::BUTTON_B,
     JoyButton::BUTTON_RIGHT_SHOULDER},
    {JoyButton::LEFT_STICK_X_LEFT, JoyButton::LEFT_STICK_X_RIGHT,
     JoyButton::BUTTON_A, JoyButton::BUTTON_B,
     JoyButton::BUTTON_RIGHT_SHOULDER},
    {JoyButton::LEFT_STICK_X_LEFT, JoyButton::LEFT_STICK_X_RIGHT,
     JoyButton::BUTTON_A, JoyButton::BUTTON_B,
     JoyButton::BUTTON_RIGHT_SHOULDER},
    {JoyButton::LEFT_STICK_X_LEFT, JoyButton::LEFT_STICK_X_RIGHT,
     JoyButton::BUTTON_A, JoyButton::BUTTON_B,
     JoyButton::BUTTON_RIGHT_SHOULDER}};

bool is_pressed(XC_STATE *joystick, JoyButton button) {

  switch (button) {
  case JoyButton::LEFT_STICK_X_LEFT:
    return (joystick->left_stick_x <= -0.6);
  case JoyButton::LEFT_STICK_X_RIGHT:
    return (joystick->left_stick_x >= 0.6);
  case JoyButton::LEFT_STICK_Y_UP:
    return (joystick->left_stick_y <= -0.6);
  case JoyButton::LEFT_STICK_Y_DOWN:
    return (joystick->left_stick_y >= 0.6);
  case JoyButton::LEFT_TRIGGER:
    return (joystick->left_trigger >= 0.6);
  case JoyButton::RIGHT_STICK_X_LEFT:
    return (joystick->right_stick_x <= -0.6);
  case JoyButton::RIGHT_STICK_X_RIGHT:
    return (joystick->right_stick_x >= 0.6);
  case JoyButton::RIGHT_STICK_Y_UP:
    return (joystick->right_stick_y <= -0.6);
  case JoyButton::RIGHT_STICK_Y_DOWN:
    return (joystick->right_stick_y >= 0.6);
  case JoyButton::RIGHT_TRIGGER:
    return (joystick->right_trigger >= 0.6);
  case JoyButton::DPAD_X_LEFT:
    return (joystick->dpad_x <= -0.6);
  case JoyButton::DPAD_X_RIGHT:
    return (joystick->dpad_x >= 0.6);
  case JoyButton::DPAD_Y_UP:
    return (joystick->dpad_y <= -0.6);
  case JoyButton::DPAD_Y_DOWN:
    return (joystick->dpad_y >= 0.6);
  case JoyButton::BUTTON_A:
    return (joystick->button_a);
  case JoyButton::BUTTON_B:
    return (joystick->button_b);
  case JoyButton::BUTTON_X:
    return (joystick->button_x);
  case JoyButton::BUTTON_Y:
    return (joystick->button_y);
  case JoyButton::BUTTON_LEFT_STICK:
    return (joystick->button_left_stick);
  case JoyButton::BUTTON_RIGHT_STICK:
    return (joystick->button_right_stick);
  case JoyButton::BUTTON_LEFT_SHOULDER:
    return (joystick->button_left_shoulder);
  case JoyButton::BUTTON_RIGHT_SHOULDER:
    return (joystick->button_right_shoulder);
  case JoyButton::BUTTON_START:
    return (joystick->button_start);
  case JoyButton::BUTTON_BACK:
    return (joystick->button_back);
  case JoyButton::BUTTON_XBOX:
    return (joystick->button_xbox);
  default:
    return false;
  }
}

char *button_to_str(JoyButton button) {
  switch (button) {
  case JoyButton::LEFT_STICK_X_LEFT:
    return ("Left Stick Left");
  case JoyButton::LEFT_STICK_X_RIGHT:
    return ("Left Stick Right");
  case JoyButton::LEFT_STICK_Y_UP:
    return ("Left Stick Up");
  case JoyButton::LEFT_STICK_Y_DOWN:
    return ("Left Stick Down");
  case JoyButton::LEFT_TRIGGER:
    return ("Left Trigger");
  case JoyButton::RIGHT_STICK_X_LEFT:
    return ("Right Stick Left");
  case JoyButton::RIGHT_STICK_X_RIGHT:
    return ("Right Stick Right");
  case JoyButton::RIGHT_STICK_Y_UP:
    return ("Right Stick Up");
  case JoyButton::RIGHT_STICK_Y_DOWN:
    return ("Right Stick Down");
  case JoyButton::RIGHT_TRIGGER:
    return ("Right Trigger");
  case JoyButton::DPAD_X_LEFT:
    return ("Dpad Left");
  case JoyButton::DPAD_X_RIGHT:
    return ("Dpad Right");
  case JoyButton::DPAD_Y_UP:
    return ("Dpad Up");
  case JoyButton::DPAD_Y_DOWN:
    return ("Dpad Down");
  case JoyButton::BUTTON_A:
    return ("A");
  case JoyButton::BUTTON_B:
    return ("B");
  case JoyButton::BUTTON_X:
    return ("X");
  case JoyButton::BUTTON_Y:
    return ("Y");
  case JoyButton::BUTTON_LEFT_STICK:
    return ("Left Stick Button");
  case JoyButton::BUTTON_RIGHT_STICK:
    return ("Right Stick Button");
  case JoyButton::BUTTON_LEFT_SHOULDER:
    return ("Left Shoulder");
  case JoyButton::BUTTON_RIGHT_SHOULDER:
    return ("Right Shoulder");
  case JoyButton::BUTTON_START:
    return ("Start");
  case JoyButton::BUTTON_BACK:
    return ("Back");
  case JoyButton::BUTTON_XBOX:
    return ("Xbox");
  default:
    return "?";
  }
}

void init_mapping_joy(struct mapping_joy *joymap, int keysetno) {
  joymap->left = mapping_joy::btn_sets[keysetno][0];
  joymap->right = mapping_joy::btn_sets[keysetno][1];
  joymap->thrust = mapping_joy::btn_sets[keysetno][2];
  joymap->shield = mapping_joy::btn_sets[keysetno][3];
  joymap->fire = mapping_joy::btn_sets[keysetno][4];
}
