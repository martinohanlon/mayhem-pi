#ifndef __MAPPING_KEY_H_
#define __MAPPING_KEY_H_

#include "vaisseau_data.h"

struct mapping_key {
	int left,right,thrust,shield,fire;
};

void init_mapping_key(struct mapping_key* keymap, int keysetno);

#endif
