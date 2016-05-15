#ifndef __INTROSEQUENCE_H__
#define __INTROSEQUENCE_H__

#include "game_mgr.h"

#define INTRO_SCREEN_WIDTH 1024
#define INTRO_SCREEN_HEIGHT 768

class IntroSequence : public GameSequence
{
public:
   IntroSequence(GameSequence* previous, float zoom=10.0, float zoomspeed=0.5, int level=0, int lives=10, bool dca=false, bool wall=true);
   ~IntroSequence();
   void DrawZoomedLogoInCenter(int y1,int y2);
private:
   static const int mini, maxi;
   GameSequence* doRun();
   fixed iZoom;
   fixed iZoomMax;
   fixed iZoomSpeed;
   BITMAP* iLogo;
   PALETTE iLogoPalette;
   BITMAP* iDoublebuffer;

   int width;
   int height;
   
   int levelchoice;
   int liveschoice;
   bool dcachoice;
   bool wallchoice;
};

#endif
