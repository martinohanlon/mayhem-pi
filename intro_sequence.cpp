#include <stdio.h>
#include <algorithm>
#include "intro_sequence.h"
#include "battle_sequence.h"

const int IntroSequence::mini=150;
const int IntroSequence::maxi=400;

// Classic mayhem joystick controls
/*int *joy_sets[4][5] = { {&joy[0].stick[0].axis[0].d1, &joy[0].stick[0].axis[0].d2, &joy[0].stick[0].axis[1].d1, &joy[0].stick[0].axis[1].d2, &joy[0].button[0].b},
                        {&joy[1].stick[0].axis[0].d1, &joy[1].stick[0].axis[0].d2, &joy[1].stick[0].axis[1].d1, &joy[1].stick[0].axis[1].d2, &joy[1].button[0].b},
                        {&joy[2].stick[0].axis[0].d1, &joy[2].stick[0].axis[0].d2, &joy[2].stick[0].axis[1].d1, &joy[2].stick[0].axis[1].d2, &joy[2].button[0].b},
                        {&joy[3].stick[0].axis[0].d1, &joy[3].stick[0].axis[0].d2, &joy[3].stick[0].axis[1].d1, &joy[3].stick[0].axis[1].d2, &joy[3].button[0].b} };*/

// New joystick controls
int *joy_sets[4][5] = { {&joy[0].stick[0].axis[0].d1, &joy[0].stick[0].axis[0].d2, &joy[0].button[0].b, &joy[0].button[1].b, &joy[0].button[5].b},
                        {&joy[1].stick[0].axis[0].d1, &joy[1].stick[0].axis[0].d2, &joy[1].button[0].b, &joy[1].button[1].b, &joy[1].button[5].b},
                        {&joy[2].stick[0].axis[0].d1, &joy[2].stick[0].axis[0].d2, &joy[2].button[0].b, &joy[2].button[1].b, &joy[2].button[5].b},
                        {&joy[3].stick[0].axis[0].d1, &joy[3].stick[0].axis[0].d2, &joy[3].button[0].b, &joy[3].button[1].b, &joy[3].button[5].b} };

// 0 - 3 : keyboard 
// 4 - 7 : joysticks 
int playercontrols[4] = {0, 1, 2, 3};


