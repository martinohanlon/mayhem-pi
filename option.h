#ifndef __OPTION_H__
#define __OPTION_H__

#include <allegro.h>
#include "player_view.h"
#include "vaisseau_data.h"
#include "platform_data.h"

// types of option 
#define  NB_OPT_TYPE 5
#define  OPT_NOOPTION 0
#define  OPT_MAXFUEL 1
#define  OPT_SLOWSHIELD 2
#define  OPT_BACKSHOT 3
#define  OPT_TRIPLESHOT 4
#define  OPT_THRUST 5

// option values
#define OPT_SLOWSHIELD_SPEED 1
#define OPT_THRUST_MAX 0.47

struct option_sprite {
    char * sprite_name;
    BITMAP *sprite;
    PALETTE sprite_colors;    
};

struct option_data {
    int    x, y;
    int    type;
    int    time_in;
    int    time_out;
    bool   active;
    int    active_time;
    int    explode_appear_time;
    int    player_expire_time;
    struct option_sprite *option_sprites;
};

void unload_option(struct option_data *opt);
int init_option_data(struct option_data *opt, struct option_sprite *option_sprites, int explode_appear_time, int active_time, int player_expire_time);
void gestion_option(struct option_data *opt, struct level_data *currentlevel,struct vaisseau_data *allv, struct player_view *views, int nbplayers, int nbviews);

#endif
