#include "utils.h"

#include "allegro_compatibility.h"

ALLEGRO_BITMAP* create_clear_bitmap(int w,int h)
	{
	ALLEGRO_BITMAP *buffer;
    buffer = al_create_bitmap(w, h);     // place pour big image de fond
    return buffer;
	}

ALLEGRO_BITMAP * screen_sprite_buffer=NULL;

int create_sprite_buffer_screen()
{
  screen_sprite_buffer = create_memory_bitmap(32, 32);                // create ALLEGRO_BITMAP pour le petit buffer
  return !screen_sprite_buffer;
}

ALLEGRO_BITMAP* sprite_buffer_screen()
{
	return screen_sprite_buffer;
}

void clean_sprite_buffer_screen()
{
    if (screen_sprite_buffer) al_destroy_bitmap(screen_sprite_buffer);
}
