#include <stdio.h>
#include <algorithm>
#include "intro_sequence.h"
#include "battle_sequence.h"
#include "allegro_compatibility.h"
#include <allegro5/allegro_primitives.h>

const int IntroSequence::mini=150;
const int IntroSequence::maxi=400;

// Classic mayhem joystick controls
/*int *joy_sets[4][5] = { {&joy[0].stick[0].axis[0].d1, &joy[0].stick[0].axis[0].d2, &joy[0].stick[0].axis[1].d1, &joy[0].stick[0].axis[1].d2, &joy[0].button[0].b},
                        {&joy[1].stick[0].axis[0].d1, &joy[1].stick[0].axis[0].d2, &joy[1].stick[0].axis[1].d1, &joy[1].stick[0].axis[1].d2, &joy[1].button[0].b},
                        {&joy[2].stick[0].axis[0].d1, &joy[2].stick[0].axis[0].d2, &joy[2].stick[0].axis[1].d1, &joy[2].stick[0].axis[1].d2, &joy[2].button[0].b},
                        {&joy[3].stick[0].axis[0].d1, &joy[3].stick[0].axis[0].d2, &joy[3].stick[0].axis[1].d1, &joy[3].stick[0].axis[1].d2, &joy[3].button[0].b} };*/

// New joystick controls
#if 0
int *joy_sets[4][5] = { {&joy[0].stick[0].axis[0].d1, &joy[0].stick[0].axis[0].d2, &joy[0].button[0].b, &joy[0].button[1].b, &joy[0].button[5].b},
                        {&joy[1].stick[0].axis[0].d1, &joy[1].stick[0].axis[0].d2, &joy[1].button[0].b, &joy[1].button[1].b, &joy[1].button[5].b},
                        {&joy[2].stick[0].axis[0].d1, &joy[2].stick[0].axis[0].d2, &joy[2].button[0].b, &joy[2].button[1].b, &joy[2].button[5].b},
                        {&joy[3].stick[0].axis[0].d1, &joy[3].stick[0].axis[0].d2, &joy[3].button[0].b, &joy[3].button[1].b, &joy[3].button[5].b} };
