#include "utils.h"

#include "allegro_compatibility.h"

ALLEGRO_BITMAP *create_clear_bitmap(int w, int h) {
  ALLEGRO_BITMAP *buffer;
  buffer = al_create_bitmap(w, h); // place pour big image de fond
  return buffer;
}
