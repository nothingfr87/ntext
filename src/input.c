#include "includes/input.h"
#include "includes/editor.h"
#include "includes/util.h"
#include <ncurses.h>
#include <string.h>

#define CTRL_KEY(k) ((k) & 0x1f)

bool read_keys(Editor *ed) {
  int c;
  c = getch();

  switch (c) {
  case CTRL_KEY('q'):
    return false;
    break;

  case CTRL_KEY('s'):
    save_file(ed);
    break;

  case KEY_UP:
    if (ed->cursor_y > 1) {
      ed->cursor_y--;

      size_t len = strlen(ed->buffer.lines[ed->cursor_y - 1]);
      if (ed->cursor_x > (int)len)
        ed->cursor_x = len;
    }
    break;

  case KEY_DOWN:
    if (ed->cursor_y < (int)ed->buffer.line_count) {
      ed->cursor_y++;

      size_t len = strlen(ed->buffer.lines[ed->cursor_y - 1]);
      if (ed->cursor_x > (int)len)
        ed->cursor_x = len;
    }
    break;

  case KEY_LEFT:
    if (ed->cursor_x > 0)
      ed->cursor_x--;
    break;

  case KEY_RIGHT: {
    char *line = ed->buffer.lines[ed->cursor_y - 1];
    size_t len = strlen(line);

    if (ed->cursor_x < (int)len)
      ed->cursor_x++;
    break;
  }
  case KEY_BACKSPACE:
    if (ed->cursor_x == 0)
      del_newline(ed);
    else
      del_char(ed);
    break;
  case '\n':
  case KEY_ENTER:
  case '\r':
    insert_newline(ed);
    break;
  default:
    if (c >= 32 && c <= 126) {
      insert_char(ed, c);
    }
    break;
  }
  return true;
}