#else
int *joy_sets[4][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
#endif
// 0 - 3 : keyboard 
// 4 - 7 : joysticks 
int playercontrols[4] = {0, 1, 2, 3};

IntroSequence::IntroSequence(GameSequence* previous, float zoom, float zoomspeed, int players, int level, int lives, bool dca, bool wall)
	: GameSequence(previous)
{
	width = GameManager::display_width;
	height = GameManager::display_height;
    
    iLogo=al_load_bitmap("assets/intro/intro_logo.bmp");
    iZoomMax=iZoom=(zoom);
    iZoomSpeed=(zoomspeed);
    iDoublebuffer=al_create_bitmap(width,maxi-mini);

	playerschoice = players;
    levelchoice = level;
    liveschoice = lives;
    dcachoice = dca;
    wallchoice = wall;

    
}

IntroSequence::~IntroSequence()
{
   if (iLogo)
       al_destroy_bitmap(iLogo);
}

GameSequence* IntroSequence::doTick(ALLEGRO_BITMAP* screen_buffer, bool key_pressed[])
{
    if (isRunning)
    {
            iZoom=(iZoom - iZoomSpeed);
            if (iZoom<1.0)
                {
                iZoom=1;
                isRunning=false;
                }

            clear_bitmap(iDoublebuffer);
            DrawZoomedLogoInCenter(mini,maxi);
            // draw 2 horizontal lines
            hline(iDoublebuffer, 0,0,width,makecol(255,255,255));
            hline(iDoublebuffer, 0,IntroSequence::maxi-IntroSequence::mini-1,width,makecol(255,255,255));

            // blit to the screen
            blit(iDoublebuffer,screen_buffer,0,0,0,mini,width,maxi-mini);

            if (key_pressed[ALLEGRO_KEY_ESCAPE]&&canQuickExit)
            {
                quickExit=true;
                isRunning=false;
            }

            return nullptr;
     }

    bool startgame = false;
    bool exit = false;
    bool reload = false;

    if (!quickExit)
    {
        black=al_map_rgb(0,0,0);
        red=al_map_rgb(255,0,0);
        lightred=al_map_rgb(255, 75, 75);
#if 0
                if (num_joysticks) poll_joystick();
#endif
                // joystick debug
                /*if (num_joysticks)
                {
                    char debugtext[20];
                    sprintf(debugtext, "   %i %i %i ", joy[0].num_sticks, joy[0].num_buttons, joy[0].stick[0].num_axis);
                    textout(screen_buffer,font, debugtext,5,29,makecol(200,200,200));
                    sprintf(debugtext, "   %i %i %i %i %i %i %i %i %i %i %i ", joy[0].button[0].b, joy[0].button[1].b, joy[0].button[2].b, joy[0].button[3].b, joy[0].button[4].b, joy[0].button[5].b, joy[0].button[6].b, joy[0].button[7].b, joy[0].button[8].b, joy[0].button[9].b, joy[0].button[9].b);
                    textout(screen_buffer,font, debugtext,5,39,makecol(200,200,200));
                    sprintf(debugtext, "   %i %i %i %i ", joy[0].stick[1].axis[0].d1, joy[0].stick[1].axis[0].d2, joy[0].stick[1].axis[1].d1, joy[0].stick[1].axis[1].d2);
                    textout(screen_buffer,font, debugtext,5,49,makecol(200,200,200));
                    sprintf(debugtext, "   %i    %i    ", joy[0].stick[1].axis[0].pos, joy[0].stick[1].axis[1].pos);
                    textout(screen_buffer,font, debugtext,5,59,makecol(200,200,200));
                    sprintf(debugtext, "   %s             ", joy[0].stick[1].axis[0].name);
                    textout(screen_buffer,font, debugtext,5,69,makecol(200,200,200));

                }*/

                // TODO - refactor - bit of a hack button 6 is back on an xbox 360 controller!
                if (key_pressed[ALLEGRO_KEY_ESCAPE] /*|| joy[0].button[6].b #FIXME*/)
                {
                    exit = true;
                }
                if (key_pressed[ALLEGRO_KEY_F2])
                {
                    playerschoice=2;
                    startgame = true;
                }
                if (key_pressed[ALLEGRO_KEY_F3])
                {
                    playerschoice=3;
                    startgame = true;
                }
                if (key_pressed[ALLEGRO_KEY_F4])
                {
                    playerschoice=4;
                    startgame = true;
                }
                // get out of the interupt loop
                if (startgame || exit || reload)
                {
                    //break;
                }

                //menu control
                if (key_pressed[ALLEGRO_KEY_DOWN] /*|| joy[0].stick[0].axis[1].d2 #FIXME */)
                {
                    if (menuselected < menuitems - 1) menuselected++;
                    else menuselected = 0;
                }
                if (key_pressed[ALLEGRO_KEY_UP] /*|| joy[0].stick[0].axis[1].d1 #FIXME */)
                {
                    if (menuselected > 0) menuselected--;
                    else menuselected = menuitems - 1;
                }
                if (key_pressed[ALLEGRO_KEY_LEFT] /*|| joy[0].stick[0].axis[0].d1 #FIXME */)
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
                    al_rest(ALLEGRO_MSECS_TO_SECS(150));
                }
                if (key_pressed[ALLEGRO_KEY_RIGHT] /*|| joy[0].stick[0].axis[0].d2 #FIXME */)
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
                    al_rest(ALLEGRO_MSECS_TO_SECS(150));
                }
                if (key_pressed[ALLEGRO_KEY_ENTER] /*|| joy[0].button[0].b #FIXME */)
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
                            if (width == GameManager::native_width && height == GameManager::native_height)
                                GameManager::ChangeScreenRes(1024, 768);
                            else
                                GameManager::ChangeScreenRes(GameManager::native_width, GameManager::native_height);
                            reload = true;
                            break;
                        case 11:
                            exit = true;
                            break;

                    }
                    al_rest(ALLEGRO_MSECS_TO_SECS(150));
                }

                auto font = GameManager::font;
                textout(screen_buffer, GameManager::font, "Press F2/F3/F4 to play for 2/3/4 players or ESC to leave", width/4, maxi+5, red);

                textout(screen_buffer, font, "Use arrow keys and enter:", width/4, maxi+15, red);

                textout(screen_buffer, font, "Start game", width/3, maxi+30, ((menuselected == 0) ? lightred : red));

                textout(screen_buffer, font, "Options:", width/3, maxi+45, red);
                snprintf(menutext, sizeof(menutext), "   Players - %d   ", playerschoice);
                textout(screen_buffer, font, menutext, width/3, maxi+55, ((menuselected == 1) ? lightred : red));

                snprintf(menutext, sizeof(menutext), "   Level - %d   ", levelchoice + 1);
                textout(screen_buffer, font, menutext, width/3, maxi+65, ((menuselected == 2) ? lightred : red));

                snprintf(menutext, sizeof(menutext), "   Lives - %d   ", liveschoice);
                textout(screen_buffer, font, menutext, width/3, maxi+75, ((menuselected == 3) ? lightred : red));

                snprintf(menutext, sizeof(menutext), "   Use DCA - %s   ", ((dcachoice) ? "yes" : "no" ));
                textout(screen_buffer, font, menutext, width/3, maxi+85, ((menuselected == 4) ? lightred : red));

                snprintf(menutext, sizeof(menutext), "   Wall Collision - %s   ", ((wallchoice) ? "yes" : "no" ));
                textout(screen_buffer, font, menutext, width/3, maxi+95, ((menuselected == 5) ? lightred : red));

                textout(screen_buffer, font, "Controls:", width/3, maxi+110, red);
                snprintf(menutext, sizeof(menutext), "   Player 1 - %s   ", (playercontrols[0] > 3 ? "Joystick" : "Keyboard"));
                textout(screen_buffer, font, menutext, width/3, maxi+120, ((menuselected == 6) ? lightred : red));
                snprintf(menutext, sizeof(menutext), "   Player 2 - %s   ", (playercontrols[1] > 3 ? "Joystick" : "Keyboard"));
                textout(screen_buffer, font, menutext, width/3, maxi+130, ((menuselected == 7) ? lightred : red));
                snprintf(menutext, sizeof(menutext), "   Player 3 - %s   ", (playercontrols[2] > 3 ? "Joystick" : "Keyboard"));
                textout(screen_buffer, font, menutext, width/3, maxi+140, ((menuselected == 8) ? lightred : red));
                snprintf(menutext, sizeof(menutext), "   Player 4 - %s   ", (playercontrols[3] > 3 ? "Joystick" : "Keyboard"));
                textout(screen_buffer, font, menutext, width/3, maxi+150, ((menuselected == 9) ? lightred : red));

                snprintf(menutext, sizeof(menutext), "Resolution (%ix%i)   ", width, height);
                textout(screen_buffer, font, menutext, width/3, maxi+165, red);

                if (width == GameManager::native_width && height == GameManager::native_height)
                    snprintf(menutext, sizeof(menutext), "   Switch to Low - 1024x768   ");
                else
                    snprintf(menutext, sizeof(menutext), "   Switch to Native - %ix%i   ", GameManager::native_width, GameManager::native_height);
                textout(screen_buffer, font, menutext, width/3, maxi+175, ((menuselected == 10) ? lightred : red));

                textout(screen_buffer, font, "Exit", width/3, maxi+190, ((menuselected == 11) ? lightred : red));

                // blit the screen buffer to the 'actual' screen
                //blit(screen_buffer, screen, 0, 0, 0, 0, width, height);
    }


