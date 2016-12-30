#ifndef __INTROSEQUENCE_H__
#define __INTROSEQUENCE_H__

#include "game_mgr.h"
#include "mapping_joy.h"
#include "ticktimer.h"

class IntroSequence : public GameSequence {
public:
  IntroSequence(GameSequence *previous, float zoom = 10.0,
                float zoomspeed = 0.5, int players = 2, int level = 0,
                int lives = 10, bool dca = false, bool wall = true);
  ~IntroSequence();
  void DrawZoomedLogoInCenter(int y1, int y2);

private:
  static const int mini, maxi;
  GameSequence *doTick(ALLEGRO_BITMAP *screen_buffer,
                       bool key_pressed[ALLEGRO_KEY_MAX],
                       bool key_down[ALLEGRO_KEY_MAX], bool *exit_game,
                       double dt) override;
  void handle_key_presses(bool key_pressed[ALLEGRO_KEY_MAX], bool *reload,
                          bool *startgame, bool *exit);

  double iZoom;
  double iZoomMax;
  double iZoomSpeed;
  ALLEGRO_BITMAP *iLogo = nullptr;
  ALLEGRO_BITMAP *iDoublebuffer = nullptr;

  int width;
  int height;

  int playerschoice;
  int levelchoice;
  int liveschoice;
  bool dcachoice;
  bool wallchoice;

  void cycle_control(int playerno);
  bool do_js_action(JoyButton button);

  ALLEGRO_COLOR black;
  ALLEGRO_COLOR red;
  ALLEGRO_COLOR lightred;

  bool isRunning = true;
  bool quickExit = false;
  bool canQuickExit = false;

  int menuitems = 32;
  int menuselected = 0;
  char menutext[50];
  TickTimer joystick_action_timer;

  int menu_exit_idx = 0;
  int menu_resolution_idx = 0;
  
  int menu_joy_kbd_idx = 0;
  
  int menu_kbd_layout1_idx = 0;
  int menu_kbd_layout2_idx = 0;
  int menu_kbd_layout3_idx = 0;
  int menu_kbd_layout4_idx = 0;
  int menu_kbd_layout_end = 0;
  
  int menu_joy_layout1_idx = 0;
  int menu_joy_layout2_idx = 0;
  int menu_joy_layout3_idx = 0;
  int menu_joy_layout4_idx = 0;
  int menu_joy_layout_end = 0;

  bool selecting_new_keyboard_button = false;
  bool selecting_new_joystick_button = false;
};

#endif
