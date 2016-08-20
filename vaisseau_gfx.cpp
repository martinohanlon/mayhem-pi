#include "vaisseau_gfx.h"

#include "allegro_compatibility.h"

bool init_vaisseau_gfx_from_file(struct vaisseau_gfx *vaisseau, char *normal,
                                 char *thrust, char *thrust2, char *shield) {
  vaisseau->sprite = al_load_bitmap(normal);
  al_convert_mask_to_alpha(vaisseau->sprite, al_map_rgb(0, 0, 0));
  vaisseau->sprite_shield = al_load_bitmap(shield);
  al_convert_mask_to_alpha(vaisseau->sprite_shield, al_map_rgb(0, 0, 0));
  vaisseau->sprite_thrust = al_load_bitmap(thrust);
  al_convert_mask_to_alpha(vaisseau->sprite_thrust, al_map_rgb(0, 0, 0));
  vaisseau->sprite_thrust2 = al_load_bitmap(thrust2);
  al_convert_mask_to_alpha(vaisseau->sprite_thrust2, al_map_rgb(0, 0, 0));
  return !(vaisseau->sprite && vaisseau->sprite_shield &&
           vaisseau->sprite_thrust && vaisseau->sprite_thrust2);
}

void cleanup_vaisseau_gfx(struct vaisseau_gfx *vaisseau) {
  if (vaisseau->sprite)
    al_destroy_bitmap(vaisseau->sprite);
  if (vaisseau->sprite_shield)
    al_destroy_bitmap(vaisseau->sprite_shield);
  if (vaisseau->sprite_thrust)
    al_destroy_bitmap(vaisseau->sprite_thrust);
  if (vaisseau->sprite_thrust2)
    al_destroy_bitmap(vaisseau->sprite_thrust2);
}

ALLEGRO_BITMAP *sprite_explode;
ALLEGRO_BITMAP *sprite_explosion_frames[24];

int init_sprite_explosion(char *bmpname) {
  sprite_explode = al_load_bitmap(bmpname);
  int i;
  for (i = 0; i < 24; i++) {
    sprite_explosion_frames[i] = al_create_bitmap(32, 32);
    blit(sprite_explode, sprite_explosion_frames[i], 32 * i, 0, 0, 0, 32, 32);

    al_convert_mask_to_alpha(sprite_explosion_frames[i], al_map_rgb(0, 0, 0));
  }

  return (!sprite_explode);
}

void cleanup_sprite_explosion() {
  int i;
  for (i = 0; i < 24; i++)
    al_destroy_bitmap(sprite_explosion_frames[i]);
  al_destroy_bitmap(sprite_explode);
}

ALLEGRO_BITMAP *get_sprite_explosion() { return sprite_explode; }

ALLEGRO_BITMAP *get_sprite_explosion_frame(int i) {
  return sprite_explosion_frames[i / 2];
}
