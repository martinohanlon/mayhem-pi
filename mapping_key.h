#ifndef __MAPPING_ALLEGRO_KEY_H_
#define __MAPPING_ALLEGRO_KEY_H_

#include "vaisseau_data.h"

struct mapping_key {
  int left, right, thrust, shield, fire;
  static int key_sets[4][5];
};

void init_mapping_key(struct mapping_key *keymap, int keysetno);

const char *key_to_str(int key);

#endif