IntroSequence::IntroSequence(GameSequence* previous, float zoom, float zoomspeed, int players, int level, int lives, bool dca, bool wall)
	: GameSequence(previous)
{
	iLogo=load_bitmap("assets/intro/intro_logo.bmp",iLogoPalette);
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
	bool canQuickExit=false;
    
    int menuitems = 11;
    int menuselected = 0;
    char menutext[50];
    
	set_palette(iLogoPalette);
	clear_bitmap(screen);
	InterruptTimer::start();

    //setup joysticks    
    if (num_joysticks) 
    {
        // setup player_controls based on number of joysticks, if there are joysticks use them first, otherwise use keyboard
        int playercontrol;
        for (playercontrol = 0; playercontrol < num_joysticks; playercontrol++)
        {
            playercontrols[playercontrol] = 4 + playercontrol;
        }
        for (playercontrol = num_joysticks; playercontrol < NB_MAX_PLAYERS; playercontrol++)
        {
            playercontrols[playercontrol] = playercontrol - num_joysticks;
        }
    }
    
	do
	{
	//	while(InterruptTimer::wasTriggered()) {
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

            if (key[KEY_ESC]&&canQuickExit)
                {
                quickExit=true;
                isRunning=false;
                }
                vsync();
	//	}
	} while(isRunning);
	InterruptTimer::reset();

	bool startgame = false;
    bool exit = false;    

	if (!quickExit)
	{
        black=makecol(0,0,0);
        red=makecol(255,0,0);
        lightred=makecol(255, 75, 75);
        
        while(!startgame && !exit)
        {
            if (num_joysticks) poll_joystick();
            // joystick debug
            /*if (num_joysticks) 
            {
                char debugtext[20];
                sprintf(debugtext, "   %i %i %i ", joy[0].num_sticks, joy[0].num_buttons, joy[0].stick[0].num_axis);
                textout(screen,font, debugtext,5,29,makecol(200,200,200));
                sprintf(debugtext, "   %i %i %i %i %i %i %i %i %i %i %i ", joy[0].button[0].b, joy[0].button[1].b, joy[0].button[2].b, joy[0].button[3].b, joy[0].button[4].b, joy[0].button[5].b, joy[0].button[6].b, joy[0].button[7].b, joy[0].button[8].b, joy[0].button[9].b, joy[0].button[9].b);
                textout(screen,font, debugtext,5,39,makecol(200,200,200));
                sprintf(debugtext, "   %i %i %i %i ", joy[0].stick[1].axis[0].d1, joy[0].stick[1].axis[0].d2, joy[0].stick[1].axis[1].d1, joy[0].stick[1].axis[1].d2);
                textout(screen,font, debugtext,5,49,makecol(200,200,200));
                sprintf(debugtext, "   %i    %i    ", joy[0].stick[1].axis[0].pos, joy[0].stick[1].axis[1].pos);
                textout(screen,font, debugtext,5,59,makecol(200,200,200));
                sprintf(debugtext, "   %s             ", joy[0].stick[1].axis[0].name);
                textout(screen,font, debugtext,5,69,makecol(200,200,200));
                
            }*/

            // TODO - refactor - bit of a hack button 6 is back on an xbox 360 controller!
            if (key[KEY_ESC] || joy[0].button[6].b)
                {
                break;
                exit = true;
                }
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
            if (key[KEY_DOWN] || joy[0].stick[0].axis[1].d2)
            {
                if (menuselected < menuitems - 1) menuselected++;
                else menuselected = 0;
                rest(50);
            }
            if (key[KEY_UP] || joy[0].stick[0].axis[1].d1)
            {
                if (menuselected > 0) menuselected--;
                else menuselected = menuitems - 1;
                rest(50);  
            }
            if (key[KEY_LEFT] || joy[0].stick[0].axis[0].d1)
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
                rest(50);
            }
            if (key[KEY_RIGHT] || joy[0].stick[0].axis[0].d2)
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
                rest(50);
            }
            if (key[KEY_ENTER] || joy[0].button[0].b)
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
                    case 6:
                        update_control(0, maxi+120);
                        break;  
                    case 7:
                        update_control(1, maxi+130);
                        break;  
                    case 8:
                        update_control(2, maxi+140);
                        break;  
                    case 9:
                        update_control(3, maxi+150);
                        break;  
                    case 10:
                        exit = true;
                        break;
                        
                }
                rest(50);
            }

            textout(screen, font, "Press F2/F3/F4 to play for 2/3/4 players or ESC to leave", INTRO_SCREEN_WIDTH/4, maxi+5, red);
            
            textout(screen, font, "Use arrow keys and enter:", INTRO_SCREEN_WIDTH/4, maxi+15, red);

            textout(screen, font, "Start game", INTRO_SCREEN_WIDTH/3, maxi+30, ((menuselected == 0) ? lightred : red));
            
            textout(screen, font, "Options:", INTRO_SCREEN_WIDTH/3, maxi+45, red);
            snprintf(menutext, sizeof(menutext), "   Players - %d   ", playerschoice);
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+55, ((menuselected == 1) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Level - %d   ", levelchoice + 1);
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+65, ((menuselected == 2) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Lives - %d   ", liveschoice);
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+75, ((menuselected == 3) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Use DCA - %s   ", ((dcachoice) ? "yes" : "no" ));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+85, ((menuselected == 4) ? lightred : red));
            
            snprintf(menutext, sizeof(menutext), "   Wall Collision - %s   ", ((wallchoice) ? "yes" : "no" ));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+95, ((menuselected == 5) ? lightred : red));
            
            textout(screen, font, "Controls:", INTRO_SCREEN_WIDTH/3, maxi+110, red);
            snprintf(menutext, sizeof(menutext), "   Player 1 - %s   ", (playercontrols[0] > 3 ? "Joystick" : "Keyboard"));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+120, ((menuselected == 6) ? lightred : red));
            snprintf(menutext, sizeof(menutext), "   Player 2 - %s   ", (playercontrols[1] > 3 ? "Joystick" : "Keyboard"));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+130, ((menuselected == 7) ? lightred : red));
            snprintf(menutext, sizeof(menutext), "   Player 3 - %s   ", (playercontrols[2] > 3 ? "Joystick" : "Keyboard"));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+140, ((menuselected == 8) ? lightred : red));
            snprintf(menutext, sizeof(menutext), "   Player 4 - %s   ", (playercontrols[3] > 3 ? "Joystick" : "Keyboard"));
            textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3, maxi+150, ((menuselected == 9) ? lightred : red));
            
            textout(screen, font, "Exit", INTRO_SCREEN_WIDTH/3, maxi+165, ((menuselected == 10) ? lightred : red));
            
            vsync();
        } 
	}
	clear_bitmap(screen);

	GameSequence * seq;
	if (startgame)
		{
		iZoom=iZoomMax;
		seq=new BattleSequence(this, playerschoice, playerschoice, liveschoice, levelchoice, dcachoice, wallchoice, width, height, playercontrols, joy_sets);
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
}