#if 0
    clear_bitmap(screen);
    destroy_bitmap(screen_buffer);
#endif

    GameSequence * seq = nullptr;
    if (startgame)
        {
        iZoom=iZoomMax;
        seq=new BattleSequence(this, playerschoice, playerschoice, liveschoice, levelchoice, dcachoice, wallchoice, width, height, playercontrols, joy_sets);
        }
    else if (reload)
        seq=new IntroSequence(NULL, 10.0, 0.5, playerschoice, levelchoice, liveschoice, dcachoice, wallchoice);
    else
        seq=ReturnScreen();

    return seq;

}


GameSequence* IntroSequence::doRun()
{
    return nullptr;
}

void IntroSequence::DrawZoomedLogoInCenter(int y1,int y2)
{
    int logowidth=fixtoi(fixmul(itofix(al_get_bitmap_width(iLogo)),iZoom));
    int logoheight=fixtoi(fixmul(itofix(al_get_bitmap_height(iLogo)),iZoom));
	int targetwidth=width;
	int targetheight=y2-y1;

	int xs,ys,ws,hs;
	int xd,yd,wd,hd;

	if (logowidth>targetwidth)
		{
		ws=fixtoi(fixdiv(itofix(targetwidth),iZoom));
        xs=(al_get_bitmap_width(iLogo)-ws)/2;
		xd=0;
		wd=targetwidth;
		}
	else
		{
		xs=0;
        ws=al_get_bitmap_width(iLogo);
		xd=(targetwidth-logowidth)/2;
		wd=logowidth;
		}

	if (logoheight>targetheight)
		{
		hs=fixtoi(fixdiv(itofix(targetheight),iZoom));
        ys=(al_get_bitmap_height(iLogo))/2;
		yd=0;
		hd=targetheight;
		}
	else
		{
		ys=0;
        hs=al_get_bitmap_height(iLogo);
		yd=(targetheight-logoheight)/2;
		hd=logoheight;
		}

    //#FIXME: do stretch_blo stretch_blit(iLogo,iDoublebuffer,xs,ys,ws,hs,xd,yd,wd,hd);
    blit(iLogo,iDoublebuffer,xs,ys,ws,hs,xd,yd);

}

