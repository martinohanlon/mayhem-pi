#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "game_mgr.h"

#include "xc.h"

#include "allegro_compatibility.h"

#include <cstdio>

#define CHECKFPS

#define SHOWDEBUG

#define FULLSCREEN

#ifdef FULLSCREEN
#define GFXOPENARG ALLEGRO_FULLSCREEN_WINDOW
#else
#define GFXOPENARG ALLEGRO_WINDOWED
#endif

// initialise static members
int GameManager::display_height;
int GameManager::display_width;
int GameManager::native_height;
int GameManager::native_width;
ALLEGRO_DISPLAY *GameManager::display = nullptr;
ALLEGRO_FONT *GameManager::font = nullptr;
int GameManager::FPS = 65;
XC_STATE *GameManager::joysticks[MAX_NUM_CONTROLLERS] = {0};
int GameManager::num_joysticks_loaded = 0;

//debug 
float GameManager::debug_start = 0;
float GameManager::debug_time = 0;

void GameManager::Init() {
  if (!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    return;
  }

  uint32_t version = al_get_allegro_version();
  printf("Allegro started version %i.%i.%i[%i]\n", version >> 24,
      (version >> 16) & 255, (version >> 8) & 255, version & 255);  

  if (!al_install_keyboard()) {
    fprintf(stderr, "failed to initialize the keyboard!\n");
    return;
  }

  al_init_image_addon();
  al_init_primitives_addon();
  al_init_font_addon(); // initialize the font addon
  al_init_ttf_addon();  // initialize the ttf (True Type Font) addon

  GameManager::font = al_load_font("assets/default/PressStart2P.ttf", 8, 0);

  xc_install();

  int i = 0;
  for (i = 0; i < MAX_NUM_CONTROLLERS; i++) {
    XC_STATE *controller = xc_get_state(i);
    if (!controller) {
      break;
    }

    GameManager::joysticks[i] = controller;
  }

  GameManager::num_joysticks_loaded = i;

  printf("Found %d joysticks\n", i);

  if (!al_install_audio()) {
    fprintf(stderr, "failed to initialize audio!\n");
  }

  if (!al_init_acodec_addon()) {
    fprintf(stderr, "failed to initialize audio codecs!\n");
  }

  if (!al_reserve_samples(8)) {
    fprintf(stderr, "failed to reserve samples!\n");
  }

  // get the screen resolution
  if (!get_desktop_resolution(0, &display_width, &display_height)) {
    // failed to get resolution, set to a default
    display_width = DEFAULT_WIDTH;
    display_height = DEFAULT_HEIGHT;
  }

  // set the native display properties
  native_width = display_width;
  native_height = display_height;

  al_set_new_display_flags(GFXOPENARG);

  GameManager::display = al_create_display(display_width, display_height);
  
  // hide mouse pointer
  al_hide_mouse_cursor(GameManager::display);
}

void GameManager::StartDebugTime() {
	GameManager::debug_start = al_get_time();
}

void GameManager::EndDebugTime() {
	GameManager::debug_time = al_get_time() - GameManager::debug_start;
}

void GameManager::ChangeScreenRes(int width, int height) {
  if (al_resize_display(GameManager::display, width, height)) {
    display_width = width;
    display_height = height;
  } else {
    fprintf(stderr, "failed to resize display!\n");
  }
}

void GameManager::Shutdown() {
  al_destroy_display(display);

  for (int i = 0; i < MAX_NUM_CONTROLLERS; i++)
    delete GameManager::joysticks[i];
}

double old_time = 0.0;
double tick_time = 0.0;
double tick_fps = 0.0;