// this all feels a bit dirty! refactoring is required.
void IntroSequence::update_control(int playerno, int screenpos)
{
    //joystick or keyboard
    if (playercontrols[playerno] > 3) update_joystick(playerno, screenpos);
    else
    {
        textout(screen, font, "not supported ", INTRO_SCREEN_WIDTH/3 + 200, screenpos, lightred);
        rest(200);
        textout(screen, font, "              ", INTRO_SCREEN_WIDTH/3 + 200, screenpos, lightred);
    }
} 

void IntroSequence::update_joystick(int playerno, int screenpos)
{
    char menutext[50];
    char controltext[][10] = {"Left", "Right", "Thrust", "Shield", "Fire"};
    int joystickno = playercontrols[playerno] - 4;
    rest(200);
    for (int control = 0; control < 5; control++)
    {
        // get joystick input
        snprintf(menutext, sizeof(menutext), "   %s   ", controltext[control]);
        textout(screen, font, menutext, INTRO_SCREEN_WIDTH/3 + 200, screenpos, lightred);
        joy_sets[joystickno][control] = get_joystick_action(joystickno);
        textout(screen, font, "   ok       ", INTRO_SCREEN_WIDTH/3 + 200, screenpos, lightred);
        rest(200);        
    }
    textout(screen, font, "            ", INTRO_SCREEN_WIDTH/3 + 200, screenpos, lightred);
}

int *IntroSequence::get_joystick_action(int joystickno)
{
    bool got_action = false;
    int stickno, axisno, buttonno;
    int *checkaxis[100];
    int checkaxiscount = 0;

    poll_joystick();
    // find all the axis which are false as if an axis is already at true we will ignore it, as its probably an inverse analogue trigger (or one already selected)
    for (stickno = 0; stickno < joy[joystickno].num_sticks; stickno++)
    {
        // loop through axis
        for (axisno = 0; axisno < joy[joystickno].stick[stickno].num_axis; axisno++)
        {
            if (!joy[joystickno].stick[stickno].axis[axisno].d1) 
            {
                checkaxis[checkaxiscount] = &joy[joystickno].stick[stickno].axis[axisno].d1;
                checkaxiscount++;
            }
            if (!joy[joystickno].stick[stickno].axis[axisno].d2) 
            {
                checkaxis[checkaxiscount] = &joy[joystickno].stick[stickno].axis[axisno].d2;
                checkaxiscount++;
            }

        }
    }

    while (!got_action)
    {
        poll_joystick();
        // loop through axis
        for (axisno = 0; axisno < checkaxiscount; axisno++)
        {
            if (*checkaxis[axisno]) return checkaxis[axisno];
        }
        // loop through buttons
        for (buttonno = 0; buttonno < joy[joystickno].num_buttons; buttonno++)
        {
            if (joy[joystickno].button[buttonno].b) return &joy[joystickno].button[buttonno].b;
        }
    }
}
