#ifndef __COMMAND_H_
#define __COMMAND_H_

#include "mapping_key.h"

#define CONTROL_KEY 1
#define CONTROL_JOY 2

struct vaisseau_data;

struct command {
  bool left;
  bool right;
  bool fire;
  bool shield;
  bool thrust;
  struct vaisseau_data *controlled_ship;
  int control_type;
  struct mapping_key *keymap;
  struct mapping_joy *joymap;
  int joystick_index;
};

void handle_command(struct command *cmd, double dt);

#endif
