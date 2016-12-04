#ifndef __PLATFORM_DATA__
#define __PLATFORM_DATA__
#include "vaisseau_data.h"
#include <allegro5/allegro.h>

#define USE_DCA 0
#define NB_DCA 2
#define MAX_DCA_TIR 3

struct dca_data {
  int xsrc, ysrc;
  int area;
  int delayed;
  int delay;
  bool shoot;
  struct tir_data dca_tir[MAX_DCA_TIR];
};

struct platform_data {
  int xmin, xmax;
  int yflat;
};

// edges of the map, where the ships will warp to the opposite edge
struct edge_data {
  int leftx, rightx;
  int topy, bottomy;
  bool wrapx, wrapy;
};

// CHANGE THESE TO BE SHIP ASSETS, which would include wavs
struct level_ship_assets {
  const char *normalsprite;
  const char *thrustsprite;
  const char *thrust2sprite;
  const char *shieldsprite;
  const char *boomwav;
  const char *refuelloopwav;
  const char *shieldloopwav;
  const char *thrustloopwav;
  const char *reboundwav;
  const char *shootwav;
};

struct level_data {
  const char *bmpname;
  const char *mini_bmpname;
  const char *collision_bmpname;
  ALLEGRO_BITMAP *bitmap;
  // PALETTE colormap;
  ALLEGRO_BITMAP *level_buffer;
  ALLEGRO_BITMAP *mini_bitmap;
  // PALETTE mini_colormap;
  ALLEGRO_BITMAP *collision_bitmap;
  collision_map coll_map;
  // PALETTE collision_colormap;
  ALLEGRO_BITMAP *mini_bitmap_buffer;
  struct platform_data *platformdata;
  int nbplatforms;
  struct dca_data alldca[NB_DCA];
  bool use_dca;
  bool wall_collision;
  struct edge_data edgedata;
  struct level_ship_assets *shipsassets;
  const char *explosion_spritename;
  int *particle_color_rgb;
  ALLEGRO_COLOR particle_color;
};

void init_level_dca(struct dca_data *dca, int xsrc, int ysrc, int area,
                    int delay);
void init_level_data(struct level_data *leveldat, const char *bmpname,
                     const char *mini_bmpname, const char *collision_bmpname,
                     struct platform_data *platformdata, int nbplatforms,
                     struct edge_data edgedata,
                     struct level_ship_assets *shipsassets,
                     const char *explosion_spritename, bool use_dca,
                     bool wall_collision, int *particle_color_rgb);
int load_level(struct level_data *leveldat, int largeur, int hauteur);
void unload_level(struct level_data *leveldat);
#endif
