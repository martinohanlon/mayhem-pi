#include "intro_sequence.h"
#include "allegro_compatibility.h"
#include "battle_sequence.h"
#include "mapping_joy.h"
#include "menuhandler.h"
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

const int IntroSequence::mini = 150;
const int IntroSequence::maxi = 400;

enum CONTROL_ID playercontrols[4] = {KEYBOARD_0, KEYBOARD_1, KEYBOARD_2,
                                     KEYBOARD_3};

IntroSequence::IntroSequence(GameSequence *previous, float zoom,
                             float zoomspeed, int players, int level, int lives,
                             bool dca, bool wall)
    : GameSequence(previous) {
  width = GameManager::display_width;
  height = GameManager::display_height;

  iLogo = al_load_bitmap("assets/intro/intro_logo.bmp");
  iZoomMax = iZoom = (zoom);
  iZoomSpeed = (zoomspeed);
  iDoublebuffer = al_create_bitmap(width, maxi - mini);

  playerschoice = players;
  levelchoice = level;
  liveschoice = lives;
  dcachoice = dca;
  wallchoice = wall;
  assert(GameManager::num_joysticks_loaded >= 0 &&
         GameManager::num_joysticks_loaded <= 4);

  // setup player_controls based on number of joysticks, if there are joysticks use them first, otherwise use keyboard
  int playercontrol;
  for (playercontrol = 0; playercontrol < GameManager::num_joysticks_loaded; playercontrol++)
    playercontrols[playercontrol] = static_cast<CONTROL_ID>(4 + playercontrol);

  for (playercontrol = GameManager::num_joysticks_loaded; playercontrol < NB_MAX_PLAYERS; playercontrol++)
    playercontrols[playercontrol] = static_cast<CONTROL_ID>(playercontrol - GameManager::num_joysticks_loaded);
}

IntroSequence::~IntroSequence() {
  if (iLogo)
    al_destroy_bitmap(iLogo);
}

