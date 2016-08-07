#include "player_input.h"
#include "mapping_joy.h"

#include "allegro_compatibility.h"
#include "game_mgr.h"

void get_control_input(int nbplayers, struct command* cmds, bool key_down[])
{
	for (int player = 0; player < nbplayers; player++)
	{
        if (cmds[player].control_type == CONTROL_KEY) get_key_input(&cmds[player], key_down);
		if (cmds[player].control_type == CONTROL_JOY) get_joy_input(&cmds[player]);
	}	
}

void get_key_input(struct command *cmd, bool key_down[])
{
	struct mapping_key* keymap = cmd->keymap;
    cmd->left = key_down[keymap->left];
    cmd->right = key_down[keymap->right];
    cmd->shield = key_down[keymap->shield];
    cmd->fire = key_down[keymap->fire];
    cmd->thrust = key_down[keymap->thrust];
}

void get_joy_input(struct command *cmd)
{
	auto joystick = GameManager::joysticks[cmd->joystick_index];
	struct mapping_joy* joymap = cmd->joymap;
	cmd->left   = is_pressed(joystick, joymap->left);
	cmd->right  = is_pressed(joystick, joymap->right);
	cmd->shield = is_pressed(joystick, joymap->shield);
	cmd->fire   = is_pressed(joystick, joymap->fire);
	cmd->thrust = is_pressed(joystick, joymap->thrust);
}

const char* get_control_id_as_string(enum CONTROL_ID cid)
{
  switch (cid) {
  case KEYBOARD_0: return "Kbd Layout 1";
  case KEYBOARD_1: return "Kbd Layout 2";
  case KEYBOARD_2: return "Kbd Layout 3";
  case KEYBOARD_3: return "Kbd Layout 4";
  case JOYSTICK_0: return "Joystick 1";
  case JOYSTICK_1: return "Joystick 2";
  case JOYSTICK_2: return "Joystick 3";
  case JOYSTICK_3: return "Joystick 4";
    default:
    return "INVALID";
    }
}