// this all feels a bit dirty! refactoring is required.
void IntroSequence::update_control(int playerno, int screenpos)
{
    //joystick or keyboard
    if (playercontrols[playerno] > 3) update_joystick(playerno, screenpos);
    else
    {
        //#FIXME textout(screen, font, "not supported ", width/3 + 200, screenpos, lightred);
        al_rest(ALLEGRO_MSECS_TO_SECS(200));
        //#FIXME textout(screen, font, "              ", width/3 + 200, screenpos, lightred);
    }
} 

void IntroSequence::update_joystick(int playerno, int screenpos)
{
    char menutext[50];
    char controltext[][10] = {"Left", "Right", "Thrust", "Shield", "Fire"};
    int joystickno = playercontrols[playerno] - 4;
    al_rest(ALLEGRO_MSECS_TO_SECS(200));
    for (int control = 0; control < 5; control++)
    {
        // get joystick input
        snprintf(menutext, sizeof(menutext), "   %s   ", controltext[control]);
        //#FIXME textout(screen, font, menutext, width/3 + 200, screenpos, lightred);
        joy_sets[joystickno][control] = get_joystick_action(joystickno);
        //#FIXME textout(screen, font, "   ok       ", width/3 + 200, screenpos, lightred);
        al_rest(ALLEGRO_MSECS_TO_SECS(200));
    }
    //#FIXME textout(screen, font, "            ", width/3 + 200, screenpos, lightred);
}

int *IntroSequence::get_joystick_action(int joystickno)
{
    bool got_action = false;
    int stickno, axisno, buttonno;
    int *checkaxis[100];
    int checkaxiscount = 0;

    //#FIXME poll_joystick();
    // find all the axis which are false as if an axis is already at true we will ignore it, as its probably an inverse analogue trigger (or one already selected)
   #if 0
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
#endif
    while (!got_action)
    {
//#FIXME poll_joystick();
        // loop through axis
        for (axisno = 0; axisno < checkaxiscount; axisno++)
        {
            if (*checkaxis[axisno]) return checkaxis[axisno];
        }
        // loop through buttons
   #if 0
        for (buttonno = 0; buttonno < joy[joystickno].num_buttons; buttonno++)
        {
            if (joy[joystickno].button[buttonno].b) return &joy[joystickno].button[buttonno].b;
        }
#endif
    }
}