GameSequence *IntroSequence::doTick(ALLEGRO_BITMAP *screen_buffer,
                                    bool key_pressed[ALLEGRO_KEY_MAX],
                                    bool key_down[ALLEGRO_KEY_MAX],
                                    bool *exit_game, double dt) {
  iZoom = (iZoom - iZoomSpeed);
  if (iZoom < 1.0) {
    iZoom = 1;
    isRunning = false;
  }

  clear_bitmap(iDoublebuffer);
  DrawZoomedLogoInCenter(mini, maxi);
  // draw 2 horizontal lines
  hline(iDoublebuffer, 0, 0, width, al_map_rgb(255, 255, 255));
  hline(iDoublebuffer, 0, IntroSequence::maxi - IntroSequence::mini - 1, width,
        al_map_rgb(255, 255, 255));

  // blit to the screen
  blit(iDoublebuffer, screen_buffer, 0, 0, 0, mini, width, maxi - mini);

  if (key_pressed[ALLEGRO_KEY_ESCAPE] && canQuickExit) {
    quickExit = true;
    isRunning = false;
  }

  if (joystick_action_timer.is_running())
    joystick_action_timer.tick();

  bool startgame = false;
  bool exit = false;
  bool reload = false;

  if (!quickExit && !isRunning) {
    black = al_map_rgb(0, 0, 0);
    red = al_map_rgb(255, 0, 0);
    lightred = al_map_rgb(255, 75, 75);

    handle_key_presses(key_pressed, &reload, &startgame, &exit);

    char layout_str[1000];
    auto font = GameManager::font;

    MenuHandler mh;

    mh.reset();
    mh.selected_idx = menuselected;
    mh.maxi = maxi;
    mh.width = width;
    mh.max_visible_lines = 25;

    mh.addline("Start game");
    mh.addline("Options:", false, 15);

    snprintf(menutext, sizeof(menutext), "   Players - %d   ", playerschoice);
    mh.addline(menutext);

    snprintf(menutext, sizeof(menutext), "   Level - %d   ", levelchoice + 1);
    mh.addline(menutext);

    snprintf(menutext, sizeof(menutext), "   Lives - %d   ", liveschoice);
    mh.addline(menutext);

    snprintf(menutext, sizeof(menutext), "   Use DCA - %s   ",
             ((dcachoice) ? "yes" : "no"));
    mh.addline(menutext);

    snprintf(menutext, sizeof(menutext), "   Wall Collision - %s   ",
             ((wallchoice) ? "yes" : "no"));
    mh.addline(menutext);

    mh.addline("Controls:", false, 15);

    snprintf(menutext, sizeof(menutext), "   Player 1 - %s",
             get_control_id_as_string(playercontrols[0]));
    mh.addline(menutext);

    snprintf(menutext, sizeof(menutext), "   Player 2 - %s",
             get_control_id_as_string(playercontrols[1]));
    mh.addline(menutext);

    snprintf(menutext, sizeof(menutext), "   Player 3 - %s",
             get_control_id_as_string(playercontrols[2]));
    mh.addline(menutext);

    snprintf(menutext, sizeof(menutext), "   Player 4 - %s",
             get_control_id_as_string(playercontrols[3]));
    mh.addline(menutext);

    mh.addline("Controller layouts:", false, 15);
    
    menu_joy_kbd_idx = 10;
  
    menu_kbd_layout1_idx = 0;
    menu_kbd_layout2_idx = 0;
    menu_kbd_layout3_idx = 0;
    menu_kbd_layout4_idx = 0;
    menu_kbd_layout_end = 0;
  
    menu_joy_layout1_idx = 0;
    menu_joy_layout2_idx = 0;
    menu_joy_layout3_idx = 0;
    menu_joy_layout4_idx = 0;
    menu_joy_layout_end = 0;
    
    if (GameManager::num_joysticks_loaded > 0) {
      for (int i = 0; i < GameManager::num_joysticks_loaded; i++) {
        switch (i) {
          case 0:
            menu_joy_layout1_idx = menu_joy_kbd_idx;
            break;
          case 1:
            menu_joy_layout2_idx = menu_joy_kbd_idx;
            break;
          case 2:
            menu_joy_layout3_idx = menu_joy_kbd_idx;
            break;
          case 3:
            menu_joy_layout4_idx = menu_joy_kbd_idx;
            break;
        }
        snprintf(menutext, sizeof(menutext), "   Joystick %d %s", (i + 1), al_get_joystick_name(GameManager::joysticks[i]->joy));
        mh.addline(menutext, false, 10);
        snprintf(menutext, sizeof(menutext), "      Left   - %s",
                 button_to_str(mapping_joy::btn_sets[i][0]));
        mh.addline(menutext);
        snprintf(menutext, sizeof(menutext), "      Right  - %s",
                 button_to_str(mapping_joy::btn_sets[i][1]));
        mh.addline(menutext);
        snprintf(menutext, sizeof(menutext), "      Thrust - %s",
                 button_to_str(mapping_joy::btn_sets[i][2]));
        mh.addline(menutext);
        snprintf(menutext, sizeof(menutext), "      Shield - %s",
                 button_to_str(mapping_joy::btn_sets[i][3]));
        mh.addline(menutext);
        snprintf(menutext, sizeof(menutext), "      Fire   - %s",
                 button_to_str(mapping_joy::btn_sets[i][4]));
        mh.addline(menutext);
        menu_joy_kbd_idx = menu_joy_kbd_idx + 5;
        menu_joy_layout_end = menu_joy_kbd_idx;
      }
    }

    for (int i = 0; i < 4; i++) {
      switch (i) {
        case 0:
          menu_kbd_layout1_idx = menu_joy_kbd_idx;
          break;
        case 1:
          menu_kbd_layout2_idx = menu_joy_kbd_idx;
          break;
        case 2:
          menu_kbd_layout3_idx = menu_joy_kbd_idx;
          break;
        case 3:
          menu_kbd_layout4_idx = menu_joy_kbd_idx;
          break;
      }
      
      snprintf(menutext, sizeof(menutext), "   Keyboard %d", (i + 1));
      mh.addline(menutext, false, 10);
      snprintf(menutext, sizeof(menutext), "      Left   - %s",
               key_to_str(mapping_key::key_sets[i][0]));
      mh.addline(menutext);
      snprintf(menutext, sizeof(menutext), "      Right  - %s",
               key_to_str(mapping_key::key_sets[i][1]));
      mh.addline(menutext);
      snprintf(menutext, sizeof(menutext), "      Thrust - %s",
               key_to_str(mapping_key::key_sets[i][2]));
      mh.addline(menutext);
      snprintf(menutext, sizeof(menutext), "      Shield - %s",
               key_to_str(mapping_key::key_sets[i][3]));
      mh.addline(menutext);
      snprintf(menutext, sizeof(menutext), "      Fire   - %s",
               key_to_str(mapping_key::key_sets[i][4]));
      mh.addline(menutext);
      menu_joy_kbd_idx = menu_joy_kbd_idx + 5;
      menu_kbd_layout_end = menu_joy_kbd_idx;
    }

    snprintf(menutext, sizeof(menutext), "Resolution (%ix%i):   ", width,
             height);
    mh.addline(menutext, false, 15);

    menu_resolution_idx = menu_joy_kbd_idx;
    menu_exit_idx = menu_resolution_idx + 1;
    menuitems = menu_exit_idx + 1;

    if (width == GameManager::native_width &&
        height == GameManager::native_height)
      snprintf(menutext, sizeof(menutext), "   Switch to Low - 1024x768   ");
    else
      snprintf(menutext, sizeof(menutext), "   Switch to Native - %ix%i   ",
               GameManager::native_width, GameManager::native_height);
    mh.addline(menutext);

    mh.addline("Exit", true, 15);

    mh.draw(screen_buffer, font);
  }

  *exit_game = exit;

  GameSequence *seq = nullptr;
  if (startgame) {
    iZoom = iZoomMax;
    seq = new BattleSequence(this, playerschoice, playerschoice, liveschoice,
                             levelchoice, dcachoice, wallchoice, width, height,
                             playercontrols);
  } else if (reload)
    seq = new IntroSequence(NULL, 10.0, 0.5, playerschoice, levelchoice,
                            liveschoice, dcachoice, wallchoice);
  else
    seq = ReturnScreen();

  return seq;
}

