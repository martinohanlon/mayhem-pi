#include "collision.h"
#include "platform_data.h"
#include "player_view.h"
#include "utils.h"

#include "allegro_compatibility.h"

bool test_collision(struct player_view *pv, struct level_data *currentlevel) {
  struct vaisseau_data *vaisseau = pv->player->ship;

  struct platform_data *plt;
  bool test_it = true;

  for (int i = 0; i < currentlevel->nbplatforms; i++) {
    plt = &currentlevel->platformdata[i];
    int xmin = plt->xmin - 9;  // centrage
    int xmax = plt->xmax - 23; // centrage
    int yflat = plt->yflat - 29;

    if ((xmin <= vaisseau->xpos) && (vaisseau->xpos <= xmax) &&
        ((vaisseau->ypos == yflat) || ((vaisseau->ypos - 1) == yflat) ||
         ((vaisseau->ypos - 2) == yflat) || ((vaisseau->ypos - 3) == yflat)) &&
        ((vaisseau->angle & 0xff) <= 12 || (vaisseau->angle & 0xff) >= 243))
      test_it = false;
    if (vaisseau->shield && (xmin <= vaisseau->xpos) &&
        (vaisseau->xpos <= xmax) &&
        ((vaisseau->ypos == yflat) || ((vaisseau->ypos - 1) == yflat) ||
         ((vaisseau->ypos - 2) == yflat) || ((vaisseau->ypos - 3) == yflat) ||
         ((vaisseau->ypos + 1) == yflat)) &&
        ((vaisseau->angle & 0xff) <= 12 || (vaisseau->angle & 0xff) >= 243))
      test_it = false;
    if ((vaisseau->thrust) && (xmin <= vaisseau->xpos) &&
        (vaisseau->xpos <= xmax) &&
        ((vaisseau->ypos == yflat) || ((vaisseau->ypos - 1) == yflat) ||
         ((vaisseau->ypos + 1) == yflat)))
      test_it = false;
  }

  if (!test_it)
    return test_it;

  constexpr int size = 31;

  int num_frames = vaisseau->coll_map.num_frames;

  int frame = vaisseau->angle / vaisseau->anglestep;

  assert(frame >= 0 && frame < num_frames);

  int y_max = currentlevel->coll_map.height;
  int x_max = currentlevel->coll_map.width;

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      int x_pos = vaisseau->xpos + x;
      int y_pos = vaisseau->ypos + y;
      bool inside = x_pos >= 0 && x_pos < x_max && y_pos >= 0 && y_pos < y_max;

      if (inside && currentlevel->coll_map.is_collide_pixel(x_pos, y_pos, 0) &&
          vaisseau->coll_map.is_collide_pixel(x, y, frame)) {
        if (currentlevel->wall_collision) {
          return true;
        } else {
          bounce_vaisseau(vaisseau);
          return false;
        }
      }
    }
  }

  return false;
}

void bounce_vaisseau(struct vaisseau_data *vaisseau) {
  vaisseau->ax = (0);
  vaisseau->ay = (0);
  vaisseau->vx = -vaisseau->vx / 2;
  vaisseau->vy = -vaisseau->vy / 2;
}

bool pixel_collision_detect_inbox(struct vaisseau_data *vaisseau1, int xl1,
                                  int yt1, struct vaisseau_data *vaisseau2,
                                  int xl2, int yt2, int w, int h) {
  int x, y;
  int frame0 = vaisseau1->angle / vaisseau1->anglestep;
  int frame1 = vaisseau2->angle / vaisseau2->anglestep;

  for (x = 0; x < w; x++) {
    for (y = 0; y < h; y++) {
      if (vaisseau1->coll_map.is_collide_pixel(xl1 + x, yt1 + y, frame0) &&
          vaisseau2->coll_map.is_collide_pixel(xl2 + x, yt2 + y, frame1)) {
        return true;
      }
    }
  }
  return false;
}

//
// Implementation de la detection des collisions entre vaisseaux
//�@First we look for a bounding box, if none, sure, there are no collision
//  If there is, we find the limit of the bounding box and
//  we pixel iterate through it...
//

