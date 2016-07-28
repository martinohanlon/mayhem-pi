#ifndef __GAMEMANAGER_H_
#define __GAMEMANAGER_H_

#include <allegro5/allegro.h>

#define  DEFAULT_WIDTH  1024
#define  DEFAULT_HEIGHT 768

//vsync creates some really erratic results on modern windows systems
//#define USE_VSYNC

class GameSequence
{
public:
   GameSequence(GameSequence *returnScreen)
                      : iReturnScreen(returnScreen) {}
   virtual ~GameSequence(){};
   GameSequence* run() { GameSequence* s=doRun(); if (s!=iReturnScreen && iReturnScreen) delete iReturnScreen; return s; };


protected:
   virtual GameSequence* doRun() = 0 ;
   GameSequence *ReturnScreen() const { return iReturnScreen; };
private:
   GameSequence *iReturnScreen;
};


class GameManager
{
public:
    static void Init();
    static void Shutdown();
    static void Run(GameSequence *aSeq);
    static void ChangeScreenRes(int width, int height);
    static int display_width;
    static int display_height;
    static int native_width;
    static int native_height;
};

class InterruptTimer
{
public:
#if 0
    static void init() { reset(); install_timer(); LOCK_VARIABLE(timing_counter); LOCK_FUNCTION(&InterruptTimer::irq); install_int_ex(&InterruptTimer::irq, BPS_TO_TIMER(40)); };
    static void shutdown() { remove_timer(); };
#else
    static void init();
    static void shutdown();
#endif
    static volatile int timing_counter;
    static ALLEGRO_TIMER* timer;

    inline static void start() { timing_counter = 0; al_start_timer(timer); };
    inline static void reset() { timing_counter = -1; if(timer != nullptr) al_set_timer_count(timer,0); };
    static void irq() { if (timing_counter>=0) ++timing_counter;	};
    static void sync();
    // change to stop triggers building up and game suddenly processing lots of triggers all in 1 go
    static bool wasTriggered();
#if 0
    END_OF_FUNCTION(wasTriggered);
#endif
    //Something wierd is going on here... Under windows 10 you dont get 40 fps, and with the above code you end up with a LOT more..  Something isn't pegging the interupt properly.
    //sstatic bool wasTriggered() { if (timing_counter>0) { timing_counter=0; return true; } return false; };
};


#endif
