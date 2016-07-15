#include <string.h>
#include <stdio.h>

#include "battle_sequence.h"
#include "platform_data.h"




//------------------//
// LEVEL VARIABLES  //
//------------------//

//LEVEL 1
struct platform_data platforms1[] =
    { { 464, 513, 333 },	
    { 60, 127, 1045 },
    { 428, 497, 531 },	
    { 504, 568, 985 }, 
    { 178, 241, 875 },
    { 8, 37, 187 },
    { 302, 351, 271 },
    { 434, 521, 835 },
    { 499, 586, 1165 },
    { 68, 145, 1181 } };
int numplatforms1 = 10;
struct edge_data edgedata = {0, 791, 0, 1500, false, false};
struct level_ship_assets shipsassets[4] = 
    { {"assets/default/ship1_256c.bmp", "assets/default/ship1_thrust_256c.bmp", "assets/default/ship1_thrust2_256c.bmp", "assets/default/ship1_shield_256c.bmp",
       "assets/default/sfx_boom.WAV", "assets/default/sfx_loop_refuel.WAV", "assets/default/sfx_loop_shield.WAV", "assets/default/sfx_loop_thrust.WAV", "assets/default/sfx_rebound.WAV", "assets/default/sfx_shoot.WAV"},
      {"assets/default/ship2_256c.bmp", "assets/default/ship2_thrust_256c.bmp", "assets/default/ship2_thrust2_256c.bmp", "assets/default/ship2_shield_256c.bmp",
       "assets/default/sfx_boom.WAV", "assets/default/sfx_loop_refuel.WAV", "assets/default/sfx_loop_shield.WAV", "assets/default/sfx_loop_thrust.WAV", "assets/default/sfx_rebound.WAV", "assets/default/sfx_shoot.WAV"},
      {"assets/default/ship3_256c.bmp", "assets/default/ship3_thrust_256c.bmp", "assets/default/ship3_thrust2_256c.bmp", "assets/default/ship3_shield_256c.bmp",
       "assets/default/sfx_boom.WAV", "assets/default/sfx_loop_refuel.WAV", "assets/default/sfx_loop_shield.WAV", "assets/default/sfx_loop_thrust.WAV", "assets/default/sfx_rebound.WAV", "assets/default/sfx_shoot.WAV"},
      {"assets/default/ship4_256c.bmp", "assets/default/ship4_thrust_256c.bmp", "assets/default/ship4_thrust2_256c.bmp", "assets/default/ship4_shield_256c.bmp",
       "assets/default/sfx_boom.WAV", "assets/default/sfx_loop_refuel.WAV", "assets/default/sfx_loop_shield.WAV", "assets/default/sfx_loop_thrust.WAV", "assets/default/sfx_rebound.WAV", "assets/default/sfx_shoot.WAV"} };
int particle_color_rgb[3] = {255, 255, 255};
struct option_sprite option_sprites[NB_OPT_TYPE] = { {"assets/default/Option1.bmp"}, {"assets/default/Option2.bmp"}, {"assets/default/Option3.bmp"}, {"assets/default/Option4.bmp"}, {"assets/default/Option5.bmp"} }; 

//LEVEL 2
struct platform_data platforms2[] =
    { { 201, 259, 175 },
    { 21, 92, 1087 }, 
    { 552, 615, 513 },
    { 468, 525, 915 },
    { 546, 599, 327 },
    { 660, 697, 447 },
    { 350, 435, 621 },
    { 596, 697, 1141 } };
int numplatforms2 = 8;

//LEVEL 3
struct platform_data platforms3[] =
    { { 14, 65, 111 },
    { 38, 93, 1121 }, 
    { 713, 760, 231 },
    { 473, 540, 617 },
    { 565, 616, 459 },
    { 343, 398, 207 },
    { 316, 385, 805 },
    { 492, 548, 987 },
    { 66, 145, 1180 } };
int numplatforms3 = 9;

//LEVEL 4
struct platform_data platforms4[] =
    { { 19, 69, 111 },
    { 32, 84, 1121 }, 
    { 705, 755, 231 },
    { 487, 547, 617 },
    { 556, 607, 459 },
    { 344, 393, 207 },
    { 326, 377, 805 },
    { 502, 554, 987 },
    { 66, 145, 1180 } };
