#include "mapping_key.h"

int key_sets[4][5] = { {KEY_Z,KEY_X,KEY_V,KEY_C,KEY_G},
                       {KEY_LEFT,KEY_RIGHT,KEY_DEL_PAD,KEY_0_PAD,KEY_ENTER_PAD},
                       {KEY_B,KEY_N,KEY_COMMA,KEY_M,KEY_L},
                       {KEY_Y,KEY_U,KEY_O,KEY_I,KEY_0} };

void init_mapping_key(struct mapping_key* keymap, int keysetno)
{
		keymap->left = key_sets[keysetno][0];
    keymap->right = key_sets[keysetno][1];
    keymap->thrust = key_sets[keysetno][2];
		keymap->shield = key_sets[keysetno][3];
    keymap->fire = key_sets[keysetno][4];
}