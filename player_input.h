#ifndef __PLAYER_INPUT_H_
#define __PLAYER_INPUT_H_

#include "command.h"
#include "mapping_key.h"

enum CONTROL_ID {
  KEYBOARD_0 = 0,
  KEYBOARD_1 = 1,
  KEYBOARD_2 = 2,
  KEYBOARD_3 = 3,
  JOYSTICK_0 = 4,
  JOYSTICK_1 = 5,
  JOYSTICK_2 = 6,
  JOYSTICK_3 = 7,
  NUM_CONTROLS = 8
};

void get_control_input(int nbplayers, struct command *cmds, bool key_down[]);

void get_key_input(struct command *cmd, bool key_down[]);

void get_joy_input(struct command *cmd);

const char *get_control_id_as_string(enum CONTROL_ID cid);

#endif
