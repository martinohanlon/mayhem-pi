#include "soundfx.h"
#include "allegro5/allegro_audio.h"

void init_loopedsfx(struct loopedsfx *l, const char *wav, double freqStep) {
  l->sfx = al_load_sample(wav);
  l->instance = al_create_sample_instance(l->sfx);
  l->playingFlag = false;
  l->freqStep = freqStep;
  l->startFreq = 1.0;
}

int init_soundfx_from_wavfile(struct soundfx *sfx, const char *thrustwav,
                              const char *shieldwav, const char *refuelwav, const char *shootwav,
                              const char *boomwav, const char *rebound) {
  init_loopedsfx(&(sfx->thrust), thrustwav, 0.0);
  init_loopedsfx(&(sfx->shield), shieldwav, 0.0);
  init_loopedsfx(&(sfx->refuel), refuelwav, 0.005);
  sfx->shoot = al_load_sample(shootwav);
  sfx->boom = al_load_sample(boomwav);
  sfx->rebound = al_load_sample(rebound);
  return !(sfx->thrust.sfx && sfx->shield.sfx && sfx->refuel.sfx &&
           sfx->shoot && sfx->boom && sfx->rebound);
}

void cleanup_soundfx(struct soundfx *sfx) {
  if (sfx->thrust.sfx)
    al_destroy_sample(sfx->thrust.sfx);
  if (sfx->shield.sfx)
    al_destroy_sample(sfx->shield.sfx);
  if (sfx->refuel.sfx)
    al_destroy_sample(sfx->refuel.sfx);
  if (sfx->shoot)
    al_destroy_sample(sfx->shoot);
  if (sfx->boom)
    al_destroy_sample(sfx->boom);
  if (sfx->rebound)
    al_destroy_sample(sfx->rebound);
}

void play_looped_sample(struct loopedsfx *l, bool active) {
  if (!active && !l->playingFlag) {
    return;
  }
  if (active && l->playingFlag) {
    if (l->freqStep != 0.0) {
      l->startFreq += l->freqStep;
      al_set_sample_instance_speed(l->instance, l->startFreq);
    }
    return;
  }

  if (active) {
    al_play_sample(l->sfx, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &l->sample_id);
  } else {
    al_stop_sample(&l->sample_id);
    l->startFreq = 1.0;
  }
  l->playingFlag = active;
}

void play_soundfx_from_shipdata(struct soundfx *sfx, struct vaisseau_data *v) {
  play_looped_sample(&sfx->thrust, (v->thrust > 0));
  play_looped_sample(&sfx->shield, (v->shield && v->shield_force > 0));
  play_looped_sample(&sfx->refuel, (v->refueling));

  if (v->rebound)
    al_play_sample(sfx->rebound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
  if (v->fire_delay)
    al_play_sample(sfx->shoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
  if (v->explode && v->explode_tick == 1) // TODO, fix this is disgusting...
    al_play_sample(sfx->boom, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}
