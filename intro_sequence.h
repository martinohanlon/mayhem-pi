#ifndef __INTROSEQUENCE_H__
#define __INTROSEQUENCE_H__

#include "game_mgr.h"

class IntroSequence : public GameSequence
{
public:
   IntroSequence(GameSequence* previous, float zoom=10.0, float zoomspeed=0.5, int players=2, int level=0, int lives=10, bool dca=false, bool wall=true);
   ~IntroSequence();
   void DrawZoomedLogoInCenter(int y1,int y2);
private:
   static const int mini, maxi;
   GameSequence* doRun();
   double iZoom;
   double iZoomMax;
   double iZoomSpeed;
   ALLEGRO_BITMAP* iLogo;
#if 0
   PALETTE iLogoPalette;
#endif
   ALLEGRO_BITMAP* iDoublebuffer;

   int width;
   int height;
   
   int playerschoice;
   int levelchoice;
   int liveschoice;
   bool dcachoice;
   bool wallchoice;
   
   void update_control(int playerno, int screenpos);
   void update_joystick(int playerno, int screenpos);
   int *get_joystick_action(int joystickno);
   
   ALLEGRO_COLOR black;
   ALLEGRO_COLOR red;
   ALLEGRO_COLOR lightred;
   
};



#endif
