#include "allegro_compatibility.h"
#include <allegro5/allegro_primitives.h>

#include <cmath>


#define PI 3.14159265

void pivot_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y, int cx, int cy, double angle){
    al_draw_rotated_bitmap(sprite, cx, cy, x, y, (angle*PI/180), 0);
}

 int fixtoi(double v) {return static_cast<int>(v);}
 double fixmul(double v0, double v1) {return v0*v1;}
 double fixdiv(double v0, double v1) {return v0/v1;}
 double fixadd(double v0, double v1) {return v0+v1;}
 double fixsub(double v0, double v1) {return v0-v1;};
 double fixhypot(double v0, double v1) {return std::sqrt( v0*v0 + v1*v1);};
 double itofix(int v) {return static_cast<double>(v);}
 double ftofix(double v) {return v;}
 double fixtof(double v) {return v;}
 double fixsin(double v) {return std::sin(v*PI/180);}
 double fixcos(double v) {return std::cos(v*PI/180);}
 double fixacos(double v) {return std::acos(v*PI/180);}

 void clear_bitmap(ALLEGRO_BITMAP* bitmap)
{
     al_set_target_bitmap(bitmap);
     al_clear_to_color(al_map_rgb(0,0,0));
 }

void hline(ALLEGRO_BITMAP *bmp, int x1, int y, int x2, ALLEGRO_COLOR color)
{
    al_set_target_bitmap(bmp);
    al_draw_line( x1,  y,  x2, y, color, 1);
}

void vline(ALLEGRO_BITMAP *bmp, int x, int y1, int y2, ALLEGRO_COLOR color)
{
    al_set_target_bitmap(bmp);
    al_draw_line( x,  y1,  x, y2, color, 1);
}

ALLEGRO_COLOR makecol(unsigned char r,unsigned char g,unsigned char b)
{
    return al_map_rgb(r,g,b);
}

void blit(ALLEGRO_BITMAP *source, ALLEGRO_BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height)
{
    al_set_target_bitmap(dest);
    al_draw_bitmap_region(source,source_x,source_y,width,height,dest_x,dest_y,0);
}

void textout(ALLEGRO_BITMAP* screen_buffer, ALLEGRO_FONT* font, const char* text, int x, int y, ALLEGRO_COLOR color)
{
    al_set_target_bitmap(screen_buffer);
    al_draw_text(font, color, x, y, 0, text);
}
void set_clip(ALLEGRO_BITMAP * bitmap, int x1, int y1, int x2, int y2)
{
    al_set_target_bitmap(bitmap);
    al_set_clipping_rectangle(x1, y1, x2 - x1, y2 - y1);
}

void rotate_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y, double angle)
{
    auto w = al_get_bitmap_width(sprite);
    auto h = al_get_bitmap_height(sprite);

    pivot_sprite(bmp, sprite, x + w/2, y + h/2, w/2, h/2, angle);
}

void draw_sprite(ALLEGRO_BITMAP *bmp, ALLEGRO_BITMAP *sprite, int x, int y)
{
 blit(sprite, bmp, 0, 0, x, y, al_get_bitmap_width(sprite), al_get_bitmap_height(sprite));
}
