#include "mapping_key.h"

int key_sets[4][5] = { {ALLEGRO_KEY_Z,ALLEGRO_KEY_X,ALLEGRO_KEY_V,ALLEGRO_KEY_C,ALLEGRO_KEY_G},
                       {ALLEGRO_KEY_LEFT,ALLEGRO_KEY_RIGHT,ALLEGRO_KEY_PAD_DELETE,ALLEGRO_KEY_PAD_0,ALLEGRO_KEY_PAD_ENTER},
                       {ALLEGRO_KEY_B,ALLEGRO_KEY_N,ALLEGRO_KEY_COMMA,ALLEGRO_KEY_M,ALLEGRO_KEY_L},
                       {ALLEGRO_KEY_Y,ALLEGRO_KEY_U,ALLEGRO_KEY_O,ALLEGRO_KEY_I,ALLEGRO_KEY_0} };

void init_mapping_key(struct mapping_key* keymap, int keysetno)
{
		keymap->left = key_sets[keysetno][0];
    keymap->right = key_sets[keysetno][1];
    keymap->thrust = key_sets[keysetno][2];
		keymap->shield = key_sets[keysetno][3];
    keymap->fire = key_sets[keysetno][4];
}
