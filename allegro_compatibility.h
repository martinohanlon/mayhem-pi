#ifndef ALLEGRO_COMPATIBILITY_H
#define ALLEGRO_COMPATIBILITY_H

#include <allegro5/allegro.h>

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

#endif // ALLEGRO_COMPATIBILITY_H