int numplatforms4 = 9;

//LEVEL 5
struct platform_data platforms5[] =
    { { 504, 568, 985 }, 
    { 464, 513, 333 },	
    { 428, 497, 531 },	
    { 178, 241, 875 },
    { 8, 37, 187 },
    { 302, 351, 271 },
    { 434, 521, 835 },
    { 60, 127, 1045 },
    { 348, 377, 1089 },
    { 499, 586, 1165 },
    { 68, 145, 1181 } };
int numplatforms5 = 11;
struct edge_data edgedata5 = {0, 791, 0, 1500, true, false};

//LEVEL 6
struct platform_data platforms6[] =
    { { 19, 69, 111 },
    { 32, 84, 1121 }, 
    { 556, 607, 459 },
    { 487, 547, 617 },
    { 705, 755, 231 },
    { 344, 393, 207 },
    { 326, 377, 805 },
    { 502, 554, 987 },
    { 66, 145, 1180 } };
int numplatforms6 = 9;
struct edge_data edgedata6 = {0, 791, 0, 1500, true, false};

// init currentlevel with level
BattleSequence::BattleSequence(GameSequence *previous, int nbviews, int nbplayers, int nblives, int levelno, bool usedca, bool wallcollision, int s_width, int s_height, int player_controls[], int *joy_sets[][5])
  : GameSequence(previous),moon_physics(0.07,0.984,0.99,0.6,0.6,0.6,0.6,0.2)
#ifdef __NET_SUPPORT__
     , gameclient(3000,"localhost"), gameserver(3000)
#endif
{
    screen_width = s_width;
    screen_height = s_height;

    nb_views = nbviews;
    nb_players = nbplayers;
    nb_lives = nblives;
    level_no = levelno;
    currentlevel=&levels[level_no];
    use_dca = usedca;
    wall_collision = wallcollision;

    InitLevelData();
    InitMappingAndControls(player_controls, joy_sets);
    InitAllSpriteGfx();
    InitSoundFx();
    InitPlayerInfo();
    InitPlayerViews();

    // TODO ASSERT?
    load_level(currentlevel, screen_width, screen_height);
}

BattleSequence::~BattleSequence()
{
    clean_sprite_buffer_screen();
    // stop sound
    cleanup_soundfx(&sounds[0]);
    cleanup_soundfx(&sounds[1]);
    if(nb_views>=3)
        cleanup_soundfx(&sounds[2]);
    if(nb_views>=4)
        cleanup_soundfx(&sounds[3]);

    int i;
    for(i=0;i<nb_views;i++)		// cleanup buffers for each player ship
        clean_player_view(&views[i]);

    for(i=0;i<nb_players;i++)		// cleanup buffers for each player ship
        clean_vaisseau_data(&vaisseaux[i]);

    for(i=0;i<NB_MAX_TYPE_VAISSEAU;i++)	// cleanup the buffers for each ship type
        cleanup_vaisseau_gfx(&gfx_vaisseaux[i]);

    cleanup_sprite_explosion();
    unload_option(opt);
    unload_level(currentlevel);
}

