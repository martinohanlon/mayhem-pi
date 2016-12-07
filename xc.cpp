#include "xc.h"
#include <stdio.h>

// support up to 8 controllers
// TODO: support an arbitrary number (is this necessary?)
static XC_STATE *controllers[8];

/*
 * Update the controller's axis positions.
 */
static void xc_update_axes(XC_STATE *state, ALLEGRO_EVENT event) {
  int stick = event.joystick.stick;
  int axis = event.joystick.axis;
  float pos = event.joystick.pos;
  
  if (stick < state->controls_map.num_sticks)
    if (state->controls_map.stick_map[stick][axis].analog_output) {
      if (state->controls_map.stick_map[stick][axis].trigger)
        *state->controls_map.stick_map[stick][axis].position = (pos + 1.0) / 2.0;
      else
        *state->controls_map.stick_map[stick][axis].position = pos;
    }
    else {
      *state->controls_map.stick_map[stick][axis].negative = (pos <= -0.6);
      *state->controls_map.stick_map[stick][axis].positive = (pos >= 0.6);
    }
}

/*
 * Update the controller's button statuses.
 */
static void xc_update_buttons(XC_STATE *state, ALLEGRO_EVENT event) {
  bool value = (event.type == XC_EVENT_BUTTON_DOWN);
  if (event.joystick.button < state->controls_map.num_buttons) 
    *state->controls_map.button_map[event.joystick.button] = value;
}

/*
 * Wrapper around al_install_joystick()
 */
bool xc_install() { return al_install_joystick(); }

/*
 * Wrapper around al_reconfigure_joysticks()
 */
bool xc_reconfigure() { return al_reconfigure_joysticks(); }

/*
 * Resets a controller's state.
 */
void xc_clear_state(XC_STATE *state) {
  state->left_stick_x = 0;
  state->left_stick_y = 0;
  state->left_trigger = 0;
  state->right_stick_x = 0;
  state->right_stick_y = 0;
  state->right_trigger = 0;
  state->dpad_left = false;
  state->dpad_right = false;
  state->dpad_up = false;
  state->dpad_down = false;
  state->button_a = false;
  state->button_b = false;
  state->button_x = false;
  state->button_y = false;
  state->button_left_stick = false;
  state->button_right_stick = false;
  state->button_left_shoulder = false;
  state->button_right_shoulder = false;
  state->button_start = false;
  state->button_back = false;
  state->button_xbox = false;
}

//specific joystick configs can be setup based on joystick name
void setup_controller_map(XC_STATE *state) {
  if (strstr(al_get_joystick_name(state->joy), "XInput Joystick") != NULL)
    setup_xinput_controller_map(state);
  else
    setup_default_controller_map(state);
}

//default joystick map - typical of an xbox 360 controller
void setup_default_controller_map(XC_STATE *state) {
  state->controls_map.num_buttons = 11;
  state->controls_map.button_map[0] = &state->button_a;
  state->controls_map.button_map[1] = &state->button_b;
  state->controls_map.button_map[2] = &state->button_x;
  state->controls_map.button_map[3] = &state->button_y;
  state->controls_map.button_map[4] = &state->button_left_shoulder;
  state->controls_map.button_map[5] = &state->button_right_shoulder;
  state->controls_map.button_map[6] = &state->button_back;
  state->controls_map.button_map[7] = &state->button_start;
  state->controls_map.button_map[8] = &state->button_xbox;
  state->controls_map.button_map[9] = &state->button_left_stick;
  state->controls_map.button_map[10] = &state->button_right_stick;

  //sticks
  state->controls_map.num_sticks = 4;
  // left stick 
  state->controls_map.stick_map[0][0].analog_output = true;
  state->controls_map.stick_map[0][0].position = &state->left_stick_x;
  state->controls_map.stick_map[0][1].analog_output = true;
  state->controls_map.stick_map[0][1].position = &state->left_stick_y;
  //right stick 
  state->controls_map.stick_map[1][1].analog_output = true;
  state->controls_map.stick_map[1][1].position = &state->right_stick_x;
  state->controls_map.stick_map[2][0].analog_output = true;
  state->controls_map.stick_map[2][0].position = &state->right_stick_y;
  //left trigger
  state->controls_map.stick_map[1][0].analog_output = true;
  state->controls_map.stick_map[1][0].trigger = true;
  state->controls_map.stick_map[1][0].position = &state->left_trigger;
  //right trigger
  state->controls_map.stick_map[2][1].analog_output = true;
  state->controls_map.stick_map[2][1].trigger = true;
  state->controls_map.stick_map[2][1].position = &state->right_trigger;
  //dpad
  state->controls_map.stick_map[3][0].analog_output = false;
  state->controls_map.stick_map[3][0].negative = &state->dpad_left;
  state->controls_map.stick_map[3][0].positive = &state->dpad_right;
  state->controls_map.stick_map[3][1].analog_output = false;
  state->controls_map.stick_map[3][1].negative = &state->dpad_up;
  state->controls_map.stick_map[3][1].positive = &state->dpad_down;
}

