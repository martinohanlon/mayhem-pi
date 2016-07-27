#ifndef __GAMEMANAGER_H_
#define __GAMEMANAGER_H_

#include <allegro.h>

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
    static void init() { reset(); install_timer(); LOCK_VARIABLE(timing_counter); LOCK_FUNCTION(&InterruptTimer::irq); install_int_ex(&InterruptTimer::irq, BPS_TO_TIMER(40)); };
    static void shutdown() { remove_timer(); };
	static volatile int timing_counter;
	inline static void start() { timing_counter = 0; };
	inline static void reset() { timing_counter = -1; };
	static void irq() { if (timing_counter>=0) ++timing_counter;	};
    // change to stop triggers building up and game suddenly processing lots of triggers all in 1 go
	static bool wasTriggered() { if (timing_counter>0) { timing_counter--; if (timing_counter > 2) timing_counter = 0; return true; } return false; };
    END_OF_FUNCTION(wasTriggered);
    //Something wierd is going on here... Under windows 10 you dont get 40 fps, and with the above code you end up with a LOT more..  Something isn't pegging the interupt properly.
    //sstatic bool wasTriggered() { if (timing_counter>0) { timing_counter=0; return true; } return false; };
};


#endif
