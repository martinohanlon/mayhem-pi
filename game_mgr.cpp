#include <allegro.h>

#include "game_mgr.h"

#define FULLSCREEN 1

#ifdef FULLSCREEN
#define GFXOPENARG GFX_AUTODETECT
#else
#define GFXOPENARG GFX_AUTODETECT_WINDOWED
#endif

volatile int InterruptTimer::timing_counter;

// initialise static members
int GameManager::display_height;
int GameManager::display_width;
int GameManager::native_height;
int GameManager::native_width;

void GameManager::Init()
{
  allegro_init();                                            // Initialise Allegro
  InterruptTimer::init();
  set_color_depth(8);                                        // Combien de bitplan
  install_keyboard();                                        // Installe le clavier
  install_joystick(JOY_TYPE_AUTODETECT);                     // Install joystick
  // GP TODO? THROW EXCEPTION?
  install_sound(DIGI_AUTODETECT , MIDI_AUTODETECT , NULL);
  //get the screen resolution
  if (get_desktop_resolution(&display_width, &display_height) != 0) {
      // failed to get resolution, set to a default
      display_width = DEFAULT_WIDTH;
      display_height = DEFAULT_HEIGHT;
  }
  //set the native display properties
  native_width = display_width;
  native_height = display_height;
  set_gfx_mode( GFXOPENARG, display_width, display_height, 0, 0 );
  //set_gfx_mode( GFX_AUTODETECT_WINDOWED, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, 0 );          // windowed
}

void GameManager::ChangeScreenRes(int width, int height)
{
    display_width = width;
    display_height = height;
    set_gfx_mode( GFXOPENARG, display_width, display_height, 0, 0 );
}

void GameManager::Shutdown()
{
  remove_sound();
  InterruptTimer::shutdown();
  allegro_exit();
}

void GameManager::Run(GameSequence *aSeq)
{
  while(aSeq)
  {
   aSeq=aSeq->run();
  }
}