void BattleSequence::InitLevelData()
{
    //initialise level data    
    switch(level_no) 
    {
        case 0:
            init_level_data(&levels[0],"assets/level1/Mayhem_Level1_Map_256c.bmp", "assets/level1/Mini_map1.bmp", "assets/level1/Mayhem_Level1_Map_256c.bmp", platforms1, numplatforms1, edgedata, shipsassets, "assets/default/Sprite_explosion.bmp", use_dca, wall_collision, particle_color_rgb);
                                                // x    y  area  delay
            init_level_dca(&(&levels[0])->alldca[0], 766, 85, 150, 25);
            init_level_dca(&(&levels[0])->alldca[1], 170, 481, 90, 25);
            break;
        case 1:
            init_level_data(&levels[1],"assets/level2/Mayhem_Level2_Map_256c.bmp", "assets/level2/Mini_map2.bmp", "assets/level2/Mayhem_Level2_Map_256c.bmp", platforms2, numplatforms2, edgedata, shipsassets, "assets/default/Sprite_explosion.bmp", use_dca, wall_collision, particle_color_rgb);
            init_level_dca(&(&levels[1])->alldca[0], 647, 273, 150, 25);
            init_level_dca(&(&levels[1])->alldca[1], 267, 947, 90, 25);
            break;
        case 2:
            init_level_data(&levels[2],"assets/level3/Mayhem_Level3_Map_256c.bmp", "assets/level3/Mini_map3.bmp", "assets/level3/Mayhem_Level3_Map_256c.bmp", platforms3, numplatforms3, edgedata, shipsassets, "assets/default/Sprite_explosion.bmp", use_dca, wall_collision, particle_color_rgb);
            init_level_dca(&(&levels[2])->alldca[0], 180, 555, 90, 25);
            init_level_dca(&(&levels[2])->alldca[1], 152, 1012, 90, 25);
            break;
        case 3:
            init_level_data(&levels[3],"assets/level4/Mayhem_Level4_Map_256c.bmp", "assets/level4/Mini_map4.bmp", "assets/level4/Mayhem_Level4_Map_256c.bmp", platforms4, numplatforms4, edgedata, shipsassets, "assets/default/Sprite_explosion.bmp", use_dca, wall_collision, particle_color_rgb);
            init_level_dca(&(&levels[3])->alldca[0], 651, 747, 90, 25);
            init_level_dca(&(&levels[3])->alldca[1], 29, 575, 150, 25);
            break;
        case 4:
            init_level_data(&levels[4],"assets/level5/Mayhem_Level5_Map_256c.bmp", "assets/level5/Mini_map5.bmp", "assets/level5/Mayhem_Level5_Map_256c.bmp", platforms5, numplatforms5, edgedata5, shipsassets, "assets/default/Sprite_explosion.bmp", use_dca, wall_collision, particle_color_rgb);
            init_level_dca(&(&levels[4])->alldca[0], 151, 632, 90, 25);
            init_level_dca(&(&levels[4])->alldca[1], 756, 709, 150, 25);
            break;
        case 5:
            init_level_data(&levels[5],"assets/level6/Mayhem_Level6_Map_256c.bmp", "assets/level6/Mini_map6.bmp", "assets/level6/Mayhem_Level6_Collision.bmp", platforms6, numplatforms6, edgedata6, shipsassets, "assets/default/Sprite_explosion.bmp", use_dca, wall_collision, particle_color_rgb);
            init_level_dca(&(&levels[5])->alldca[0], 58, 429, 150, 25);
            init_level_dca(&(&levels[5])->alldca[1], 361, 347, 90, 25);
            break;
    }

}

void BattleSequence::InitMappingAndControls(int player_controls[], int *joy_sets[][5])
{
    // init commands assigning either keyboard or joystick control mappings
    int joystickno;
    for (int playerno=0; playerno < nb_views; playerno++) 
    {
        //joystick or keyboard? 0-3 = keyboard 4-7 = joystick
        if (player_controls[playerno] > 3)
        {
            joystickno = player_controls[playerno] - 4;
            init_mapping_joy(&joyvaisseau[playerno], joy_sets, joystickno);
            commands[playerno].joymap = &joyvaisseau[playerno];
            commands[playerno].control_type = CONTROL_JOY;
        } 
        else
        {
            init_mapping_key(&keyvaisseau[playerno], player_controls[playerno]);
            commands[playerno].keymap = &keyvaisseau[playerno];
            commands[playerno].control_type = CONTROL_KEY;
        }
        commands[playerno].controlled_ship=&vaisseaux[playerno];
    }
}

