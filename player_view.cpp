#include <stdio.h>

#include "collision.h"
#include "game_mgr.h"
#include "option.h"
#include "physics.h"
#include "platform_data.h"
#include "player_view.h"
#include "utils.h"

#include "allegro_compatibility.h"

#include <allegro5/allegro_primitives.h>

int init_player_view(struct player_view *pv, int x, int y, int w, int h,
                     struct player_info *player) {
  pv->bordersize = 10;

  pv->x = x;
  pv->y = y;
  pv->w = w - 2 * pv->bordersize;
  pv->h = h - 2 * pv->bordersize;
  pv->player = player;
  pv->back_map_buffer = create_clear_bitmap(w, h);
  if (!pv->back_map_buffer)
    return -1;
  return 0;
}

void clean_player_view(struct player_view *pv) {
  if (pv->back_map_buffer)
    al_destroy_bitmap(pv->back_map_buffer);
}

void draw_basic_player_view(struct player_view *v, int nbviews,
                            ALLEGRO_BITMAP *src_map) {

  for (int i = 0; i < nbviews; i++) {

    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
    struct vaisseau_data *ship = v->player->ship;

    set_clip(v->back_map_buffer, 0, 0, v->w + 2 * v->bordersize,
             v->h + 2 * v->bordersize);
    clear_bitmap(v->back_map_buffer);
    hline(v->back_map_buffer, 0, 0, v->w + 2 * v->bordersize, color);
    hline(v->back_map_buffer, 0, v->h + 2 * v->bordersize - 1,
          v->w + 2 * v->bordersize, color);
    vline(v->back_map_buffer, 0, 0, v->h + 2 * v->bordersize, color);
    vline(v->back_map_buffer, v->w + 2 * v->bordersize - 1, 0,
          v->h + 2 * v->bordersize, color);

    char buffer[20];

    // debug x,y data
    /*char bufferx[20];
    char buffery[20];
    char buffervx[20];
    char buffervy[20];

        sprintf(bufferx,"x=%d",ship->xpos);
        sprintf(buffery,"y=%d",ship->ypos);
        sprintf(buffervx,"vx=%d",fixtoi(ship->vx));
        sprintf(buffervy,"vy=%d",-fixtoi(ship->vy));

    textout(v->back_map_buffer, font, bufferx, 3 , v->h+v->bordersize+1, color);
    textout(v->back_map_buffer, font, buffery, 55 , v->h+v->bordersize+1,
    color);
    textout(v->back_map_buffer, font, buffervx, 195 , v->h+v->bordersize+1,
    color);
    textout(v->back_map_buffer, font, buffervy, 250 , v->h+v->bordersize+1,
    color);*/

    if (player_gameover(v->player))
      sprintf(buffer, "Game over");
    else
      sprintf(buffer, "Live(s): %d", v->player->nblives);

    textout(v->back_map_buffer, GameManager::font, v->player->name, 3, 2,
            color);
    textout(v->back_map_buffer, GameManager::font, buffer, v->bordersize + 195,
            2, color);

    int barheight_fuel = v->h * ship->fuel / ship->max_fuel;
    int barheight_shield = v->h * ship->shield_force / ship->max_shield_force;
    ALLEGRO_COLOR fuel_col;
    ALLEGRO_COLOR shield_col;

    if (ship->fuel >= ship->max_fuel / 2) {
      auto fuel_col_r =
          255 - fixtoi(fixmul(
                    itofix(255),
                    fixsub(fixmul(itofix(2), fixdiv(itofix(ship->fuel),
                                                    itofix(ship->max_fuel))),
                           itofix(1))));
      fuel_col = al_map_rgb(fuel_col_r, 255, 0);
    } else {
      auto fuel_col_g = 255 * 2 * ship->fuel / ship->max_fuel;
      fuel_col = al_map_rgb(255, fuel_col_g, 0);
    }

    if (ship->shield_force >= ship->max_shield_force / 2) {
      auto shield_col_r =
          255 -
          fixtoi(fixmul(
              itofix(255),
              fixsub(fixmul(itofix(2), fixdiv(itofix(ship->shield_force),
                                              itofix(ship->max_shield_force))),
                     itofix(1))));
      shield_col = al_map_rgb(shield_col_r, 255, 0);
    } else {
      auto shield_col_g = 255 * 2 * ship->shield_force / ship->max_shield_force;
      shield_col = al_map_rgb(255, shield_col_g, 0);
    }

    vline(v->back_map_buffer, (v->bordersize / 2) + 1, v->h + v->bordersize,
          v->bordersize + (v->h - barheight_fuel), fuel_col);
    vline(v->back_map_buffer, v->bordersize / 2, v->h + v->bordersize,
          v->bordersize + (v->h - barheight_fuel), fuel_col);
    vline(v->back_map_buffer, v->w + v->bordersize + v->bordersize / 2,
          v->h + v->bordersize, v->bordersize + (v->h - barheight_shield),
          shield_col);
    vline(v->back_map_buffer, v->w + v->bordersize + (v->bordersize / 2) - 1,
          v->h + v->bordersize, v->bordersize + (v->h - barheight_shield),
          shield_col);
    // thicker shield line
    if (ship->option_type == OPT_SLOWSHIELD) {
      vline(v->back_map_buffer, v->w + v->bordersize + (v->bordersize / 2) - 2,
            v->h + v->bordersize, v->bordersize + (v->h - barheight_shield),
            shield_col);
      vline(v->back_map_buffer, v->w + v->bordersize + (v->bordersize / 2) - 3,
            v->h + v->bordersize, v->bordersize + (v->h - barheight_shield),
            shield_col);
    }
    // reset clip after
    set_clip(v->back_map_buffer, v->bordersize, v->bordersize, v->w, v->h);
    v++;
  }
}

