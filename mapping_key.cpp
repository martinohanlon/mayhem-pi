#include "mapping_key.h"

#include <cstdio>
int mapping_key::key_sets[4][5] = {
    {ALLEGRO_KEY_Z, ALLEGRO_KEY_X, ALLEGRO_KEY_V, ALLEGRO_KEY_C, ALLEGRO_KEY_G},
    {ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_PAD_DELETE,
     ALLEGRO_KEY_PAD_0, ALLEGRO_KEY_PAD_ENTER},
    {ALLEGRO_KEY_B, ALLEGRO_KEY_N, ALLEGRO_KEY_COMMA, ALLEGRO_KEY_M,
     ALLEGRO_KEY_L},
    {ALLEGRO_KEY_Y, ALLEGRO_KEY_U, ALLEGRO_KEY_O, ALLEGRO_KEY_I,
     ALLEGRO_KEY_0}};

void init_mapping_key(struct mapping_key *keymap, int keysetno) {
  keymap->left = mapping_key::key_sets[keysetno][0];
  keymap->right = mapping_key::key_sets[keysetno][1];
  keymap->thrust = mapping_key::key_sets[keysetno][2];
  keymap->shield = mapping_key::key_sets[keysetno][3];
  keymap->fire = mapping_key::key_sets[keysetno][4];
}

