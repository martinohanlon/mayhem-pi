#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "game_mgr.h"

#include "allegro_compatibility.h"

#include <cstdio>

#define FULLSCREEN 1

#if 0
#ifdef FULLSCREEN
#define GFXOPENARG GFX_AUTODETECT
#else
#define GFXOPENARG GFX_AUTODETECT_WINDOWED
#endif
#endif
volatile int InterruptTimer::timing_counter = -1;
ALLEGRO_TIMER* InterruptTimer::timer = nullptr;

// initialise static members
int GameManager::display_height;
int GameManager::display_width;
int GameManager::native_height;
int GameManager::native_width;
ALLEGRO_DISPLAY* GameManager::display = nullptr;
ALLEGRO_FONT* GameManager::font = nullptr;
ALLEGRO_TIMER* GameManager::timer = nullptr;

void GameManager::Init()
{  
  if(!al_init()) {
     fprintf(stderr, "failed to initialize allegro!\n");
     return;
  }

  if(!al_install_keyboard()) {
     fprintf(stderr, "failed to initialize the keyboard!\n");
     return;
  }

  al_init_image_addon();

  al_init_font_addon(); // initialize the font addon
  al_init_ttf_addon();// initialize the ttf (True Type Font) addon

  GameManager::font = al_load_font("assets/default/PressStart2P.ttf", 8, 0);
  GameManager::timer = al_create_timer(ALLEGRO_BPS_TO_SECS(40));

  if(!GameManager::timer) {
     fprintf(stderr, "failed to create timer!\n");
  }

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

  GameManager::display = al_create_display(display_width, display_height);
  al_set_target_bitmap(al_get_backbuffer(display));

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

GameSequence* GameSequence::run()
{
    auto event_queue = al_create_event_queue();
      if(!event_queue) {
         fprintf(stderr, "failed to create event_queue!\n");
         return nullptr;
      }

      al_register_event_source(event_queue, al_get_display_event_source(GameManager::display));

      al_register_event_source(event_queue, al_get_timer_event_source(GameManager::timer));

      al_register_event_source(event_queue, al_get_keyboard_event_source());

      al_start_timer(GameManager::timer);

      ALLEGRO_BITMAP * screen_buffer;
      screen_buffer = al_create_bitmap(GameManager::display_width, GameManager::display_height);
      al_set_target_bitmap(screen_buffer);
      al_clear_to_color(al_map_rgb(0,0,0));

      bool key_pressed[ALLEGRO_KEY_MAX] = {0};
      bool key_down[ALLEGRO_KEY_MAX] = {0};

      bool doexit = false;
      bool redraw =true;
      bool exit_game = false;
      GameSequence* seq_next = nullptr;
       while(!doexit)
       {
               ALLEGRO_EVENT ev;
               al_wait_for_event(event_queue, &ev);

               if(ev.type == ALLEGRO_EVENT_TIMER) {
                   al_set_target_bitmap(screen_buffer);
                   al_clear_to_color(al_map_rgb(0,0,0));

                  seq_next = doTick(screen_buffer, key_pressed, key_down, &exit_game);
                  for (auto& pressed : key_pressed)
                      pressed = false;
                  redraw = true;

                  doexit = exit_game || seq_next != nullptr ;
               }
               else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                   key_pressed[ev.keyboard.keycode] = true;
                   key_down[ev.keyboard.keycode] = true;
               }
               else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
                  key_pressed[ev.keyboard.keycode] = false;
                  key_down[ev.keyboard.keycode] = false;
               }

               if (redraw && al_is_event_queue_empty(event_queue)) {
                    redraw = false;
                    al_set_target_bitmap(al_get_backbuffer(GameManager::display));
                    al_draw_bitmap(screen_buffer,0,0,0);
                    al_flip_display();
                 }
       }

          al_destroy_event_queue(event_queue);
          al_destroy_bitmap(screen_buffer);
          al_stop_timer(GameManager::timer);

    if (seq_next!=iReturnScreen && iReturnScreen)
        delete iReturnScreen;

    if (exit_game)
        return nullptr;

    return seq_next;
}



 void InterruptTimer::init()
{
        reset();
        timer = al_create_timer(1.0/40.0);
        al_start_timer(timer);
        //start();


}

 void InterruptTimer::sync()
{
    if (timing_counter >= 0)
        timing_counter = al_get_timer_count(timer);

}

 void InterruptTimer::shutdown()
{
     al_destroy_timer(timer);
 }

 bool InterruptTimer::wasTriggered()
{
    if (timing_counter>0)
    {
        timing_counter--;
        if (timing_counter > 2)
            timing_counter = 0;
        return true;
    }
    return false;
}

