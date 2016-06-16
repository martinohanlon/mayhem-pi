#include "mapping_joy.h"

void init_mapping_joy(struct mapping_joy* joymap, int *joy_sets[][5], int joyno)
{
    joymap->left = joy_sets[joyno][0];
    joymap->right = joy_sets[joyno][1];
    joymap->thrust = joy_sets[joyno][2];
    joymap->shield = joy_sets[joyno][3];
    joymap->fire = joy_sets[joyno][4];
    
}