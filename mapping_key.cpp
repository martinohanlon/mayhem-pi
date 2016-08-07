#include "mapping_key.h"

#include <cstdio>
int mapping_key::key_sets[4][5] = { {ALLEGRO_KEY_Z,ALLEGRO_KEY_X,ALLEGRO_KEY_V,ALLEGRO_KEY_C,ALLEGRO_KEY_G},
                       {ALLEGRO_KEY_LEFT,ALLEGRO_KEY_RIGHT,ALLEGRO_KEY_PAD_DELETE,ALLEGRO_KEY_PAD_0,ALLEGRO_KEY_PAD_ENTER},
                       {ALLEGRO_KEY_B,ALLEGRO_KEY_N,ALLEGRO_KEY_COMMA,ALLEGRO_KEY_M,ALLEGRO_KEY_L},
                       {ALLEGRO_KEY_Y,ALLEGRO_KEY_U,ALLEGRO_KEY_O,ALLEGRO_KEY_I,ALLEGRO_KEY_0} };

void init_mapping_key(struct mapping_key* keymap, int keysetno)
{
    keymap->left   = mapping_key::key_sets[keysetno][0];
    keymap->right  = mapping_key::key_sets[keysetno][1];
    keymap->thrust = mapping_key::key_sets[keysetno][2];
    keymap->shield = mapping_key::key_sets[keysetno][3];
    keymap->fire   = mapping_key::key_sets[keysetno][4];
}

char* key_to_str(int key) {
  switch(key) {
    case ALLEGRO_KEY_Z          : return("Z");
    case ALLEGRO_KEY_X          : return("X");
    case ALLEGRO_KEY_V          : return("V");
    case ALLEGRO_KEY_C          : return("C");
    case ALLEGRO_KEY_G          : return("G");
    case ALLEGRO_KEY_LEFT       : return("Left");
    case ALLEGRO_KEY_RIGHT      : return("Right");
    case ALLEGRO_KEY_PAD_DELETE : return("Keypad Del");
    case ALLEGRO_KEY_PAD_0      : return("Keypad 0");
    case ALLEGRO_KEY_PAD_ENTER  : return("Keypad Enter");
    case ALLEGRO_KEY_B          : return("B");
    case ALLEGRO_KEY_N          : return("N");
    case ALLEGRO_KEY_COMMA      : return(",");
    case ALLEGRO_KEY_M          : return("M");
    case ALLEGRO_KEY_L          : return("L");
    case ALLEGRO_KEY_Y          : return("Y");
    case ALLEGRO_KEY_U          : return("U");
    case ALLEGRO_KEY_O          : return("O");
    case ALLEGRO_KEY_I          : return("I");
    case ALLEGRO_KEY_0          : return("0");
    default: return("?");
    }
}