void BattleSequence::InitAllSpriteGfx()
{
    // get the ship sprites for this level
    struct level_ship_assets * assets = currentlevel->shipsassets;
    // init the gfx for the first vaisseau type
    init_vaisseau_gfx_from_file(&gfx_vaisseaux[0], assets[0].normalsprite, assets[0].thrustsprite, assets[0].thrust2sprite, assets[0].shieldsprite);
    init_vaisseau_gfx_from_file(&gfx_vaisseaux[1], assets[1].normalsprite, assets[1].thrustsprite, assets[1].thrust2sprite, assets[1].shieldsprite);
    init_vaisseau_gfx_from_file(&gfx_vaisseaux[2], assets[2].normalsprite, assets[2].thrustsprite, assets[2].thrust2sprite, assets[2].shieldsprite);
    init_vaisseau_gfx_from_file(&gfx_vaisseaux[3], assets[3].normalsprite, assets[3].thrustsprite, assets[3].thrust2sprite, assets[3].shieldsprite);
    init_sprite_explosion(currentlevel->explosion_spritename);

    for(int i=0;i<nb_players;i++)
        init_vaisseau_data(&vaisseaux[i], &gfx_vaisseaux[i], 
                           VAISSEAU_MASS,
                           VAISSEAU_THRUST_MAX,
                           VAISSEAU_ANGLESTEP,
                           VAISSEAU_MAX_FUEL,
                           VAISSEAU_SPEED_FUEL_DOWN,
                           VAISSEAU_SPEED_FUEL_UP,
                           VAISSEAU_MAX_SHIELD_FORCE,
                           VAISSEAU_SPEED_SHIELD_FORCE_DOWN,
                           VAISSEAU_SPEED_SHIELD_FORCE_UP);
        
    // time after explosion, time active, time player has
    init_option_data(opt, option_sprites, 49, 150, 1500);
}

void BattleSequence::InitPlayerInfo()
{
    // init player info
    char *defplayername[] = { "Player 1" , "Player 2" , "Player 3" , "Player 4" };
    for(int i=0;i<nb_players;i++)
    {
        init_player_info(&players[i],defplayername[i],nb_lives,&vaisseaux[i]);
        init_ship_pos_from_platforms(&vaisseaux[i],&(currentlevel->platformdata[i]));
    }
}


void BattleSequence::InitPlayerViews()
{
    if (nb_views == 1)
    {
        init_player_view(&views[0],90,100,300,260,&players[0]);
    }
    else if (nb_views == 2)
    {
        init_player_view(&views[0], screen_width*(90.0/800.0) , screen_height*(100.0/600.0), screen_width*(300.0/800.0), screen_height*(260.0/600.0),&players[0]);
        init_player_view(&views[1], screen_width*(410.0/800.0) , screen_height*(100.0/600.0) ,screen_width*(300.0/800.0), screen_height*(260.0/600.0),&players[1]);
    }
    else if (nb_views == 3)
    {
        init_player_view(&views[0], screen_width*(90/800.0), screen_height*(40/600.0),screen_width*(300.0/800.0),screen_height*(260.0/600.0),&players[0]);
        init_player_view(&views[1], screen_width*(410/800.0) ,screen_height*(40/600.0),screen_width*(300.0/800.0),screen_height*(260.0/600.0),&players[1]);
        init_player_view(&views[2], screen_width*(40/800.0) , screen_height*(310/600.0),screen_width*(300.0/800.0),screen_height*(260.0/600.0),&players[2]);
    }
    else if (nb_views == 4)
    {
        init_player_view(&views[0], screen_width*(90/800.0), screen_height*(40/600.0),screen_width*(300.0/800.0),screen_height*(260.0/600.0),&players[0]);
        init_player_view(&views[1], screen_width*(410/800.0) ,screen_height*(40/600.0),screen_width*(300.0/800.0),screen_height*(260.0/600.0),&players[1]);
        init_player_view(&views[2], screen_width*(40/800.0), screen_height*(310/600.0),screen_width*(300.0/800.0),screen_height*(260.0/600.0),&players[2]);
        init_player_view(&views[3], screen_width*(460/800.0), screen_height*(310/600.0),screen_width*(300.0/800.0),screen_height*(260.0/600.0),&players[3]);
    }
}

