#include "menuhandler.h"

#include "allegro_compatibility.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <cassert>
#include <cstring>

MenuHandler::MenuHandler() {}

void MenuHandler::reset() { num_lines = 0; }

void MenuHandler::draw(ALLEGRO_BITMAP *screen_buffer, ALLEGRO_FONT *font) {
  ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
  ALLEGRO_COLOR red = al_map_rgb(142, 52, 36);
  ALLEGRO_COLOR lightred = al_map_rgb(239, 89, 36);

  textout(screen_buffer, font,
          "Press F2/F3/F4 to play for 2/3/4 players or ESC to leave", width / 4,
          maxi + 5, red);
  textout(screen_buffer, font, "Use arrow keys and enter:", width / 4,
          maxi + 15, red);

  int selected_idx_adjusted = selected_idx;

  int offset = maxi + 20;

  int highlight_line = get_current_line_index();

  int start_idx = highlight_line - (max_visible_lines - 1) / 2;

  if (start_idx < 0)
    start_idx = 0;

  int end_idx = start_idx + max_visible_lines;

  if (end_idx >= num_lines) {
    start_idx = num_lines - max_visible_lines;
    end_idx = num_lines;
  }
  offset += 10;

  if (start_idx > 0) {
    textout(screen_buffer, font, "             ...", width / 3, offset,
            lightred);
  } else {
    textout(screen_buffer, font, "", width / 3, offset, red);
  }
  offset += 10;

  for (int i = start_idx; i < end_idx; i++) {
    offset += line_offset[i];
    bool selected = highlight_line == i;
    textout(screen_buffer, font, lines[i], width / 3, offset,
            (selected ? lightred : red));

    if (!line_selectable[i])
      selected_idx_adjusted++;
  }

  offset += 15;
  if (end_idx < num_lines) {
    textout(screen_buffer, font, "            ...", width / 3, offset,
            lightred);
    offset += 10;
  }
}

void MenuHandler::addline(char *line, bool selectable, int offset) {
  assert(num_lines < 100);

  strncpy(lines[num_lines], line, 1000);
  line_selectable[num_lines] = selectable;
  line_offset[num_lines] = offset;

  num_lines++;
}

int MenuHandler::get_current_line_index() {
  int selected_idx_adjusted = selected_idx;
  for (int i = 0; i < num_lines; i++) {
    if (line_selectable[i] && selected_idx_adjusted == i)
      return i;

    if (!line_selectable[i])
      selected_idx_adjusted++;
  }

  assert(false);
  return 0;
}
