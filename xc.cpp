#include "xc.h"
#include <stdio.h>

// support up to 8 controllers
// TODO: support an arbitrary number (is this necessary?)
static XC_STATE *controllers[8];

/*
 * Update the controller's axis positions.
 */
static void xc_update_axes(XC_STATE *state, ALLEGRO_EVENT event) {
  int axis = event.joystick.axis;
  float pos = event.joystick.pos;

  switch (event.joystick.stick) {
  case 0:
    if (axis == 0)
      state->left_stick_x = pos;
    else if (axis == 1)
      state->left_stick_y = pos;
    break;
  case 1:
    if (axis == 0)
      state->left_trigger = (pos + 1.0) / 2.0;
    else if (axis == 1)
      state->right_stick_x = pos;
    break;
  case 2:
    if (axis == 0)
      state->right_stick_y = pos;
    else if (axis == 1)
      state->right_trigger = (pos + 1.0) / 2.0;
    break;
  case 3:
    if (axis == 0)
      state->dpad_x = pos;
    else if (axis == 1)
      state->dpad_y = pos;
    break;
  }
}

/*
 * Update the controller's button statuses.
 */
static void xc_update_buttons(XC_STATE *state, ALLEGRO_EVENT event) {
  bool value = (event.type == XC_EVENT_BUTTON_DOWN);
  switch (event.joystick.button) {
  case 0:
    state->button_a = value;
    break;
  case 1:
    state->button_b = value;
    break;
  case 2:
    state->button_x = value;
    break;
  case 3:
    state->button_y = value;
    break;
  case 4:
    state->button_left_shoulder = value;
    break;
  case 5:
    state->button_right_shoulder = value;
    break;
  case 6:
    state->button_back = value;
    break;
  case 7:
    state->button_start = value;
    break;
  case 8:
    state->button_xbox = value;
    break;
  case 9:
    state->button_left_stick = value;
    break;
  case 10:
    state->button_right_stick = value;
    break;
  default:
    fprintf(stderr, "[XC] Error: unexpected button (%d)\n",
            event.joystick.button);
    break;
  }
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
  state->dpad_x = 0;
  state->dpad_y = 0;
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
  xc_clear_state(new_state);
  new_state->joy = joy;
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