#ifdef CHECKFPS
void draw_fps(ALLEGRO_BITMAP *screen_buffer) {
  double new_time = al_get_time();
  char fps[100];
  #ifdef SHOWDEBUG
  sprintf(fps, "goal fps:%d, draw fps:%.1f, tick ms:%.1f, tick fps: %.1f, debug time %.1f",
          GameManager::FPS, 1.0 / (new_time - old_time), 1000.0 * tick_time,
          tick_fps, 1000 * GameManager::debug_time);
  #else
  sprintf(fps, "fps:%.1f", 1.0 / (new_time - old_time));
  #endif
  textout(screen_buffer, GameManager::font, fps, 105, 5,
          al_map_rgb(200, 200, 200));
  char reso[100];
  sprintf(reso, "%ix%i", GameManager::display_width,
          GameManager::display_height);
  textout(screen_buffer, GameManager::font, reso, 5, 5, al_map_rgb(200, 200, 200));
  old_time = new_time;
}
#else
void draw_fps(ALLEGRO_BITMAP *) {}
#endif

void GameManager::Run(GameSequence *aSeq) {

  auto event_queue = al_create_event_queue();
  if (!event_queue) {
    fprintf(stderr, "failed to create event_queue!\n");
    return;
  }

  al_register_event_source(event_queue,
                           al_get_display_event_source(GameManager::display));

  al_register_event_source(event_queue, al_get_keyboard_event_source());

  al_register_event_source(event_queue, xc_get_event_source());

  ALLEGRO_BITMAP *screen_buffer;
  screen_buffer =
      al_create_bitmap(GameManager::display_width, GameManager::display_height);
  al_set_target_bitmap(screen_buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));

  bool key_pressed[ALLEGRO_KEY_MAX] = {0};
  bool key_down[ALLEGRO_KEY_MAX] = {0};

  bool doexit = false;
  bool exit_game = false;
  GameSequence *seq_next = nullptr;

  double last_time = al_get_time();
  const double delta_min = ALLEGRO_BPS_TO_SECS(GameManager::FPS);

  //joy debug
  /*
  char debug[50];
  int but = 0, axis = 0;
  double pos = 0.0;
  */
  while (!doexit) {

    ALLEGRO_EVENT ev;

    while (al_get_next_event(event_queue, &ev)) {  
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        key_pressed[ev.keyboard.keycode] = true;
        key_down[ev.keyboard.keycode] = true;
      } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        key_pressed[ev.keyboard.keycode] = false;
        key_down[ev.keyboard.keycode] = false;
      } else if (ev.type == XC_EVENT_AXIS || ev.type == XC_EVENT_BUTTON_DOWN ||
                 ev.type == XC_EVENT_BUTTON_UP) {
                   
        //joy debug
        /*
        if (ev.type == XC_EVENT_BUTTON_DOWN) but = ev.joystick.button;
        if (ev.type == XC_EVENT_AXIS) {
          axis = ev.joystick.axis;
          pos = ev.joystick.pos;
        }
        */

        xc_update(ev);
      } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        exit_game = true;
        doexit = true;
      }
    }
    double now = al_get_time();
    bool do_tick = (now - last_time) >= delta_min;
    if (do_tick) {

      al_set_target_bitmap(screen_buffer);
      al_clear_to_color(al_map_rgb(0, 0, 0));

      seq_next = aSeq->doTick(screen_buffer, key_pressed, key_down, &exit_game,
                              (now - last_time));
      for (auto &pressed : key_pressed)
        pressed = false;

      doexit = exit_game || seq_next != nullptr;

      tick_fps = 1.0 / (now - last_time);
      last_time = now;
      tick_time = al_get_time() - now;
    }

    // joy debug
    /*
    sprintf(debug, "%i.%i.%i", but, axis, pos);
    //sprintf(debug, "%s", al_get_joystick_name(GameManager::joysticks[0]->joy));
    textout(screen_buffer, GameManager::font, debug, 605, 5, al_map_rgb(200, 200, 200));
    */

    draw_fps(screen_buffer);
    al_set_target_bitmap(al_get_backbuffer(GameManager::display));
    al_draw_bitmap(screen_buffer, 0, 0, 0);
    al_flip_display();

    if (doexit) {
      if (seq_next != nullptr && seq_next->ReturnScreen() != aSeq)
        delete aSeq;

      if (exit_game)
        break;

      aSeq = seq_next;

      doexit = false;
    }
  }

  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(screen_buffer);
}
