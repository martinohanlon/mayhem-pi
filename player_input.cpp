#include "player_input.h"

#include "allegro_compatibility.h"

void get_control_input(int nbplayers, struct command* cmds, bool key_down[])
{
//#FIXME	if (num_joysticks) poll_joystick();
	
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
	struct mapping_joy* joymap = cmd->joymap;
	cmd->left = *joymap->left;
	cmd->right = *joymap->right;
	cmd->shield = *joymap->shield;
	cmd->fire = *joymap->fire;
	cmd->thrust = *joymap->thrust;
}
