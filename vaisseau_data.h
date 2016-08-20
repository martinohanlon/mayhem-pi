#ifndef __VAISSEAU_DATA_H__
#define __VAISSEAU_DATA_H__
#include <allegro5/allegro.h>

#include "vaisseau_gfx.h"

#define MAX_TIR 50

#define VAISSEAU_MASS 0.9
#define VAISSEAU_THRUST_MAX 0.32
#define VAISSEAU_ANGLESTEP 5
#define VAISSEAU_MAX_FUEL 1284
#define VAISSEAU_SPEED_FUEL_DOWN 1
#define VAISSEAU_SPEED_FUEL_UP 8
#define VAISSEAU_MAX_SHIELD_FORCE 214
#define VAISSEAU_SPEED_SHIELD_FORCE_DOWN 2
#define VAISSEAU_SPEED_SHIELD_FORCE_UP 2

struct debris_data {
  int x, y;
  double xposprecise, yposprecise;
  double ax, ay;
  double vx, vy;
  double impultion;
  int angle;
  bool active;
};

struct collision_map {
  collision_map() = default;
  ~collision_map();

  void init(int width_in, int height_in, int num_frames_in);

  bool is_collide_pixel(int x, int y, int frame);
  void set_pixel(int x, int y, int frame, bool value);

  int get_index(int x, int y, int frame);

  int width;
  int height;
  int num_frames;

  bool *coll_map;
};

struct tir_data {
  int x, y;
  double xposprecise, yposprecise;
  double dx, dy;
  bool free;
};

struct vaisseau_data {
  // special for each ship
  double mass;
  double thrust_max;
  int anglestep;

  double fuel;
  double shield_force;

  int max_fuel;
  int speed_fuel_down;
  int speed_fuel_up;
  bool refueling;
  int max_shield_force;
  int speed_shield_force_down;
  int speed_shield_force_up;

  int explode_tick;
  double explode_count;
  bool explode;
  int option_type;
  double option_expire_time;
  bool explode_appear_time_passed;

  int impactx, impacty;
  double ax, ay;
  double vx, vy;
  double xposprecise, yposprecise;
  int xpos, ypos;
  int angle;
  double angle_precise;
  double thrust;
  bool shield;
  bool fire;
  bool fire_delay;
  bool landed;
  bool rebound;
  ALLEGRO_BITMAP *sprite_buffer; // Image du vaisseau
  ALLEGRO_BITMAP *sprite_buffer_rota;
  collision_map coll_map;
  struct vaisseau_gfx *gfx;
  struct tir_data tir[MAX_TIR];
  struct tir_data backtir[MAX_TIR];

  struct debris_data debris[8]; // 8 debris
};

int init_vaisseau_data(struct vaisseau_data *v, struct vaisseau_gfx *gfx,
                       float mass, float thrust_max, int anglestep,
                       int max_fuel, int speed_fuel_down, int speed_fuel_up,
                       int max_shield_force, int speed_shield_force_down,
                       int speed_shield_force_up);

void clean_vaisseau_data(struct vaisseau_data *v);

void init_ship_pos_from_platforms(struct vaisseau_data *v,
                                  struct platform_data *plats);

// to be called at each vbl!
void fuel_shield_calcul(int nbvaisseau, struct vaisseau_data *v, double dt);

#endif
