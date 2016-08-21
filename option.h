#ifndef __OPTION_H__
#define __OPTION_H__

#include "platform_data.h"
#include "player_view.h"
#include "vaisseau_data.h"
#include <allegro5/allegro.h>

// types of option
#define NB_OPT_TYPE 5
#define OPT_NOOPTION 0
#define OPT_MAXFUEL 1
#define OPT_SLOWSHIELD 2
#define OPT_BACKSHOT 3
#define OPT_TRIPLESHOT 4
#define OPT_THRUST 5

// option values
#define OPT_SLOWSHIELD_SPEED 1
#define OPT_THRUST_MAX 0.47

struct option_sprite {
  char *sprite_name;
  ALLEGRO_BITMAP *sprite;
  //    PALETTE sprite_colors;
};

struct option_data {
  int x, y;
  int type;
  double time_in;
  bool active;
  double active_time;
  double explode_appear_time;
  double player_expire_time;
  struct option_sprite *option_sprites;
};

void unload_option(struct option_data *opt);
int init_option_data(struct option_data *opt,
                     struct option_sprite *option_sprites,
                     double explode_appear_time, double active_time,
                     double player_expire_time);
void gestion_option(struct option_data *opt, struct level_data *currentlevel,
                    struct vaisseau_data *allv, struct player_view *views,
                    int nbplayers, int nbviews, double dt);

#endif