void rotate_sprite(struct player_view *v) {
  struct vaisseau_data *ship = v->player->ship;

  clear_bitmap(ship->sprite_buffer_rota);
  rotate_sprite(ship->sprite_buffer_rota, ship->sprite_buffer, 0, 0,
                itofix(ship->angle));
}

void display_rotate_sprites(struct player_view allviews[], int nbviews,
                            struct level_data *currentlevel) {
  struct vaisseau_data *ship;
  int j = 0;
  for (j = 0; j < nbviews; j++) {
    struct player_view *view = &allviews[j];
    struct vaisseau_data *ship = view->player->ship;
    if (!ship->explode) {
      draw_sprite(currentlevel->level_buffer, ship->sprite_buffer_rota,
                  ship->xpos, ship->ypos);

      // if the ship is halfway across the gap, draw it on the other side
      if (ship->xpos + 32 > currentlevel->edgedata.rightx) {
        draw_sprite(currentlevel->level_buffer, ship->sprite_buffer_rota,
                    ship->xpos - al_get_bitmap_width(currentlevel->bitmap),
                    ship->ypos);
      }
    }
  }
}

void init_tir(struct vaisseau_data *v) {

  struct tir_data *shoot;

  if (v->fire && (test_place_tir(v) != -1) && v->fire_delay) {
    int cx;
    int cy;
    int place_free_tir;
    int angle;

    int num_of_tir;
    // triple shot option?
    num_of_tir = v->option_type == OPT_TRIPLESHOT ? 3 : 1;

    for (int i = 0; i < num_of_tir; i++) {
      place_free_tir = test_place_tir(v);
      if (place_free_tir == -1)
        return; // only do something IF THERE IS A FREE SHOOT !
      shoot = &v->tir[test_place_tir(v)];

      cx = v->xpos + 15;
      cy = v->ypos + 16;

      if (i == 0)
        angle = v->angle;
      // triple shot
      if (i == 1)
        angle = v->angle - 2;
      if (i == 2)
        angle = v->angle + 2;

      shoot->x = cx + fixtoi(fixmul(itofix(18), fixsin(itofix(angle))));
      shoot->y = cy + fixtoi(fixmul(itofix(18), -fixcos(itofix(angle))));
      shoot->xposprecise = itofix(shoot->x);
      shoot->yposprecise = itofix(shoot->y);

      shoot->dx = fixmul(ftofix(5.1), fixsin(itofix(angle)));
      shoot->dy = fixmul(ftofix(5.1), -fixcos(itofix(angle)));
      shoot->dx = fixadd(shoot->dx, fixdiv(v->vx, ftofix(3.5)));
      shoot->dy = fixadd(shoot->dy, fixdiv(v->vy, ftofix(3.5)));

      shoot->free = false;
    }

    if (v->option_type == OPT_BACKSHOT) {
      struct tir_data *backshoot;
      place_free_tir = test_place_backtir(v);
      if (place_free_tir == -1)
        return; // only do something IF THERE IS A FREE BACKSHOOT !

      backshoot = &v->backtir[test_place_backtir(v)];

      backshoot->x = 2 * (v->xpos + 16) - shoot->x;
      backshoot->y = 2 * (v->ypos + 16) - shoot->y;
      backshoot->xposprecise = itofix(backshoot->x);
      backshoot->yposprecise = itofix(backshoot->y);
      backshoot->dx = -fixmul(ftofix(5.1), fixsin(itofix(v->angle)));
      backshoot->dy = -fixmul(ftofix(5.1), -fixcos(itofix(v->angle)));
      backshoot->free = false;
    }
  }
}

