#include "utils.h"

ALLEGRO_BITMAP* create_clear_bitmap(int w,int h)
	{
	ALLEGRO_BITMAP *buffer;
    buffer = al_create_bitmap(w, h);     // place pour big image de fond
    //#FIXME al_clear_bitmap(buffer);   // Nettoyage
	return buffer;
	}

int __assert_success(int error,char *info)
  {
#if 0
	if (error)                                  // 
	{  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);          //
		 allegro_message(info);                     //
	}
#endif
	return error;
  }

ALLEGRO_BITMAP * screen_sprite_buffer=NULL;

int create_sprite_buffer_screen()
{
  screen_sprite_buffer = create_clear_bitmap(32, 32);                // create ALLEGRO_BITMAP pour le petit buffer
  return !screen_sprite_buffer;
}

ALLEGRO_BITMAP* sprite_buffer_screen()
{
	return screen_sprite_buffer;
}

void clean_sprite_buffer_screen()
{
//#FIXME	if (screen_sprite_buffer) destroy_bitmap(screen_sprite_buffer);
}
