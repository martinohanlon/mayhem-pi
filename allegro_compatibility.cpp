#include "allegro_compatibility.h"

#include <cmath>

#define PI 3.14159265

allegro_compatibility::allegro_compatibility()
{

}


static void update_pressed_keys()
{
//#FIXME:
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
