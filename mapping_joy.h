#ifndef __MAPPING_JOY_H_
#define __MAPPING_JOY_H_

#include "vaisseau_data.h"

struct mapping_joy {
	int *left, *right, *thrust, *shield, *fire;
};

void init_mapping_joy(struct mapping_joy* joymap, int *joy_sets[][5], int joyno);

#endif