void plot_tir(struct vaisseau_data *v, struct level_data *currentlevel,
              double dt) {
  struct tir_data *shoot;
  int w = al_get_bitmap_width(currentlevel->collision_bitmap);
  int h = al_get_bitmap_height(currentlevel->collision_bitmap);

  for (int i = 0; i < MAX_TIR; i++) {
    shoot = &v->tir[i];
    if (shoot->free)
      continue; // only iterate through the non free shoot
    if (testcollision_bullet4pix(currentlevel->coll_map, shoot->x, shoot->y, w,
                                 h)) {
      // if there is collision we free the shoot
      // and we go on!
      shoot->free = true;
      continue;
    }

    put_big_pixel(currentlevel->level_buffer, shoot->x, shoot->y,
                  currentlevel->particle_color);

    shoot->xposprecise = fixadd(shoot->xposprecise, shoot->dx * (dt / 0.025));
    shoot->yposprecise = fixadd(shoot->yposprecise, shoot->dy * (dt / 0.025));
    shoot->x = fixtoi(shoot->xposprecise);
    shoot->y = fixtoi(shoot->yposprecise);

    // warp tir
    if (currentlevel->edgedata.wrapx) {
      if (shoot->x < currentlevel->edgedata.leftx) {
        shoot->x = currentlevel->edgedata.rightx;
        shoot->xposprecise = itofix(currentlevel->edgedata.rightx);
      } else if (shoot->x > currentlevel->edgedata.rightx) {
        shoot->x = currentlevel->edgedata.leftx;
        shoot->xposprecise = itofix(currentlevel->edgedata.leftx);
      }
    }
  }

  if (v->option_type == OPT_BACKSHOT) {
    struct tir_data *backshoot;

    for (int i = 0; i < MAX_TIR; i++) {
      backshoot = &v->backtir[i];
      if (backshoot->free)
        continue; // only iterate through the non free shoot
      if (testcollision_bullet4pix(currentlevel->coll_map, backshoot->x,
                                   backshoot->y, w, h)) {
        // if there is collision we free the shoot
        // and we go on!
        backshoot->free = true;
        continue;
      }

      put_big_pixel(currentlevel->level_buffer, backshoot->x, backshoot->y,
                    currentlevel->particle_color);

      backshoot->xposprecise =
          fixadd(backshoot->xposprecise, backshoot->dx * (dt / 0.025));
      backshoot->yposprecise =
          fixadd(backshoot->yposprecise, backshoot->dy * (dt / 0.025));
      backshoot->x = fixtoi(backshoot->xposprecise);
      backshoot->y = fixtoi(backshoot->yposprecise);

      // warp back tir
      if (currentlevel->edgedata.wrapx) {
        if (backshoot->x < currentlevel->edgedata.leftx) {
          backshoot->x = currentlevel->edgedata.rightx;
          backshoot->xposprecise = itofix(currentlevel->edgedata.rightx);
        } else if (backshoot->x > currentlevel->edgedata.rightx) {
          backshoot->x = currentlevel->edgedata.leftx;
          backshoot->xposprecise = itofix(currentlevel->edgedata.leftx);
        }
      }
    }
  }
}