bool test_collision_ship2ship(struct vaisseau_data *vaisseau1,
                              struct vaisseau_data *vaisseau2) {
  // first find the bouding box
  int xl1, xl2, yt1, yt2;
  int w, h;

  if (vaisseau1->xpos + 32 >= vaisseau2->xpos &&
      vaisseau1->xpos <= vaisseau2->xpos) {
    xl2 = 0;
    xl1 = vaisseau2->xpos - vaisseau1->xpos;
    w = vaisseau1->xpos + 32 - vaisseau2->xpos;
  } else if (vaisseau2->xpos + 32 >= vaisseau1->xpos &&
             vaisseau2->xpos <= vaisseau1->xpos) {
    xl1 = 0;
    xl2 = vaisseau1->xpos - vaisseau2->xpos;
    w = vaisseau2->xpos + 32 - vaisseau1->xpos;
  } else
    return false;

  if (vaisseau1->ypos + 32 >= vaisseau2->ypos &&
      vaisseau1->ypos <= vaisseau2->ypos) {
    yt2 = 0;
    yt1 = vaisseau2->ypos - vaisseau1->ypos;
    h = vaisseau1->ypos + 32 - vaisseau2->ypos;
  } else if (vaisseau2->ypos + 32 >= vaisseau1->ypos &&
             vaisseau2->ypos <= vaisseau1->ypos) {
    yt1 = 0;
    yt2 = vaisseau1->ypos - vaisseau2->ypos;
    h = vaisseau2->ypos + 32 - vaisseau1->ypos;
  } else
    return false;

  // if we arrive here we might have a bounding box
  // with collision

  return pixel_collision_detect_inbox(vaisseau1, xl1, yt1, vaisseau2, xl2, yt2,
                                      w, h);
}

bool testcollision_bullet4pix(collision_map &coll_map, int x, int y, int w,
                              int h) {

  if (x < 0 || (x + 1) >= w || (y - 1) < 0 || y >= h)
    return true;
  else {
    unsigned long address_bmp; // pour le sprite
    unsigned char pixelcolor;

    int j;
    for (j = y - 1; j <= y; j++) {
      if (coll_map.is_collide_pixel(x, j, 0) ||
          coll_map.is_collide_pixel(x + 1, j, 0)) {
        return true;
      }
    }
  }
  return false;
}

bool testcollision_bullet1pix(vaisseau_data *v, int x, int y) {
  return v->coll_map.is_collide_pixel(x, y, v->angle / v->anglestep);
}

bool collision_tir_ship(struct vaisseau_data *v, struct vaisseau_data *allv,
                        int nombre_vaisseau) {
  struct tir_data *shoot;

  while (nombre_vaisseau--) {
    for (int i = 0; i < MAX_TIR; i++) {
      shoot = &allv->tir[i];
      if (shoot->free)
        continue; // only iterate through the non free shoot

      int xtrans = shoot->x - v->xpos;
      int ytrans = shoot->y - v->ypos;

      // if outside of the bounding box
      if (xtrans < 0 || xtrans >= 32 || ytrans < 0 || ytrans >= 32)
        continue;

      bool b = testcollision_bullet1pix(v, xtrans, ytrans);
      if (xtrans + 1 < 32) {
        if (ytrans - 1 >= 0) {
          b |= testcollision_bullet1pix(v, xtrans + 1, ytrans - 1);
          b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
        }
        b |= testcollision_bullet1pix(v, xtrans + 1, ytrans);
      } else if (ytrans - 1 >= 0) {
        b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
      }
      if (b) {
        shoot->free = true;
        bool isProtecting = (v->shield && v->shield_force > 0);
        if (isProtecting && !v->landed) {
          v->impactx = shoot->dx;
          v->impacty = shoot->dy;
        }
        return !isProtecting;
      }
    }
    allv++;
  }
  return false;
}

