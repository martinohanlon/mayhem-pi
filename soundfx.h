#ifndef __SOUNDFX_H__
#define __SOUNDFX_H__

#include "vaisseau_data.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

struct loopedsfx {
  ALLEGRO_SAMPLE *sfx;
  ALLEGRO_SAMPLE_INSTANCE *instance;
  bool playingFlag;
  double freqStep;
  double startFreq;
  ALLEGRO_SAMPLE_ID sample_id;
};

struct soundfx {
  struct loopedsfx thrust; // loop
  struct loopedsfx shield; // loop
  struct loopedsfx refuel; // loop with a freq twist ;)
  ALLEGRO_SAMPLE *shoot;   // one shot
  ALLEGRO_SAMPLE *boom;    // one shot
  ALLEGRO_SAMPLE *rebound; // one shot
};

int init_soundfx_from_wavfile(struct soundfx *sfx, const char *thrustwav,
                              const char *shieldwav, const char *refuelwav, const char *shootwav,
                              const char *boomwav, const char *rebound);

void cleanup_soundfx(struct soundfx *sfx);
void play_soundfx_from_shipdata(struct soundfx *sfx, struct vaisseau_data *v);

#endif