// src_map necessary for collision detection
void gestion_tir(struct vaisseau_data *v, struct level_data *currentlevel,
                 double dt) {
  init_tir(v);
  plot_tir(v, currentlevel, dt);
}

int test_place_tir(struct vaisseau_data *v) {
  struct tir_data *shoot;

  for (int i = 0; i < MAX_TIR; i++) {
    shoot = &v->tir[i];
    if (shoot->free)
      return (i);
  }
  return (-1);
}

int test_place_backtir(struct vaisseau_data *v) {
  struct tir_data *backshoot;

  for (int i = 0; i < MAX_TIR; i++) {
    backshoot = &v->backtir[i];
    if (backshoot->free)
      return (i);
  }
  return (-1);
}

void put_big_pixel(ALLEGRO_BITMAP *bmp, int x, int y, ALLEGRO_COLOR color) {
  al_set_target_bitmap(bmp);
  al_draw_filled_rectangle(x, y, x+2, y+2,color);
}

void draw_explosion(struct player_info *allpi, struct platform_data *plats,
                    int nombre_vaisseau, struct level_data *currentlevel,
                    double dt) {
  int i;
  int j;
  for (i = 0; i < nombre_vaisseau; i++) {
    if (allpi[i].ship->explode)
      if (allpi[i].ship->explode_count < (48 * 0.025)) {
        draw_sprite(
            currentlevel->level_buffer,
            get_sprite_explosion_frame(allpi[i].ship->explode_count * 40),
            allpi[i].ship->xpos, allpi[i].ship->ypos);

        // if the ship has exploded across the gap, draw it on the other side
        if (currentlevel->edgedata.wrapx)
          if ((currentlevel->edgedata.wrapx) &&
              (allpi[i].ship->xpos + 32 > currentlevel->edgedata.rightx)) {
            draw_sprite(
                currentlevel->level_buffer,
                get_sprite_explosion_frame(allpi[i].ship->explode_count * 40),
                allpi[i].ship->xpos - al_get_bitmap_width(currentlevel->bitmap),
                allpi[i].ship->ypos);
          }
        allpi[i].ship->explode_count += dt;
        allpi[i].ship->explode_tick++;
      } else {
        if (allpi[i].ship->explode_count < 200 * 0.025) {
          allpi[i].ship->explode_count += dt;
          allpi[i].ship->explode_tick++;
        } else {
          allpi[i].ship->explode_count = 0;
          allpi[i].ship->explode_tick = 0;
          allpi[i].ship->explode_appear_time_passed = false;
          allpi[i].ship->explode = false;
          init_ship_pos_from_platforms(allpi[i].ship, &plats[i]);
          allpi[i].nblives--;
        }
      }
  }
}

void mega_collision_test(struct player_info *allpi, struct player_view *views,
                         struct vaisseau_data *vaisseaux,
                         struct level_data *currentlevel, int nbplayers,
                         int nombre_vaisseau) {
  struct dca_data *dca;
  dca = &currentlevel->alldca[0];

  int i;
  for (i = 0; i < nbplayers; i++) {
    if (!allpi[i].ship->explode &&
        collision_debris_ship(allpi[i].ship, vaisseaux, nombre_vaisseau))
      player_exploded(&allpi[i]);

    if (!allpi[i].ship->explode &&
        collision_dca_ship(allpi[i].ship, dca, NB_DCA))
      player_exploded(&allpi[i]);

    if (!allpi[i].ship->explode &&
        collision_backtir_ship(allpi[i].ship, vaisseaux, nombre_vaisseau))
      player_exploded(&allpi[i]);

    if (!allpi[i].ship->explode &&
        collision_tir_ship(allpi[i].ship, vaisseaux, nombre_vaisseau)) {
      player_exploded(&allpi[i]);
      // textout(screen, font, "SHOT   ", 50*(i+1), 50,
      // makecol(255*(i+1)/(nombre_vaisseau),128,128));
    } else {
      if (!allpi[i].ship->explode && !(vaisseaux[i].landed) &&
          test_collision(&views[i], currentlevel)) {
        player_exploded(&allpi[i]);
        // textout(screen, font, "BOOM  ", 50*(i+1), 50,
        // makecol(255*(i+1)/(nombre_vaisseau),128,128));
      }
      // else
      // textout(screen, font, "OK    ", 50*(i+1), 50,
      // makecol(255,255*(i+1)/(nombre_vaisseau),255));
    }
  }

  int j;
  for (i = 0; i < nombre_vaisseau; i++)
    for (j = nombre_vaisseau - 1; j > i; j--)
      if (!allpi[i].ship->explode && !allpi[j].ship->explode &&
          test_collision_ship2ship(&vaisseaux[i], &vaisseaux[j])) {
        player_exploded(&allpi[i]);
        player_exploded(&allpi[j]);
        // textout(screen, font, "DOUBLEBOOM", 350, 50, makecol(255,255,255));
      }
}