void IntroSequence::DrawZoomedLogoInCenter(int y1, int y2) {
  int logowidth = fixtoi(fixmul(itofix(al_get_bitmap_width(iLogo)), iZoom));
  int logoheight = fixtoi(fixmul(itofix(al_get_bitmap_height(iLogo)), iZoom));
  int targetwidth = width;
  int targetheight = y2 - y1;

  int xs, ys, ws, hs;
  int xd, yd, wd, hd;

  if (logowidth > targetwidth) {
    ws = fixtoi(fixdiv(itofix(targetwidth), iZoom));
    xs = (al_get_bitmap_width(iLogo) - ws) / 2;
    xd = 0;
    wd = targetwidth;
  } else {
    xs = 0;
    ws = al_get_bitmap_width(iLogo);
    xd = (targetwidth - logowidth) / 2;
    wd = logowidth;
  }

  if (logoheight > targetheight) {
    hs = fixtoi(fixdiv(itofix(targetheight), iZoom));
    ys = (al_get_bitmap_height(iLogo) - hs) / 2;
    yd = 0;
    hd = targetheight;
  } else {
    ys = 0;
    hs = al_get_bitmap_height(iLogo);
    yd = (targetheight - logoheight) / 2;
    hd = logoheight;
  }

  stretch_blit(iLogo, iDoublebuffer, xs, ys, ws, hs, xd, yd, wd, hd);
}

