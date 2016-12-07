#include "allegro_compatibility.h"
#include <allegro5/allegro_primitives.h>

#include <algorithm>
#include <cmath>

#define PI 3.14159265

void pivot_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y,
                  int cx, int cy, int angle) {
  al_draw_rotated_bitmap(sprite, cx, cy, x, y, (angle * PI / 180), 0);
  //al_draw_rotated_bitmap(sprite, cx, cy, x, y, al_fixmul(angle, al_fixtorad_r), 0);
}

int fixtoi(double v) { return static_cast<int>(v); }
double fixmul(double v0, double v1) { return v0 * v1; }
double fixdiv(double v0, double v1) { return v0 / v1; }
double fixadd(double v0, double v1) { return v0 + v1; }
double fixsub(double v0, double v1) { return v0 - v1; };
double fixhypot(double v0, double v1) { return std::sqrt(v0 * v0 + v1 * v1); };
double itofix(int v) { return static_cast<double>(v); }
double ftofix(double v) { return v; }
double fixtof(double v) { return v; }
double fixsin(double v) { return std::sin(v * PI / 180); }
double fixcos(double v) { return std::cos(v * PI / 180); }
double fixacos(double v) { return std::acos(v) * (180 / PI); }

void alc_set_target_bitmap(ALLEGRO_BITMAP *mytargetbitmap) {
  if (al_get_target_bitmap() != mytargetbitmap) {
 	  al_set_target_bitmap(mytargetbitmap);
  }
}

void clear_bitmap(ALLEGRO_BITMAP *bitmap) {
  alc_set_target_bitmap(bitmap);
  al_clear_to_color(al_map_rgba(0, 0, 0, 0));
}

void hline(ALLEGRO_BITMAP *bmp, int x1, int y, int x2, ALLEGRO_COLOR color) {
  alc_set_target_bitmap(bmp);
  al_draw_line(x1 +0.5, y +0.5, x2 +0.5, y+ 0.5, color, 1);
}

void vline(ALLEGRO_BITMAP *bmp, int x, int y1, int y2, ALLEGRO_COLOR color) {
  alc_set_target_bitmap(bmp);
  al_draw_line(x +0.5, y1 +0.5, x + 0.5, y2 +0.5, color, 1);
}

void blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *dest, int source_x,
          int source_y, int dest_x, int dest_y, int width, int height) {
  alc_set_target_bitmap(dest);
  al_draw_bitmap_region(source, source_x, source_y, width, height, dest_x,
                        dest_y, 0);
}

void textout(ALLEGRO_BITMAP *screen_buffer, ALLEGRO_FONT *font,
             const char *text, int x, int y, ALLEGRO_COLOR color) {
  alc_set_target_bitmap(screen_buffer);
  al_draw_text(font, color, x, y, 0, text);
}
void set_clip(ALLEGRO_BITMAP *bitmap, int x1, int y1, int x2, int y2) {
  alc_set_target_bitmap(bitmap);
  al_set_clipping_rectangle(x1, y1, x2 - x1, y2 - y1);
}

void rotate_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y,
                   double angle) {
  auto w = al_get_bitmap_width(sprite);
  auto h = al_get_bitmap_height(sprite);

  pivot_sprite(bmp, sprite, x + w / 2, y + h / 2, w / 2, h / 2, angle);
}

void draw_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y) {
  blit(sprite, bmp, 0, 0, x, y, al_get_bitmap_width(sprite),
       al_get_bitmap_height(sprite));
}

allegro_pixel get_pixel(ALLEGRO_BITMAP *bmp, int x, int y) {
  unsigned char r, g, b;
  al_unmap_rgb(al_get_pixel(bmp, x, y), &r, &g, &b);
  allegro_pixel pixel;
  pixel.r = r;
  pixel.g = g;
  pixel.b = b;
  return pixel;
}

allegro_pixel get_pixel(ALLEGRO_LOCKED_REGION *bmp, int x, int y) {
  allegro_pixel pixel;

  int pos = y * bmp->pitch + bmp->pixel_size * x;

  unsigned char *data_pos = (unsigned char *)bmp->data;

  pixel.r = data_pos[pos];
  pixel.g = data_pos[pos + 1];
  pixel.b = data_pos[pos + 2];

  return pixel;
}

void set_pixel(ALLEGRO_LOCKED_REGION *bmp, int x, int y, ALLEGRO_COLOR color) {
  int pos = y * bmp->pitch + bmp->pixel_size * x;

  unsigned char *data_pos = (unsigned char *)bmp->data;

  unsigned char r, g, b;
  al_unmap_rgb(color, &r, &g, &b);

  data_pos[pos] = r;
  data_pos[pos + 1] = g;
  data_pos[pos + 2] = b;
}

bool is_nonblack_pixel(const allegro_pixel &p) {
  return p.r != 0 || p.g != 0 || p.b != 0;
}

bool is_black_pixel(const allegro_pixel &p) {
  return p.r == 0 && p.g == 0 && p.b == 0;
}

void stretch_blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *dest, int source_x,
                  int source_y, int source_width, int source_height, int dest_x,
                  int dest_y, int dest_width, int dest_height) {
  alc_set_target_bitmap(dest);
  al_draw_scaled_bitmap(source, source_x, source_y, source_width, source_height,
                        dest_x, dest_y, dest_width, dest_height, 0);
}

bool get_desktop_resolution(int adapter, int *w, int *h) {
  ALLEGRO_MONITOR_INFO info;
  if (!al_get_monitor_info(adapter, &info)) {
    return false;
  }

  *w = info.x2 - info.x1;
  *h = info.y2 - info.y1;

  return true;
}

ALLEGRO_BITMAP *load_memory_bitmap(const char *file) {
  int flags = al_get_new_bitmap_flags();
  al_set_new_bitmap_flags(flags | ALLEGRO_MEMORY_BITMAP);
  ALLEGRO_BITMAP *bmp = al_load_bitmap(file);
  al_set_new_bitmap_flags(flags);
  return bmp;
}
