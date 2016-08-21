#ifndef __PLAYER_VIEW_H__
#define __PLAYER_VIEW_H__
#include "physics.h"
#include "player_info.h"
#include <allegro5/allegro.h>

struct player_view {
  int xborder, yborder;
  int bordersize;
  int x, y;
  int w, h;
  struct player_info *player;
  ALLEGRO_BITMAP *back_map_buffer;
};

int init_player_view(struct player_view *pv, int x, int y, int w, int h,
                     struct player_info *player);
void clean_player_view(struct player_view *pv);
void draw_basic_player_view(struct player_view *v, int nbviews,
                            ALLEGRO_BITMAP *src_map);
void rotate_sprite(struct player_view *v);
void display_rotate_sprite_in_all_view(struct player_view *v,
                                       struct player_view allviews[],
                                       int nbviews);
void display_rotate_sprites(struct player_view allviews[], int nbviews,
                            struct level_data *currentlevel);

void gestion_tir(struct vaisseau_data *v, struct level_data *currentlevel,
                 double dt);
void put_big_pixel(ALLEGRO_BITMAP *bmp, int x, int y, ALLEGRO_COLOR color);
int test_place_tir(struct vaisseau_data *v);
int test_place_backtir(struct vaisseau_data *v);

void draw_explosion(struct player_info *allpi, struct platform_data *plats,
                    int nombre_vaisseau, struct level_data *currentlevel,
                    double dt);
void mega_collision_test(struct player_info *allpi, struct player_view *views,
                         struct vaisseau_data *vaisseaux,
                         struct level_data *currentlevel, int nbplayers,
                         int nombre_vaisseau);

void init_debris(struct vaisseau_data *v);
void test_collision_debris(struct vaisseau_data *v, ALLEGRO_BITMAP *src_map);
void plot_debris(struct vaisseau_data *v, const physics_constants &physics,
                 struct level_data *currentlevel);
void draw_debris(struct player_info *allpi, const physics_constants &physics,
                 int nombre_vaisseau, struct level_data *currentlevel,
                 double dt);

void gestion_minimap(struct vaisseau_data *vaisseaux,
                     struct level_data *currentlevel, int nbplayers,
                     int largeur, int hauteur);

int test_place_dca_tir(struct dca_data *dca);
void gestion_dca(struct dca_data *dca, struct vaisseau_data *v,
                 struct level_data *currentlevel);

void warp_zone(struct vaisseau_data *v, int nbplayers);
void gestion_warps(struct vaisseau_data *v, struct level_data *currentlevel,
                   int nbplayers);

#endif
