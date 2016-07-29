#ifndef ALLEGRO_COMPATIBILITY_H
#define ALLEGRO_COMPATIBILITY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class allegro_compatibility
{
public:
    allegro_compatibility();

};

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

static void update_pressed_keys();

static bool key[ALLEGRO_KEY_MAX];


void clear_bitmap(ALLEGRO_BITMAP* bitmap);
void hline(ALLEGRO_BITMAP *bmp, int x1, int y, int x2, ALLEGRO_COLOR color);

ALLEGRO_COLOR makecol(unsigned char r,unsigned char g,unsigned char b);
void blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void textout(ALLEGRO_BITMAP* screen_buffer, ALLEGRO_FONT* font, const char* text, int x, int y, ALLEGRO_COLOR color);
#endif // ALLEGRO_COMPATIBILITY_H