//----------------------------------------------------------------------------//
//                        Gestion des Debris
//----------------------------------------------------------------------------//

void init_debris(struct vaisseau_data *v) {
  int angle = 16;

  for (int i = 0; i < 8; i++) {

    v->debris[i].angle = angle;
    v->debris[i].x =
        ((v->xpos + 15) +
         fixtoi(fixmul(itofix(20), fixsin(itofix(v->debris[i].angle)))));
    v->debris[i].y =
        ((v->ypos + 16) +
         fixtoi(fixmul(itofix(20), -fixcos(itofix(v->debris[i].angle)))));
    v->debris[i].xposprecise = itofix(v->debris[i].x);
    v->debris[i].yposprecise = itofix(v->debris[i].y);
    v->debris[i].ax = itofix(0);
    v->debris[i].ay = itofix(0);
    v->debris[i].impultion = ftofix(7.5);
    v->debris[i].vx = itofix(0);
    v->debris[i].vy = itofix(0);
    v->debris[i].active = true;

    angle += 32;
  }
}

void test_collision_debris(struct vaisseau_data *v, collision_map &src_map,
                           int w, int h) {
  for (int i = 0; i < 8; i++) {
    if (testcollision_bullet4pix(src_map, v->debris[i].x, v->debris[i].y, w, h))
      v->debris[i].active = false;
  }
}

void plot_debris(struct vaisseau_data *v, const physics_constants &physics,
                 struct level_data *currentlevel, double dt) {

  for (int j = 0; j < 8; j++) {
    if (v->debris[j].active) {
      put_big_pixel(currentlevel->level_buffer, v->debris[j].x, v->debris[j].y,
                    currentlevel->particle_color);
    }
  }

  for (int i = 0; i < 8; i++) {
    if (v->debris[i].active) {
      v->debris[i].ax =
          fixmul(v->debris[i].impultion, fixsin(itofix(v->debris[i].angle)));
      v->debris[i].ay =
          fixadd(physics.iG, fixmul(v->debris[i].impultion,
                                    -fixcos(itofix(v->debris[i].angle))));

      v->debris[i].vx =
          fixadd(v->debris[i].vx, fixmul(physics.iCoeffax, v->debris[i].ax));
      v->debris[i].vy =
          fixadd(v->debris[i].vy, fixmul(physics.iCoeffay, v->debris[i].ay));

      v->debris[i].vx = fixmul(v->debris[i].vx, physics.iXfrott);
      v->debris[i].vy = fixmul(v->debris[i].vy, physics.iYfrott);

      v->debris[i].vx = fixadd(v->debris[i].vx, fixdiv(v->vx, ftofix(2.5)));
      v->debris[i].vy = fixadd(v->debris[i].vy, fixdiv(v->vy, ftofix(8.5)));

      v->debris[i].xposprecise =
          fixadd(v->debris[i].xposprecise,
                 fixmul(physics.iCoeffvx, v->debris[i].vx) * (dt / 0.025));
      v->debris[i].yposprecise =
          fixadd(v->debris[i].yposprecise,
                 fixmul(physics.iCoeffvy, v->debris[i].vy) * (dt / 0.025));

      v->debris[i].x = fixtoi(v->debris[i].xposprecise);
      v->debris[i].y = fixtoi(v->debris[i].yposprecise);

      v->debris[i].impultion = itofix(0);

      // warp debris
      if (currentlevel->edgedata.wrapx) {
        if (v->debris[i].x < currentlevel->edgedata.leftx) {
          v->debris[i].x = currentlevel->edgedata.rightx;
          v->debris[i].xposprecise = itofix(currentlevel->edgedata.rightx);
        } else if (v->debris[i].x > currentlevel->edgedata.rightx) {
          v->debris[i].x = currentlevel->edgedata.leftx;
          v->debris[i].xposprecise = itofix(currentlevel->edgedata.leftx);
        }
      }
    }
  }
  v->vx = itofix(0);
  v->vy = itofix(0);
}

