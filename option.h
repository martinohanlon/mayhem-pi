#ifndef __OPTION_H__
#define __OPTION_H__

#include <allegro.h>
#include "player_view.h"
#include "vaisseau_data.h"
#include "platform_data.h"


#define  NB_OPT_TYPE 4
#define  OPT_NOOPTION 0
#define  OPT_MAXFUEL 1
#define  OPT_SLOWSHIELD 2
#define  OPT_BACKSHOT 3
#define  OPT_TRIPLESHOT 4

struct option_data {
   int    x, y;
   int    type;
   int    time_in;
   int    time_out;
   bool   active;
   int    active_time;
   int    explode_appear_time;
   int    player_expire_time;
   BITMAP *option_sprite;
   PALETTE option_sprite_colors;
};

void unload_option(struct option_data *opt);
int init_option_data(struct option_data *opt, char *option_sprite_name, int explode_appear_time, int active_time, int player_expire_time);
void gestion_option(struct option_data *opt, struct level_data *currentlevel,struct vaisseau_data *allv, struct player_view *views, int nbplayers, int nbviews);

#endif
