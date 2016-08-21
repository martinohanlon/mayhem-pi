#ifndef __VAISSEAU_GFX_H__
#define __VAISSEAU_GFX_H__

#include <allegro5/allegro.h>

struct vaisseau_gfx {
  ALLEGRO_BITMAP *sprite;
  ALLEGRO_BITMAP *sprite_thrust;
  ALLEGRO_BITMAP *sprite_thrust2;
  ALLEGRO_BITMAP *sprite_shield;
};

bool init_vaisseau_gfx_from_file(struct vaisseau_gfx *vaisseau, char *normal,
                                 char *thrust, char *thrust2, char *shield);
void cleanup_vaisseau_gfx(struct vaisseau_gfx *vaisseau);
int init_sprite_explosion(char *bmpname);
ALLEGRO_BITMAP *get_sprite_explosion();
void cleanup_sprite_explosion();
ALLEGRO_BITMAP *get_sprite_explosion_frame(int i);
#endif