void draw_debris(struct player_info *allpi, const physics_constants &physics,
                 int nombre_vaisseau, struct level_data *currentlevel,
                 double dt) {
  int w = al_get_bitmap_width(currentlevel->collision_bitmap);
  int h = al_get_bitmap_height(currentlevel->collision_bitmap);

  for (int i = 0; i < nombre_vaisseau; i++) {
    if (allpi[i].ship->explode_tick == 1)
      init_debris(allpi[i].ship);

    if ((allpi[i].ship->explode) && (allpi[i].ship->explode_tick > 1)) {
      test_collision_debris(allpi[i].ship, currentlevel->coll_map, w, h);
      plot_debris(allpi[i].ship, physics, currentlevel, dt);
    }

    if (!allpi[i].ship->explode)
      for (int j = 0; j < 8; j++) {
        allpi[i].ship->debris[j].active = false;
      }
  }
}

//----------------------------------------------------------------------------//
//                        Gestion MiniMap
//----------------------------------------------------------------------------//

void gestion_minimap(struct vaisseau_data *vaisseaux,
                     struct level_data *currentlevel, int nbplayers,
                     int largeur, int hauteur) {
  stretch_blit(currentlevel->mini_bitmap, currentlevel->mini_bitmap_buffer, 0,
               0, 99, 150, 0, 0, 10.0 * (largeur / 100.0),
               15.0 * (largeur / 100.0));

  int x, y;
  struct vaisseau_data *v;
  for (int i = 0; i < nbplayers; i++) {
    v = &vaisseaux[i];
    x = (v->xpos >> 3) + 1;
    y = (v->ypos >> 3) + 3;
    // put_big_pixel(currentlevel->mini_ALLEGRO_BITMAP_buffer,
    // x*(largeur*(99/800.0)/99.0), y*(hauteur*(150/600.0)/150.0), makecol(255,
    // 255, 255));
    put_big_pixel(currentlevel->mini_bitmap_buffer,
                  x * ((10.0 * (largeur / 100.0)) / 99.0),
                  y * ((15.0 * (largeur / 100.0)) / 150.0),
                  al_map_rgb(255, 255, 255));
  }
}

//----------------------------------------------------------------------------//
//                        Gestion DCA
//----------------------------------------------------------------------------//

void init_dca_tir(struct dca_data *dca, struct vaisseau_data *v) {
  double distance;
  double deltax, deltay;
  double angle;

  deltax = fixsub(v->xposprecise + itofix(16), itofix(dca->xsrc));
  deltay = fixsub(v->yposprecise + itofix(16), itofix(dca->ysrc));
  distance = fixhypot(deltax, deltay);

  struct tir_data *dca_tir;
  if (distance < itofix(dca->area) && (test_place_dca_tir(dca) != -1) &&
      dca->delayed == 0) {
    int place_free_dca_tir = test_place_dca_tir(dca);
    if (place_free_dca_tir == -1)
      return;

    dca_tir = &(dca->dca_tir[test_place_dca_tir(dca)]);

    angle = fixacos(fixdiv(deltay, distance));

    dca_tir->x = dca->xsrc;
    dca_tir->y = dca->ysrc;

    dca_tir->xposprecise = itofix(dca_tir->x);
    dca_tir->yposprecise = itofix(dca_tir->y);

    if (deltax < itofix(0))
      dca_tir->dx = fixmul(ftofix(1.1), -fixsin(angle));
    else
      dca_tir->dx = fixmul(ftofix(1.1), fixsin(angle));

    dca_tir->dy = fixmul(ftofix(1.1), fixcos(angle));

    dca_tir->free = false;
    dca->shoot = true;
  }
}