char *key_to_str(int key) {
  switch (key) {
  case ALLEGRO_KEY_A:
    return ("A");
  case ALLEGRO_KEY_B:
    return ("B");
  case ALLEGRO_KEY_C:
    return ("C");
  case ALLEGRO_KEY_D:
    return ("D");
  case ALLEGRO_KEY_E:
    return ("E");
  case ALLEGRO_KEY_F:
    return ("F");
  case ALLEGRO_KEY_G:
    return ("G");
  case ALLEGRO_KEY_H:
    return ("H");
  case ALLEGRO_KEY_I:
    return ("I");
  case ALLEGRO_KEY_J:
    return ("J");
  case ALLEGRO_KEY_K:
    return ("K");
  case ALLEGRO_KEY_L:
    return ("L");
  case ALLEGRO_KEY_M:
    return ("M");
  case ALLEGRO_KEY_N:
    return ("N");
  case ALLEGRO_KEY_O:
    return ("O");
  case ALLEGRO_KEY_P:
    return ("P");
  case ALLEGRO_KEY_Q:
    return ("Q");
  case ALLEGRO_KEY_R:
    return ("R");
  case ALLEGRO_KEY_S:
    return ("S");
  case ALLEGRO_KEY_T:
    return ("T");
  case ALLEGRO_KEY_U:
    return ("U");
  case ALLEGRO_KEY_V:
    return ("V");
  case ALLEGRO_KEY_W:
    return ("W");
  case ALLEGRO_KEY_X:
    return ("X");
  case ALLEGRO_KEY_Y:
    return ("Y");
  case ALLEGRO_KEY_Z:
    return ("Z");

  case ALLEGRO_KEY_0:
    return ("0");
  case ALLEGRO_KEY_1:
    return ("1");
  case ALLEGRO_KEY_2:
    return ("2");
  case ALLEGRO_KEY_3:
    return ("3");
  case ALLEGRO_KEY_4:
    return ("4");
  case ALLEGRO_KEY_5:
    return ("5");
  case ALLEGRO_KEY_6:
    return ("6");
  case ALLEGRO_KEY_7:
    return ("7");
  case ALLEGRO_KEY_8:
    return ("8");
  case ALLEGRO_KEY_9:
    return ("9");

  case ALLEGRO_KEY_PAD_0:
    return ("Keypad 0");
  case ALLEGRO_KEY_PAD_1:
    return ("Keypad 1");
  case ALLEGRO_KEY_PAD_2:
    return ("Keypad 2");
  case ALLEGRO_KEY_PAD_3:
    return ("Keypad 3");
  case ALLEGRO_KEY_PAD_4:
    return ("Keypad 4");
  case ALLEGRO_KEY_PAD_5:
    return ("Keypad 5");
  case ALLEGRO_KEY_PAD_6:
    return ("Keypad 6");
  case ALLEGRO_KEY_PAD_7:
    return ("Keypad 7");
  case ALLEGRO_KEY_PAD_8:
    return ("Keypad 8");
  case ALLEGRO_KEY_PAD_9:
    return ("Keypad 9");

  case ALLEGRO_KEY_F1:
    return ("F1");
  case ALLEGRO_KEY_F2:
    return ("F2");
  case ALLEGRO_KEY_F3:
    return ("F3");
  case ALLEGRO_KEY_F4:
    return ("F4");
  case ALLEGRO_KEY_F5:
    return ("F5");
  case ALLEGRO_KEY_F6:
    return ("F6");
  case ALLEGRO_KEY_F7:
    return ("F7");
  case ALLEGRO_KEY_F8:
    return ("F8");
  case ALLEGRO_KEY_F9:
    return ("F9");
  case ALLEGRO_KEY_F10:
    return ("F10");
  case ALLEGRO_KEY_F11:
    return ("F11");
  case ALLEGRO_KEY_F12:
    return ("F12");

  case ALLEGRO_KEY_LSHIFT:
    return ("LShift");
  case ALLEGRO_KEY_RSHIFT:
    return ("RShift");
  case ALLEGRO_KEY_LCTRL:
    return ("LCtrl");
  case ALLEGRO_KEY_RCTRL:
    return ("RCtrl");
  case ALLEGRO_KEY_ALT:
    return ("Alt");
  case ALLEGRO_KEY_ALTGR:
    return ("AltGr");
  case ALLEGRO_KEY_LWIN:
    return ("LWin");
  case ALLEGRO_KEY_RWIN:
    return ("RWin");
  case ALLEGRO_KEY_MENU:
    return ("Menu");
  case ALLEGRO_KEY_SCROLLLOCK:
    return ("Scrollock");
  case ALLEGRO_KEY_NUMLOCK:
    return ("Numlock");
  case ALLEGRO_KEY_CAPSLOCK:
    return ("Capslock");

  case ALLEGRO_KEY_ESCAPE:
    return ("");
  case ALLEGRO_KEY_TILDE:
    return ("~");
  case ALLEGRO_KEY_MINUS:
    return ("-");
  case ALLEGRO_KEY_EQUALS:
    return ("=");
  case ALLEGRO_KEY_BACKSPACE:
    return ("Backspace");
  case ALLEGRO_KEY_TAB:
    return ("Tab");
  case ALLEGRO_KEY_OPENBRACE:
    return ("[");
  case ALLEGRO_KEY_CLOSEBRACE:
    return ("]");
  case ALLEGRO_KEY_ENTER:
    return ("Enter");
  case ALLEGRO_KEY_SEMICOLON:
    return (";");
  case ALLEGRO_KEY_QUOTE:
    return ("\"");
  case ALLEGRO_KEY_BACKSLASH:
    return ("\\");
  case ALLEGRO_KEY_BACKSLASH2:
    return ("\\");
  case ALLEGRO_KEY_COMMA:
    return (",");
  case ALLEGRO_KEY_FULLSTOP:
    return (".");
  case ALLEGRO_KEY_SLASH:
    return ("/");
  case ALLEGRO_KEY_SPACE:
    return ("Space");

  case ALLEGRO_KEY_INSERT:
    return ("Insert");
  case ALLEGRO_KEY_DELETE:
    return ("Delete");
  case ALLEGRO_KEY_HOME:
    return ("Home");
  case ALLEGRO_KEY_END:
    return ("End");
  case ALLEGRO_KEY_PGUP:
    return ("PgUp");
  case ALLEGRO_KEY_PGDN:
    return ("PgDn");
  case ALLEGRO_KEY_LEFT:
    return ("Left");
  case ALLEGRO_KEY_RIGHT:
    return ("Right");
  case ALLEGRO_KEY_UP:
    return ("Up");
  case ALLEGRO_KEY_DOWN:
    return ("Down");

  case ALLEGRO_KEY_PAD_SLASH:
    return ("Keypad /");
  case ALLEGRO_KEY_PAD_ASTERISK:
    return ("Keypad *");
  case ALLEGRO_KEY_PAD_MINUS:
    return ("Keypad -");
  case ALLEGRO_KEY_PAD_PLUS:
    return ("Keypad +");
  case ALLEGRO_KEY_PAD_DELETE:
    return ("Keypad Del");
  case ALLEGRO_KEY_PAD_ENTER:
    return ("Keypad Enter");
  default:
    return ("???");
  }
}
