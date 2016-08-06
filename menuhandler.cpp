#include "menuhandler.h"

#include "allegro_compatibility.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <cassert>
#include <cstring>

MenuHandler::MenuHandler()
{

}

void MenuHandler::reset() {
  num_lines = 0;
}

void MenuHandler::draw(ALLEGRO_BITMAP* screen_buffer, ALLEGRO_FONT* font) {
  ALLEGRO_COLOR black = al_map_rgb(0,0,0);
  ALLEGRO_COLOR red = al_map_rgb(255,0,0);
  ALLEGRO_COLOR lightred = al_map_rgb(255, 75, 75);

  textout(screen_buffer, font, "Press F2/F3/F4 to play for 2/3/4 players or ESC to leave", width/4, maxi+5, red);
  textout(screen_buffer, font, "Use arrow keys and enter:", width/4, maxi+15, red);

  int selected_idx_adjusted = selected_idx;

  int offset = maxi+20;

  for (int i = 0; i < num_lines; i++) {
      offset += line_offset[i];
      bool selected = line_selectable[i] && selected_idx_adjusted == i;
      textout(screen_buffer, font, lines[i], width/3, offset, (selected ? lightred : red));

      if (!line_selectable[i])
        selected_idx_adjusted++;
    }

}

void MenuHandler::addline(char *line, bool selectable, int offset) {
  assert(num_lines < 100);

  strncpy(lines[num_lines], line, 1000);
  line_selectable[num_lines] = selectable;
  line_offset[num_lines] = offset;

  num_lines++;
}
