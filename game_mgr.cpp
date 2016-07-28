#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include "game_mgr.h"

#define FULLSCREEN 1

#if 0
#ifdef FULLSCREEN
#define GFXOPENARG GFX_AUTODETECT
#else
#define GFXOPENARG GFX_AUTODETECT_WINDOWED
#endif
#endif
volatile int InterruptTimer::timing_counter;

// initialise static members
int GameManager::display_height;
int GameManager::display_width;
int GameManager::native_height;
int GameManager::native_width;

void GameManager::Init()
{

  al_init();                                            // Initialise Allegro
  InterruptTimer::init();
//#FIXME  set_color_depth(8);                                        // Combien de bitplan
  al_install_keyboard();                                        // Installe le clavier
//#FIXME al_install_joystick(JOY_TYPE_AUTODETECT);                     // Install joystick
  // GP TODO? THROW EXCEPTION?
  al_install_audio();
  //get the screen resolution
  //#FIXME if (get_desktop_resolution(0, &display_width, &display_height) != 0) {
      // failed to get resolution, set to a default
      display_width = DEFAULT_WIDTH;
      display_height = DEFAULT_HEIGHT;
  // }
  //set the native display properties
  native_width = display_width;
  native_height = display_height;

  auto display = al_create_display(display_width, display_height);

  //set_gfx_mode( GFXOPENARG, display_width, display_height, 0, 0 );
  //set_gfx_mode( GFX_AUTODETECT_WINDOWED, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, 0 );          // windowed
}

void GameManager::ChangeScreenRes(int width, int height)
{
    display_width = width;
    display_height = height;
#if 0
    set_gfx_mode( GFXOPENARG, display_width, display_height, 0, 0 );
#endif
}

void GameManager::Shutdown()
{
#if 0
  remove_sound();
#endif
  InterruptTimer::shutdown();
#if 0
  allegro_exit();
#endif
}

void GameManager::Run(GameSequence *aSeq)
{
  while(aSeq)
  {
   aSeq=aSeq->run();
  }
}