//xinput joystick map 
void setup_xinput_controller_map(XC_STATE *state) {
  //buttons
  state->controls_map.num_buttons = 14;
  state->controls_map.button_map[0] = &state->button_a;
  state->controls_map.button_map[1] = &state->button_b;
  state->controls_map.button_map[2] = &state->button_x;
  state->controls_map.button_map[3] = &state->button_y;
  state->controls_map.button_map[4] = &state->button_right_shoulder;
  state->controls_map.button_map[5] = &state->button_left_shoulder;
  state->controls_map.button_map[8] = &state->button_back;
  state->controls_map.button_map[9] = &state->button_start;
  state->controls_map.button_map[7] = &state->button_left_stick;
  state->controls_map.button_map[6] = &state->button_right_stick;
  state->controls_map.button_map[10] = &state->dpad_right;
  state->controls_map.button_map[11] = &state->dpad_left;
  state->controls_map.button_map[12] = &state->dpad_down;
  state->controls_map.button_map[13] = &state->dpad_up;
  
  //sticks
  state->controls_map.num_sticks = 4;
  // left stick
  state->controls_map.stick_map[0][0].analog_output = true;
  state->controls_map.stick_map[0][0].position = &state->left_stick_x;
  state->controls_map.stick_map[0][1].analog_output = true;
  state->controls_map.stick_map[0][1].position = &state->left_stick_y;
  //right stick
  state->controls_map.stick_map[1][0].analog_output = true;
  state->controls_map.stick_map[1][0].position = &state->right_stick_x;
  state->controls_map.stick_map[1][1].analog_output = true;
  state->controls_map.stick_map[1][1].position = &state->right_stick_y;
  //left trigger
  state->controls_map.stick_map[2][0].analog_output = true;
  state->controls_map.stick_map[2][0].trigger = true;
  state->controls_map.stick_map[2][0].position = &state->left_trigger;
  //right trigger
  state->controls_map.stick_map[3][0].analog_output = true;
  state->controls_map.stick_map[3][0].trigger = true;
  state->controls_map.stick_map[3][0].position = &state->right_trigger;
}

/*
 * Gets the state for a controller.
 */
XC_STATE *xc_get_state(int num) {
  if (num < 0 || num > 7)
    return NULL;

  if (controllers[num] != NULL)
    return controllers[num];

  ALLEGRO_JOYSTICK *joy = al_get_joystick(num);
  if (joy == NULL)
    return NULL;

  XC_STATE *new_state = (XC_STATE *)malloc(sizeof(XC_STATE));
  new_state->joy = joy;
  setup_controller_map(new_state);  
  xc_clear_state(new_state);
  
  controllers[num] = new_state;

  return new_state;
}

/*
 * Free a controller's state.
 */
void xc_free_state(XC_STATE *state) {
  free(state->joy);
  free(state);
}

/*
 * Wrapper around al_get_joystick_event_source()
 */
ALLEGRO_EVENT_SOURCE *xc_get_event_source() {
  return al_get_joystick_event_source();
}

/*
 * Update the controller's state.
 */
void xc_update(ALLEGRO_EVENT event) {
  // TODO: there has to be a better way to do this...
  ALLEGRO_JOYSTICK *id = event.joystick.id;
  XC_STATE *state = NULL;
  int i;
  for (i = 0; i < 7; i++) {
    if (controllers[i] == NULL)
      continue;

    if (controllers[i]->joy == id) {
      state = controllers[i];
      break;
    }
  }

  if (state == NULL)
    return;

  switch (event.type) {
  case XC_EVENT_AXIS:
    xc_update_axes(state, event);
    break;
  case XC_EVENT_BUTTON_DOWN:
  case XC_EVENT_BUTTON_UP:
    xc_update_buttons(state, event);
    break;
  default:
    fprintf(stderr, "[XC] Error: unrecognized event (%d)\n", event.type);
    break;
  }
}
