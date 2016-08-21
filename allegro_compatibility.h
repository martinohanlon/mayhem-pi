#ifndef ALLEGRO_COMPATIBILITY_H
#define ALLEGRO_COMPATIBILITY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

int fixtoi(double v);
double fixmul(double v0, double v1);
double fixdiv(double v0, double v1);
double fixadd(double v0, double v1);
double fixsub(double v0, double v1);
double itofix(int v);
double ftofix(double v);
double fixtof(double v);
double fixsin(double v);
double fixcos(double v);
double fixacos(double v);
double fixhypot(double v0, double v1);

void clear_bitmap(ALLEGRO_BITMAP *bitmap);
void hline(ALLEGRO_BITMAP *bmp, int x1, int y, int x2, ALLEGRO_COLOR color);
void vline(ALLEGRO_BITMAP *bmp, int x, int y1, int y2, ALLEGRO_COLOR color);

void blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *dest, int source_x,
          int source_y, int dest_x, int dest_y, int width, int height);
void textout(ALLEGRO_BITMAP *screen_buffer, ALLEGRO_FONT *font,
             const char *text, int x, int y, ALLEGRO_COLOR color);

void set_clip(ALLEGRO_BITMAP *bitmap, int x1, int y1, int x2, int y2);
void draw_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y);

void rotate_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y,
                   double angle);

struct allegro_pixel {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

allegro_pixel get_pixel(ALLEGRO_BITMAP *bmp, int x, int y);
allegro_pixel get_pixel(ALLEGRO_LOCKED_REGION *bmp, int x, int y);
void set_pixel(ALLEGRO_LOCKED_REGION *bmp, int x, int y, ALLEGRO_COLOR color);

bool is_nonblack_pixel(const allegro_pixel &p);
bool is_black_pixel(const allegro_pixel &p);

void stretch_blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *dest, int source_x,
                  int source_y, int source_width, int source_height, int dest_x,
                  int dest_y, int dest_width, int dest_height);

bool get_desktop_resolution(int adapter, int *w, int *h);

ALLEGRO_BITMAP *load_memory_bitmap(const char *file);

#endif // ALLEGRO_COMPATIBILITY_H
