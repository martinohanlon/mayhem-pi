#include "player_input.h"

void get_control_input(int nbplayers, struct command* cmds)
{
	if (num_joysticks) poll_joystick();
	
	for (int player = 0; player < nbplayers; player++)
	{
		if (cmds[player].control_type == CONTROL_KEY) get_key_input(&cmds[player]);
		if (cmds[player].control_type == CONTROL_JOY) get_joy_input(&cmds[player]);
	}	
}

void get_key_input(struct command *cmd)
{
	struct mapping_key* keymap = cmd->keymap;
	cmd->left = key[keymap->left];
	cmd->right = key[keymap->right];
	cmd->shield = key[keymap->shield];
	cmd->fire = key[keymap->fire];
	cmd->thrust = key[keymap->thrust];
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