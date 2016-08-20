#include "option.h"
#include "allegro_compatibility.h"

#include <stdio.h>

void option_time(struct option_data *opt, double dt) {
  if (opt->active) {
    if (opt->time_in > opt->active_time) {
      opt->active = false;
      opt->time_in = 0;
    } else
      opt->time_in += dt;
  }
}

bool test_pos_option(struct option_data *opt, int opt_type,
                     struct level_data *currentlevel, int x, int y) {
  unsigned long address_bmp;
  unsigned char pixelcolor;

  // bmp_select(currentlevel->collision_bitmap);
  int ligne;

  auto height = al_get_bitmap_height(opt->option_sprites[opt_type - 1].sprite);
  auto width = al_get_bitmap_width(opt->option_sprites[opt_type - 1].sprite);

  for (ligne = 0; ligne < height; ligne++) {
    for (int colonne = 0; colonne < width; colonne++) {
      auto pixel =
          get_pixel(currentlevel->collision_bitmap, colonne + x, ligne + y);

      if (is_nonblack_pixel(pixel))
        return false;
    }
  }

  return (true);
}

void init_option(struct option_data *opt, struct level_data *currentlevel,
                 struct vaisseau_data *allv, int nombre_vaisseau) {
  // make sure the option isn't already active
  if (!opt->active) {
    // has a ship exploded?
    for (int i = 0; i < nombre_vaisseau; i++) {
      // is it at explode_count 100
      if (!allv[i].explode_appear_time_passed &&
          allv[i].explode_count >= opt->explode_appear_time) {
        int x, y;
        int opt_type = rand() % NB_OPT_TYPE + 1;
        x = allv[i].xpos +
            (15 -
             (al_get_bitmap_width(opt->option_sprites[opt_type - 1].sprite) /
              2));
        y = allv[i].ypos +
            (15 -
             (al_get_bitmap_height(opt->option_sprites[opt_type - 1].sprite) /
              2));

        // make sure the option isnt going to collide with the background
        if (test_pos_option(opt, opt_type, currentlevel, x, y))
          opt->active = true;
        opt->x = x;
        opt->y = y;
        opt->type = opt_type;
        continue;
      }
    }
  }

  for (int i = 0; i < nombre_vaisseau; i++) {
    allv[i].explode_appear_time_passed =
        allv[i].explode_count >= opt->explode_appear_time;
  }
}

void attrib_option(struct option_data *opt, struct vaisseau_data *allv,
                   int test) {
  struct vaisseau_data *v;
  if (test != -1) {
    v = &allv[test];

    // give the ship the option
    v->option_type = opt->type;
    v->option_expire_time = opt->player_expire_time;

    if (opt->type == OPT_MAXFUEL)
      v->fuel = v->max_fuel;

    if (opt->type == OPT_SLOWSHIELD) {
      v->speed_shield_force_down = OPT_SLOWSHIELD_SPEED;
    }

    if (opt->type == OPT_THRUST) {
      v->thrust_max = ftofix(OPT_THRUST_MAX);
    }

    opt->active = false;
    opt->time_in = 0;
  }
}

void gestion_player_options(struct option_data *opt, struct vaisseau_data *allv,
                            int nbplayers, double dt) {
  struct vaisseau_data *v;
  for (int i = 0; i < nbplayers; i++) {
    v = &allv[i];

    // expire the players option
    if (v->option_type != OPT_NOOPTION) {
      // has the players option expired?
      if (v->option_expire_time <= 0) {
        // reset the players option
        if (v->option_type == OPT_SLOWSHIELD)
          v->speed_shield_force_down = VAISSEAU_SPEED_SHIELD_FORCE_DOWN;
        if (v->option_type == OPT_THRUST)
          v->thrust_max = ftofix(VAISSEAU_THRUST_MAX);

        v->option_type = OPT_NOOPTION;
      } else
        v->option_expire_time -= dt;
    }

    // has this player taken the option?
    if (!v->explode && opt->active)
      if (abs((v->xpos + 16) - (opt->x + 6)) <= (26 + 12) / 2 &&
          abs((v->ypos + 16) - (opt->y + 6)) <= (28 + 12) / 2)
        attrib_option(opt, allv, i);
  }
}

void draw_option(struct option_data *opt, struct level_data *currentlevel) {
  if (opt->active) {
    draw_sprite(currentlevel->level_buffer,
                opt->option_sprites[opt->type - 1].sprite, opt->x, opt->y);
  }
}

void gestion_option(struct option_data *opt, struct level_data *currentlevel,
                    struct vaisseau_data *allv, struct player_view *views,
                    int nbplayers, int nbviews, double dt) {
  option_time(opt, dt); // alternance option active ou pas

  init_option(opt, currentlevel, allv,
              nbplayers); // init la pos + type de l'option

  gestion_player_options(opt, allv, nbplayers, dt);
  draw_option(opt, currentlevel); // affiche sprite option
}

int init_option_data(struct option_data *opt,
                     struct option_sprite *option_sprites,
                     double explode_appear_time, double active_time,
                     double player_expire_time) {
  srand(time(NULL));

  opt->active = false;
  opt->time_in = 0;
  opt->type = 0;
  opt->x = 0;
  opt->y = 0;
  opt->active_time = active_time;
  opt->explode_appear_time = explode_appear_time;
  opt->player_expire_time = player_expire_time;

  // load the sprites
  opt->option_sprites = option_sprites;
  for (int optioncount = 0; optioncount < NB_OPT_TYPE; optioncount++) {
    opt->option_sprites[optioncount].sprite =
        al_load_bitmap(opt->option_sprites[optioncount].sprite_name);
    al_convert_mask_to_alpha(opt->option_sprites[optioncount].sprite,
                             al_map_rgb(0, 0, 0));
  }

  return (0);
}

void unload_option(struct option_data *opt) {
  for (int optioncount = 0; optioncount < NB_OPT_TYPE; optioncount++) {
    al_destroy_bitmap(opt->option_sprites[optioncount].sprite);
  }
}