void IntroSequence::cycle_control(int playerno) {
  int num_keyboard_layouts = 4;
  int num_ctrls = static_cast<int>(NUM_CONTROLS);
  int end_control_index = std::min(
      num_ctrls, num_keyboard_layouts + GameManager::num_joysticks_loaded);

  int next_ctrl_idx = static_cast<int>(playercontrols[playerno]) + 1;

  playercontrols[playerno] =
      static_cast<CONTROL_ID>(next_ctrl_idx % end_control_index);
}

bool IntroSequence::do_js_action(JoyButton button) {
  auto joystick = GameManager::joysticks[0];

  if (joystick == nullptr)
    return false;

  if (!is_pressed(joystick, button))
    return false;

  bool js_ok = GameManager::num_joysticks_loaded > 0;
  bool timer_ok = joystick_action_timer.is_done();

  if (js_ok && timer_ok) {
    joystick_action_timer.start(0.10, GameManager::FPS);
    return true;
  }
  return false;
};

bool get_first_keyboard_button_pressed(bool key_pressed[ALLEGRO_KEY_MAX],
                                       int *keycode) {

  for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
    if (key_pressed[i]) {
      *keycode = i;
      return true;
    }
  }

  return false;
}

bool get_first_joystick_button_pressed(XC_STATE *joystick, JoyButton *button) {
  if (is_pressed(joystick, JoyButton::LEFT_STICK_X_LEFT)) {
    *button = JoyButton::LEFT_STICK_X_LEFT;
    return true;
  }
  if (is_pressed(joystick, JoyButton::LEFT_STICK_X_RIGHT)) {
    *button = JoyButton::LEFT_STICK_X_RIGHT;
    return true;
  }
  if (is_pressed(joystick, JoyButton::LEFT_STICK_Y_UP)) {
    *button = JoyButton::LEFT_STICK_Y_UP;
    return true;
  }
  if (is_pressed(joystick, JoyButton::LEFT_STICK_Y_DOWN)) {
    *button = JoyButton::LEFT_STICK_Y_DOWN;
    return true;
  }
  if (is_pressed(joystick, JoyButton::LEFT_TRIGGER)) {
    *button = JoyButton::LEFT_TRIGGER;
    return true;
  }
  if (is_pressed(joystick, JoyButton::RIGHT_STICK_X_LEFT)) {
    *button = JoyButton::RIGHT_STICK_X_LEFT;
    return true;
  }
  if (is_pressed(joystick, JoyButton::RIGHT_STICK_X_RIGHT)) {
    *button = JoyButton::RIGHT_STICK_X_RIGHT;
    return true;
  }
  if (is_pressed(joystick, JoyButton::RIGHT_STICK_Y_UP)) {
    *button = JoyButton::RIGHT_STICK_Y_UP;
    return true;
  }
  if (is_pressed(joystick, JoyButton::RIGHT_STICK_Y_DOWN)) {
    *button = JoyButton::RIGHT_STICK_Y_DOWN;
    return true;
  }
  if (is_pressed(joystick, JoyButton::RIGHT_TRIGGER)) {
    *button = JoyButton::RIGHT_TRIGGER;
    return true;
  }
  if (is_pressed(joystick, JoyButton::DPAD_X_LEFT)) {
    *button = JoyButton::DPAD_X_LEFT;
    return true;
  }
  if (is_pressed(joystick, JoyButton::DPAD_X_RIGHT)) {
    *button = JoyButton::DPAD_X_RIGHT;
    return true;
  }
  if (is_pressed(joystick, JoyButton::DPAD_Y_UP)) {
    *button = JoyButton::DPAD_Y_UP;
    return true;
  }
  if (is_pressed(joystick, JoyButton::DPAD_Y_DOWN)) {
    *button = JoyButton::DPAD_Y_DOWN;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_A)) {
    *button = JoyButton::BUTTON_A;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_B)) {
    *button = JoyButton::BUTTON_B;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_X)) {
    *button = JoyButton::BUTTON_X;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_Y)) {
    *button = JoyButton::BUTTON_Y;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_LEFT_STICK)) {
    *button = JoyButton::BUTTON_LEFT_STICK;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_RIGHT_STICK)) {
    *button = JoyButton::BUTTON_RIGHT_STICK;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_LEFT_SHOULDER)) {
    *button = JoyButton::BUTTON_LEFT_SHOULDER;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_RIGHT_SHOULDER)) {
    *button = JoyButton::BUTTON_RIGHT_SHOULDER;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_START)) {
    *button = JoyButton::BUTTON_START;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_BACK)) {
    *button = JoyButton::BUTTON_BACK;
    return true;
  }
  if (is_pressed(joystick, JoyButton::BUTTON_XBOX)) {
    *button = JoyButton::BUTTON_XBOX;
    return true;
  }

  return false;
}

