#ifndef __UTILS_H__
#define __UTILS_H__

#include <allegro5/allegro.h>

ALLEGRO_BITMAP* create_clear_bitmap(int w,int h);
int create_sprite_buffer_screen();
ALLEGRO_BITMAP* sprite_buffer_screen();
void clean_sprite_buffer_screen();

#endif
