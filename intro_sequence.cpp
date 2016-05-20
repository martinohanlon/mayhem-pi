#include <stdio.h>
#include "intro_sequence.h"
#include "battle_sequence.h"


const int IntroSequence::mini=150;
const int IntroSequence::maxi=400;

IntroSequence::IntroSequence(GameSequence* previous, float zoom, float zoomspeed, int players, int level, int lives, bool dca, bool wall)
	: GameSequence(previous)
{
	iLogo=load_bitmap("intro_logo.bmp",iLogoPalette);
	iZoomMax=iZoom=ftofix(zoom);
	iZoomSpeed=ftofix(zoomspeed);
	iDoublebuffer=create_bitmap(INTRO_SCREEN_WIDTH,maxi-mini);

	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
    
    playerschoice = players;
    levelchoice = level;
    liveschoice = lives;
    dcachoice = dca;
    wallchoice = wall;
}


IntroSequence::~IntroSequence()
{
   if (iLogo)
	   destroy_bitmap(iLogo);
}

GameSequence* IntroSequence::doRun()
{
	bool isRunning=true;
	bool quickExit=false;
	int tempo=0;
	bool canQuickExit=false;
    
    int menuitems = 6;
    int menuselected = 0;
    char menutext[50];
    
	set_palette(iLogoPalette);
	clear_bitmap(screen);
	InterruptTimer::start();

	do
	{
//		while(InterruptTimer::wasTriggered()) {
            iZoom=fixsub(iZoom,iZoomSpeed);
            if (fixtof(iZoom)<1.0)
                {
                iZoom=itofix(1);
                isRunning=false;
                }
            clear_bitmap(iDoublebuffer);
            DrawZoomedLogoInCenter(mini,maxi);
            // draw 2 horizontal lines
            hline(iDoublebuffer, 0,0,INTRO_SCREEN_WIDTH,makecol(255,255,255));
            hline(iDoublebuffer, 0,IntroSequence::maxi-IntroSequence::mini-1,INTRO_SCREEN_WIDTH,makecol(255,255,255));
            // blit to the screen
            blit(iDoublebuffer,screen,0,0,0,mini,INTRO_SCREEN_WIDTH,maxi-mini);
            if (tempo>25)
                {
                tempo=0;
                canQuickExit=true;
                }
            else
                tempo++;

            if (key[KEY_ESC]&&canQuickExit)
                {
                quickExit=true;
                isRunning=false;
                }
            vsync();
//		}
	} while(isRunning);
	InterruptTimer::reset();

	bool startgame = false;
    bool exit = false;

	if (!quickExit)
	{
        tempo=0;
        int black=makecol(0,0,0);
        int red=makecol(255,0,0);
        int lightred=makecol(255, 50, 50);
        int currentcolor=red;
        
        while(!startgame && !exit)
        {

            if(tempo++ == 50)
                {
                tempo=0;
                //if(currentcolor==red)
                    //currentcolor=black;
                //else
                    currentcolor=red;
                }
            if (key[KEY_ESC])
                {
                break;
                exit = true;
                }
            /*if (key[KEY_ENTER])
                {
                choice=2;
                break;
                }*/
            if (key[KEY_F2])
                {
                playerschoice=2;
                startgame = true;
                break;
                }
            if (key[KEY_F3])
                {
                playerschoice=3;
                startgame = true;
                break;
                }
            if (key[KEY_F4])
                {
                playerschoice=4;
                startgame = true;
                break;
                }
            if (key[KEY_F5])
                {
                levelchoice += 1;
                if(levelchoice == NB_LEVELS) levelchoice = 0;
                //short rest to stop multiple key presses
                rest(100);
                }
            if (key[KEY_MINUS_PAD] || key[KEY_MINUS_PAD])
                {
                width = 800;
                height = 600;
                set_gfx_mode( GFX_AUTODETECT, width, height, 0, 0 );
                }
            if (key[KEY_PLUS_PAD] || key[KEY_PLUS_PAD])
                {
                width = 1280;
                height = 800;
                set_gfx_mode( GFX_AUTODETECT, width, height, 0, 0 );
                }
            if (key[KEY_ASTERISK])
                {
                width = 1024;
                height = 768;
                set_gfx_mode( GFX_AUTODETECT, width, height, 0, 0 );
                }
                
            //menu control
            if (key[KEY_DOWN] || key[KEY_X])
            {
                if (menuselected < menuitems - 1) menuselected++;
                rest(100);
            }
            if (key[KEY_UP] || key[KEY_Z])
            {
                if (menuselected > 0) menuselected--;
                rest(100);  
            }
            if (key[KEY_LEFT] || key[KEY_C])
            {
                switch(menuselected) 
                {
                    case 1:
                        if(playerschoice > 2) playerschoice--;
                        break;
                    case 2:
                        if(levelchoice > 0) levelchoice--;
                        break;
                    case 3:
                        if(liveschoice > 0) liveschoice--;
                        break;
                    case 4:
                        dcachoice = !dcachoice;
                        break;
                    case 5:
                        wallchoice = !wallchoice;
                        break;
                }
                rest(100);
            }
            if (key[KEY_RIGHT] || key[KEY_V])
            {
                switch(menuselected) 
                {
                    case 1:
                        if(playerschoice < NB_MAX_PLAYERS) playerschoice++;
                        break;
                    case 2:
                        if(levelchoice < NB_LEVELS - 1) levelchoice++;
                        break;
                    case 3:
                        liveschoice++;
                        break;
                    case 4:
                        dcachoice = !dcachoice;
                        break;
                    case 5:
                        wallchoice = !wallchoice;
                        break;
                }
                rest(100);
            }
            if (key[KEY_ENTER] || key[KEY_G])
            {
                switch(menuselected) 
                {
                    case 0:
                        startgame = true;
                        break;
                    case 1:
                        playerschoice++;
                        if(playerschoice > NB_MAX_PLAYERS) playerschoice = 2;
                        break;
                    case 2:
                        levelchoice++;
                        if (levelchoice == NB_LEVELS) levelchoice = 0;
                        break;
                    case 3:
                        liveschoice++;
                        if (liveschoice == NB_MAXLIVES) liveschoice = 0;
                        break;
                    case 4:
                        dcachoice = !dcachoice;
                        break;
                    case 5:
                        wallchoice = !wallchoice;
                        break;
                }
                rest(100);
            }

            textout_centre(screen, font, "Press F2/F3/F4 to play for 2/3/4 players or ESC to leave", INTRO_SCREEN_WIDTH/2, maxi+5, currentcolor);
            
            textout(screen, font, "Use arrow keys and enter:", INTRO_SCREEN_WIDTH/3, maxi+15, currentcolor);

            textout(screen, font, "Start game", INTRO_SCREEN_WIDTH/3, maxi+25, ((menuselected == 0) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Players - %d   ", playerschoice);
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+35, ((menuselected == 1) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Level - %d   ", levelchoice + 1);
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+45, ((menuselected == 2) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Lives - %d   ", liveschoice);
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+55, ((menuselected == 3) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Use DCA - %s   ", ((dcachoice) ? "yes" : "no" ));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+65, ((menuselected == 4) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Wall Collision - %s   ", ((wallchoice) ? "yes" : "no" ));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+75, ((menuselected == 5) ? lightred : red));
            
            vsync();
        } 
	}
	clear_bitmap(screen);

	GameSequence * seq;
	if (startgame)
		{
		iZoom=iZoomMax;
		seq=new BattleSequence(this, playerschoice, playerschoice, liveschoice, levelchoice, dcachoice, wallchoice, width, height);
		}
	else
		seq=ReturnScreen();

	return seq;
}

void IntroSequence::DrawZoomedLogoInCenter(int y1,int y2)
{
	int width=fixtoi(fixmul(itofix(iLogo->w),iZoom));
	int height=fixtoi(fixmul(itofix(iLogo->h),iZoom));
	int targetwidth=INTRO_SCREEN_WIDTH;
	int targetheight=y2-y1;

	int xs,ys,ws,hs;
	int xd,yd,wd,hd;

	if (width>targetwidth)
		{
		ws=fixtoi(fixdiv(itofix(targetwidth),iZoom));
		xs=(iLogo->w-ws)/2;
		xd=0;
		wd=targetwidth;
		}
	else
		{
		xs=0;
		ws=iLogo->w;
		xd=(targetwidth-width)/2;
		wd=width;
		}

	if (height>targetheight)
		{
		hs=fixtoi(fixdiv(itofix(targetheight),iZoom));
		ys=(iLogo->h-hs)/2;
		yd=0;
		hd=targetheight;
		}
	else
		{
		ys=0;
		hs=iLogo->h;
		yd=(targetheight-height)/2;
		hd=height;
		}
	stretch_blit(iLogo,iDoublebuffer,xs,ys,ws,hs,xd,yd,wd,hd);
	//void stretch_blit(BITMAP *source, BITMAP *dest, int source_x, source_y, source_width, source_height, int dest_x, dest_y, dest_width, dest_height);
}