void IntroSequence::handle_key_presses(bool key_pressed[ALLEGRO_KEY_MAX],
                                       bool *reload, bool *startgame,
                                       bool *exit) {

  if (selecting_new_keyboard_button) {
    int keycode;
    if (get_first_keyboard_button_pressed(key_pressed, &keycode)) {

      int keyboard_set = -1;
      int start_idx = -1;

      if (menuselected >= menu_kbd_layout1_idx) {
        keyboard_set = 0;
        start_idx = menu_kbd_layout1_idx;
      }
      if (menu_kbd_layout2_idx != 0 && menuselected >= menu_kbd_layout2_idx) {
        keyboard_set = 1;
        start_idx = menu_kbd_layout2_idx;
      }
      if (menu_kbd_layout3_idx != 0 && menuselected >= menu_kbd_layout3_idx) {
        keyboard_set = 2;
        start_idx = menu_kbd_layout3_idx;
      }
      if (menu_kbd_layout4_idx != 0 && menuselected >= menu_kbd_layout4_idx) {
        keyboard_set = 3;
        start_idx = menu_kbd_layout4_idx;
      }
      int key_idx = menuselected - start_idx;

      mapping_key::key_sets[keyboard_set][key_idx] = keycode;

      selecting_new_keyboard_button = false;

      return;
    }
  } else if (selecting_new_joystick_button) {
    JoyButton button;

    int joy_set = -1;
    int start_idx = -1;
    
    if (menuselected >= menu_joy_layout1_idx) {
      joy_set = 0;
      start_idx = menu_joy_layout1_idx;
    }
    if (menu_joy_layout2_idx != 0 && menuselected >= menu_joy_layout2_idx) {
      joy_set = 1;
      start_idx = menu_joy_layout2_idx;
    }
    if (menu_joy_layout3_idx != 0 && menuselected >= menu_joy_layout3_idx) {
      joy_set = 2;
      start_idx = menu_joy_layout3_idx;
    }
    if (menu_joy_layout4_idx != 0 && menuselected >= menu_joy_layout4_idx) {
      joy_set = 3;
      start_idx = menu_joy_layout4_idx;
    }
    int key_idx = menuselected - start_idx;

    if (joystick_action_timer.is_done() &&
        get_first_joystick_button_pressed(GameManager::joysticks[joy_set], &button)) {

      mapping_joy::btn_sets[joy_set][key_idx] = button;

      selecting_new_joystick_button = false;
      do_js_action(button); // For resetting timer
    }
  }

  auto do_js_action = [&](JoyButton button) {
    auto joystick = GameManager::joysticks[0];

    if (joystick == nullptr)
      return false;

    if (!is_pressed(joystick, button))
      return false;

    bool js_ok = GameManager::num_joysticks_loaded > 0;
    bool timer_ok = joystick_action_timer.is_done();

    if (js_ok && timer_ok) {
      joystick_action_timer.start(0.10, GameManager::FPS);
      return true;
    }
    return false;
  };

  auto do_key_action = [&](int button) {
    if (!key_pressed[button])
      return false;

    if (button != ALLEGRO_KEY_ESCAPE &&
        (selecting_new_keyboard_button || selecting_new_joystick_button)) {
      return false;
    }
    return true;
  };

  if (do_key_action(ALLEGRO_KEY_ESCAPE) ||
      do_js_action(JoyButton::BUTTON_BACK)) {
    if (selecting_new_joystick_button || selecting_new_keyboard_button) {
      selecting_new_joystick_button = false;
      selecting_new_keyboard_button = false;
    } else {
      *exit = true;
    }
  }
  if (do_key_action(ALLEGRO_KEY_F2)) {
    playerschoice = 2;
    *startgame = true;
  }
  if (do_key_action(ALLEGRO_KEY_F3)) {
    playerschoice = 3;
    *startgame = true;
  }
  if (do_key_action(ALLEGRO_KEY_F4)) {
    playerschoice = 4;
    *startgame = true;
  }

  // menu control
  if (do_key_action(ALLEGRO_KEY_DOWN) ||
      do_js_action(JoyButton::LEFT_STICK_Y_DOWN)) {
    if (menuselected < menuitems - 1)
      menuselected++;
    else
      menuselected = 0;
  }
  if (do_key_action(ALLEGRO_KEY_UP) ||
      do_js_action(JoyButton::LEFT_STICK_Y_UP)) {
    if (menuselected > 0)
      menuselected--;
    else
      menuselected = menuitems - 1;
  }
  if (do_key_action(ALLEGRO_KEY_LEFT) ||
      do_js_action(JoyButton::LEFT_STICK_X_LEFT)) {
    switch (menuselected) {
    case 1:
      if (playerschoice > 2)
        playerschoice--;
      break;
    case 2:
      if (levelchoice > 0)
        levelchoice--;
      break;
    case 3:
      if (liveschoice > 0)
        liveschoice--;
      break;
    case 4:
      dcachoice = !dcachoice;
      break;
    case 5:
      wallchoice = !wallchoice;
      break;
    }
  }
  if (do_key_action(ALLEGRO_KEY_RIGHT) ||
      do_js_action(JoyButton::LEFT_STICK_X_RIGHT)) {
    switch (menuselected) {
    case 1:
      if (playerschoice < NB_MAX_PLAYERS)
        playerschoice++;
      break;
    case 2:
      if (levelchoice < NB_LEVELS - 1)
        levelchoice++;
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
  }
  if (do_key_action(ALLEGRO_KEY_ENTER) || do_js_action(JoyButton::BUTTON_A)) {
    switch (menuselected) {
    case 0:
      *startgame = true;
      break;
    case 1:
      playerschoice++;
      if (playerschoice > NB_MAX_PLAYERS)
        playerschoice = 2;
      break;
    case 2:
      levelchoice++;
      if (levelchoice == NB_LEVELS)
        levelchoice = 0;
      break;
    case 3:
      liveschoice++;
      if (liveschoice == NB_MAXLIVES)
        liveschoice = 0;
      break;
    case 4:
      dcachoice = !dcachoice;
      break;
    case 5:
      wallchoice = !wallchoice;
      break;
    case 6:
      cycle_control(0);
      break;
    case 7:
      cycle_control(1);
      break;
    case 8:
      cycle_control(2);
      break;
    case 9:
      cycle_control(3);
      break;
    }
    if (menuselected == menu_resolution_idx) {
      if (width == GameManager::native_width &&
          height == GameManager::native_height)
        GameManager::ChangeScreenRes(1024, 768);
      else
        GameManager::ChangeScreenRes(GameManager::native_width,
                                     GameManager::native_height);
      *reload = true;
    } else if (menuselected == menu_exit_idx) {
      *exit = true;
    } else if (menuselected >= menu_kbd_layout1_idx &&
               menuselected < menu_kbd_layout_end) {
      selecting_new_keyboard_button = true;
    } else if (menuselected >= menu_joy_layout1_idx &&
               menuselected < menu_joy_layout_end) {
      selecting_new_joystick_button = true;
    }
  }
}