void BattleSequence::InitSoundFx()
{
    // get the ship wav's for this level
    struct level_ship_assets * assets = currentlevel->shipsassets;
    
    init_soundfx_from_wavfile(&sounds[0], assets[0].thrustloopwav, assets[0].shieldloopwav, assets[0].refuelloopwav, assets[0].shootwav, assets[0].boomwav, assets[0].reboundwav);
    init_soundfx_from_wavfile(&sounds[1], assets[1].thrustloopwav, assets[1].shieldloopwav, assets[1].refuelloopwav, assets[1].shootwav, assets[1].boomwav, assets[1].reboundwav);
    if (nb_views >= 3)
        init_soundfx_from_wavfile(&sounds[2], assets[2].thrustloopwav, assets[2].shieldloopwav, assets[2].refuelloopwav, assets[2].shootwav, assets[2].boomwav, assets[2].reboundwav);
    if (nb_views >= 4)
        init_soundfx_from_wavfile(&sounds[3], assets[3].thrustloopwav, assets[3].shieldloopwav, assets[3].refuelloopwav, assets[3].shootwav, assets[3].boomwav, assets[3].reboundwav);

    create_sprite_buffer_screen();
}

GameSequence* BattleSequence::doRun()
{
  int i; // for everythign counter

#ifdef CHECKFPS
  int check_fps=1;
  int retrace_count_init=retrace_count;
#endif

  bool isRunning=true;
  InterruptTimer::start();
  while(isRunning)
  {
    while(InterruptTimer::wasTriggered()) {
        // TODO - refactor - bit of a hack button 6 is back on an xbox 360 controller!
        if(key[KEY_ESC]  || joy[0].button[6].b || Gameover())
        {
            isRunning=false;
            break;
        }
        
        get_control_input(nb_players, commands);

        #ifdef __NETSUPPORT__
        struct command  *cmdptr=keyvaisseau[0].cmd;
        if (memcmp(&netpadcmd,cmdptr,sizeof(struct command)))
            {
            static int count=0;
            static int miss=0;
            char bf[20];
            sprintf(bf,"net send:%d",count++);
            textout(screen,font,bf,700,50,makecol(255,255,255));
            if (!gameclient.send(keyvaisseau[0].cmd))
                {
                sprintf(bf,"send miss:%d",miss++);
                textout(screen,font,bf,700,60,makecol(255,255,255));
                }
            }
        if (gameserver.recv(netpadcmd))
            {
            static int count=0;
            char bf[20];
            sprintf(bf,"net recv:%d",count++);
            textout(screen,font,bf,700,80,makecol(255,255,255));
            netpadcmd.controlled_ship=&vaisseaux[0];
            }

        handle_command(&netpadcmd);
        #else
        
        if(!player_gameover(&players[0]))
            handle_command(&commands[0]);
        #endif
        
        if(!player_gameover(&players[1]))
            handle_command(&commands[1]);

        if(nb_views>=3)
            if(!player_gameover(&players[2]))
                handle_command(&commands[2]);

        if(nb_views>=4)
            if(!player_gameover(&players[3]))
                handle_command(&commands[3]);
                
        calcul_pos(moon_physics,nb_players,vaisseaux,currentlevel->platformdata,currentlevel->nbplatforms);  // Position
        fuel_shield_calcul(nb_players,vaisseaux);
        
        // sound both player
        play_soundfx_from_shipdata(&sounds[0],&vaisseaux[0]);
        play_soundfx_from_shipdata(&sounds[1],&vaisseaux[1]);
        if(nb_views>=3)
            play_soundfx_from_shipdata(&sounds[2],&vaisseaux[2]);
        if(nb_views>=4)
            play_soundfx_from_shipdata(&sounds[3],&vaisseaux[3]);

        // create level buffer
        blit(currentlevel->bitmap, currentlevel->level_buffer, 0, 0, 0, 0, currentlevel->bitmap->w, currentlevel->bitmap->h);

        draw_basic_player_view(views, nb_views, currentlevel->bitmap, currentlevel->colormap);

        // first we rotate the sprite then display the shooting
        for(i=0;i<nb_players;i++)
            rotate_sprite(&views[i]);

        mega_collision_test(players, views, vaisseaux, currentlevel, nb_views, nb_players);

        gestion_option(opt, currentlevel,vaisseaux, views, nb_players,nb_views);

        for(i=0;i<nb_players;i++)
            gestion_tir(&vaisseaux[i], currentlevel);

        if(use_dca) 
        {
            for(i=0;i<nb_players;i++)
                gestion_dca(&currentlevel->alldca[0], &vaisseaux[i], currentlevel);
        }

        draw_explosion(players, currentlevel->platformdata, nb_players, currentlevel);
        
        draw_debris(players, moon_physics, nb_players, currentlevel);
        
        gestion_minimap(vaisseaux, currentlevel, nb_players, screen_width, screen_height);

        if(currentlevel==&levels[0]) warp_zone(vaisseaux, nb_players);
        gestion_warps(vaisseaux, currentlevel, nb_players);

        display_rotate_sprites(views, nb_views, currentlevel);

        // back_map_buffer dans screen
        for(i=0;i<nb_views;i++)
        {
            struct player_view* v = &views[i];
            struct vaisseau_data *ship = v->player->ship;
            blit(currentlevel->level_buffer, v->back_map_buffer,
                ship->xpos - (v->w/2), ship->ypos - (v->h/2),
                v->bordersize, v->bordersize, v->w, v->h);

            // does the level wrap in x
            if (currentlevel->edgedata.wrapx)
            {

                if (ship->xpos - (v->w/2) < 0) 
                {
                    blit(currentlevel->level_buffer, v->back_map_buffer,
                        currentlevel->bitmap->w + (ship->xpos - (v->w/2)), ship->ypos - (v->h/2),
                        v->bordersize, v->bordersize, v->w - (ship->xpos - (v->w/2)), v->h);
                }
                else if (ship->xpos + (v->w/2) > currentlevel->bitmap->w)
                {                    
                    blit(currentlevel->level_buffer, v->back_map_buffer,
                        0, ship->ypos - (v->h/2),
                        v->bordersize + (v->w - (ship->xpos + (v->w/2) - currentlevel->bitmap->w)), v->bordersize, 
                        ship->xpos + (v->w/2) - currentlevel->bitmap->w, v->h);
                }
            }
            
            blit(v->back_map_buffer, screen, 0, 0, v->x, v->y, v->w+2*v->bordersize, v->h+2*v->bordersize);
        }

    #ifdef CHECKFPS
        check_fps++;
        if (check_fps == 100)
        {
            char fps[10];
            sprintf(fps,"fps=%.1f",check_fps*70.0/(retrace_count-retrace_count_init));
            textout(screen,font,fps,5,5,makecol(200,200,200));

            char reso[10];
            sprintf(reso, "%ix%i", screen_width, screen_height);
            textout(screen,font, reso ,5,17,makecol(200,200,200));

            //debug interupt counter
            /*char counter[10];
            sprintf(counter, "%i", InterruptTimer::timing_counter);
            textout(screen,font, counter,5,29,makecol(200,200,200));*/

            check_fps=0;
            retrace_count_init=retrace_count;
         }
    #endif
    #ifdef USE_VSYNC
        vsync();    // wait the raster
    #endif 
    } // eof while(InterruptTimer())
  } // eof while (isRunning)
  
  if (Gameover())
  {
      char gameovermsg[10];
      //who won?
      int winner = 0;
      int winnerlives = 0;
      for(i=0;i<nb_players;i++)
        if(players[i].nblives > winnerlives)
        {
            winnerlives = players[i].nblives;
            winner = i + 1;
        }
      if(winner == 0) sprintf(gameovermsg, "Game over. Draw!");
      else sprintf(gameovermsg, "Game over. Player %i wins!", winner);
      textout(screen,font, gameovermsg ,5,29,makecol(255,0,0));
      rest(2000);
  }
  InterruptTimer::reset();

  return  ReturnScreen();
}

bool BattleSequence::Gameover()
{
    int gameovers = 0;
    //count how many players are game over
    for(int i=0;i<nb_players;i++)
    {
        if (player_gameover(&players[i])) gameovers++;
    }
    //are all but one players 
    return(((gameovers + 1) >= nb_players) ? true : false);
}