void plot_dca_tir(struct dca_data *dca, struct level_data *currentlevel) {
  struct tir_data *dca_tir;
  int w = al_get_bitmap_width(currentlevel->collision_bitmap);
  int h = al_get_bitmap_height(currentlevel->collision_bitmap);

  for (int i = 0; i < MAX_DCA_TIR; i++) {
    dca_tir = &(dca->dca_tir[i]);
    if (dca_tir->free)
      continue;
    if (testcollision_bullet4pix(currentlevel->coll_map, dca_tir->x, dca_tir->y,
                                 w, h)) {
      dca_tir->free = true;
      continue;
    }

    put_big_pixel(currentlevel->level_buffer, dca_tir->x, dca_tir->y,
                  currentlevel->particle_color);

    dca_tir->xposprecise = fixadd(dca_tir->xposprecise, dca_tir->dx);
    dca_tir->yposprecise = fixadd(dca_tir->yposprecise, dca_tir->dy);
    dca_tir->x = fixtoi(dca_tir->xposprecise);
    dca_tir->y = fixtoi(dca_tir->yposprecise);

    // warp dca tir
    if (currentlevel->edgedata.wrapx) {
      if (dca_tir->x < currentlevel->edgedata.leftx) {
        dca_tir->x = currentlevel->edgedata.rightx;
        dca_tir->xposprecise = itofix(currentlevel->edgedata.rightx);
      } else if (dca_tir->x > currentlevel->edgedata.rightx) {
        dca_tir->x = currentlevel->edgedata.leftx;
        dca_tir->xposprecise = itofix(currentlevel->edgedata.leftx);
      }
    }
  }
}

void gestion_dca(struct dca_data *dca, struct vaisseau_data *v,
                 struct level_data *currentlevel) {

  for (int i = 0; i < NB_DCA; i++) {
    init_dca_tir(dca, v);
    plot_dca_tir(dca, currentlevel);
    if (dca->shoot) {
      dca->delayed++;
      if (dca->delayed > dca->delay) {
        dca->delayed = 0;
        dca->shoot = false;
      }
    }
    dca++;
  }
}

int test_place_dca_tir(struct dca_data *dca) {
  struct tir_data *dca_tir;

  for (int i = 0; i < MAX_DCA_TIR; i++) {
    dca_tir = &(dca->dca_tir[i]);
    if (dca_tir->free)
      return (i);
  }
  return (-1);
}

//----------------------------------------------------------------------------//
//                        Gestion Warp Zone
//----------------------------------------------------------------------------//

void gestion_warps(struct vaisseau_data *v, struct level_data *currentlevel,
                   int nbplayers) {
  while (nbplayers--) {
    if (v->xpos < currentlevel->edgedata.leftx) {
      v->xpos = currentlevel->edgedata.rightx;
      v->xposprecise = itofix(currentlevel->edgedata.rightx);
    } else if (v->xpos > currentlevel->edgedata.rightx) {
      v->xpos = currentlevel->edgedata.leftx;
      v->xposprecise = itofix(currentlevel->edgedata.leftx);
    }
    v++;
  }
}

void warp_zone(struct vaisseau_data *v, int nbplayers) {
  while (nbplayers--) {
    if (v->ypos <= 160 && v->xpos >= 174 && v->xpos <= 184) {
      v->xpos = 344;
      v->ypos = 1052;
      v->xposprecise = itofix(344);
      v->yposprecise = itofix(1052);
    }
    if (1053 <= v->ypos && v->xpos >= 339 && v->xpos <= 349) {
      v->xpos = 179;
      v->ypos = 165;
      v->xposprecise = itofix(179);
      v->yposprecise = itofix(165);
    }
    v++;
  }
}
