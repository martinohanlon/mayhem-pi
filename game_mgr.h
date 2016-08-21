#ifndef __GAMEMANAGER_H_
#define __GAMEMANAGER_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "xc.h"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

#define MAX_NUM_CONTROLLERS 4

class GameSequence {
public:
  GameSequence(GameSequence *returnScreen) : iReturnScreen(returnScreen) {}
  virtual ~GameSequence(){};
  virtual GameSequence *doTick(ALLEGRO_BITMAP *screen_buffer,
                               bool key_pressed[ALLEGRO_KEY_MAX],
                               bool key_down[ALLEGRO_KEY_MAX], bool *exit_game,
                               double dt) {
    return nullptr;
  };
  GameSequence *ReturnScreen() const { return iReturnScreen; };

protected:
  GameSequence *iReturnScreen;
};

class GameManager {
public:
  static void Init();
  static void Shutdown();
  static void Run(GameSequence *aSeq);
  static void ChangeScreenRes(int width, int height);
  static int display_width;
  static int display_height;
  static int native_width;
  static int native_height;
  static ALLEGRO_DISPLAY *display;
  static ALLEGRO_FONT *font;
  static int FPS;
  static XC_STATE *joysticks[MAX_NUM_CONTROLLERS];
  static int num_joysticks_loaded;
};

#endif
