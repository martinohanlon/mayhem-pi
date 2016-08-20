#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <allegro5/allegro.h>

#include "platform_data.h"
#include "vaisseau_data.h"

class physics_constants {
public:
  physics_constants(float g, float xfrott, float yfrott, float coeffax,
                    float coeffvx, float coeffay, float coeffvy,
                    float coeffimpact);

public:
  double iG;           // cte gravi
  double iXfrott;      // frottement en x
  double iYfrott;      // frottement en y
  double iCoeffax;     // pour dV = coeffa A
  double iCoeffvx;     // pour dX = coeffv V
  double iCoeffay;     // pour dV = coeffa A
  double iCoeffvy;     // pour dX = coeffv V
  double iCoeffimpact; // when shooted on
};

void calcul_pos(const physics_constants &physics, int nbvaisseau,
                struct vaisseau_data *vaisseau,
                struct platform_data platforms[], int nbplatforms, double dt);
bool test_landed(struct vaisseau_data *vaisseau, struct platform_data *plt);

#endif
