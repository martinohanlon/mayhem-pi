#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class MenuHandler {
public:
  MenuHandler();

  void reset();
  void draw(ALLEGRO_BITMAP *screen_buffer, ALLEGRO_FONT *font);

  void addline(char *line, bool selectable = true, int offset = 10);

  int get_current_line_index();

  char lines[1000][100];
  bool line_selectable[100];
  int line_offset[100];

  int num_lines = 0;
  int maxi = 0;
  int width = 0;
  int selected_idx = 0;
  int max_visible_lines = 0;
};

#endif // MENUHANDLER_H