bool collision_backtir_ship(struct vaisseau_data *v, struct vaisseau_data *allv,
                            int nombre_vaisseau) {
  struct tir_data *backshoot;

  while (nombre_vaisseau--) {
    for (int i = 0; i < MAX_TIR; i++) {
      backshoot = &allv->backtir[i];
      if (backshoot->free)
        continue; // only iterate through the non free shoot

      int xtrans = backshoot->x - v->xpos;
      int ytrans = backshoot->y - v->ypos;

      // if outside of the bounding box
      if (xtrans < 0 || xtrans >= 32 || ytrans < 0 || ytrans >= 32)
        continue;

      bool b = testcollision_bullet1pix(v, xtrans, ytrans);
      if (xtrans + 1 < 32) {
        if (ytrans - 1 >= 0) {
          b |= testcollision_bullet1pix(v, xtrans + 1, ytrans - 1);
          b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
        }
        b |= testcollision_bullet1pix(v, xtrans + 1, ytrans);
      } else if (ytrans - 1 >= 0) {
        b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
      }
      if (b) {
        backshoot->free = true;
        bool isProtecting = (v->shield && v->shield_force > 0);
        if (isProtecting && !v->landed) {
          v->impactx = backshoot->dx;
          v->impacty = backshoot->dy;
        }
        return !isProtecting;
      }
    }
    allv++;
  }
  return false;
}

bool collision_debris_ship(struct vaisseau_data *v, struct vaisseau_data *allv,
                           int nombre_vaisseau) {
  struct debris_data *debris;

  while (nombre_vaisseau--) {
    for (int i = 0; i < 8; i++) {
      debris = &allv->debris[i];

      if (!debris->active)
        continue;

      int xtrans = debris->x - v->xpos;
      int ytrans = debris->y - v->ypos;

      // if outside of the bounding box
      if (xtrans < 0 || xtrans >= 32 || ytrans < 0 || ytrans >= 32)
        continue;

      bool b = testcollision_bullet1pix(v, xtrans, ytrans);
      if (xtrans + 1 < 32) {
        if (ytrans - 1 >= 0) {
          b |= testcollision_bullet1pix(v, xtrans + 1, ytrans - 1);
          b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
        }
        b |= testcollision_bullet1pix(v, xtrans + 1, ytrans);
      } else if (ytrans - 1 >= 0) {
        b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
      }
      if (b) {
        debris->active = false;
        bool isProtecting = (v->shield && v->shield_force > 0);
        if (isProtecting && !v->landed) {
          v->impactx = (debris->vx);
          v->impacty = (debris->vy);
        }
        return !isProtecting;
      }
    }
    allv++;
  }
  return false;
}

bool collision_dca_ship(struct vaisseau_data *v, struct dca_data *alldca,
                        int nb_dca) {
  struct tir_data *dca_tir;

  while (nb_dca--) {
    for (int i = 0; i < MAX_DCA_TIR; i++) {
      dca_tir = &alldca->dca_tir[i];

      if (dca_tir->free)
        continue;

      int xtrans = dca_tir->x - v->xpos;
      int ytrans = dca_tir->y - v->ypos;

      // if outside of the bounding box
      if (xtrans < 0 || xtrans >= 32 || ytrans < 0 || ytrans >= 32)
        continue;

      bool b = testcollision_bullet1pix(v, xtrans, ytrans);
      if (xtrans + 1 < 32) {
        if (ytrans - 1 >= 0) {
          b |= testcollision_bullet1pix(v, xtrans + 1, ytrans - 1);
          b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
        }
        b |= testcollision_bullet1pix(v, xtrans + 1, ytrans);
      } else if (ytrans - 1 >= 0) {
        b |= testcollision_bullet1pix(v, xtrans, ytrans - 1);
      }
      if (b) {
        dca_tir->free = true;
        bool isProtecting = (v->shield && v->shield_force > 0);
        if (isProtecting && !v->landed) {
          v->impactx = (dca_tir->dx);
          v->impacty = (dca_tir->dy);
        }
        return !isProtecting;
      }
    }
    alldca++;
  }
  return false;
}
