#include "includes/ui.h"
#include "includes/editor.h"
#include <ncurses.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static WINDOW *header;

void ui_init(void) {
  initscr();
  noecho();
  cbreak();
  curs_set(1);
  timeout(-1);
  keypad(stdscr, TRUE);
}

void ui_destroy(void) { endwin(); }

void ui_draw_header(const char *filename) {
  int len = strlen(filename);

  attron(A_REVERSE);
  mvhline(0, 0, ' ', COLS);
  mvprintw(0, 3, "NTEXT");
  mvprintw(0, (COLS - len) / 2, "%s", filename);
  attroff(A_REVERSE);
}

void ui_draw_buffer(Editor *ed) {
  int max_rows = LINES - 3;

  for (int y = 0; y < LINES - 3; y++) {

    int file_row = y + ed->row_offset;

    if (file_row >= ed->buffer.line_count)
      break;

    char *line = ed->buffer.lines[file_row];

    if ((int)strlen(line) > ed->col_offset)
      mvaddnstr(y + 1, 0, line + ed->col_offset, COLS);
  }
}

void ui_draw_footer(void) {
  const char *str = "Ctrl+S: Save\t\tCtrl+Q: Quit";

  attron(A_REVERSE);

  mvhline(LINES - 2, 0, ' ', COLS);
  mvprintw(LINES - 2, 3, "%s", str);

  attroff(A_REVERSE);
}

void ui_refresh(Editor *ed) {
  if (ed->cursor_y - 1 < ed->row_offset)
    ed->row_offset = ed->cursor_y - 1;

  if (ed->cursor_y - 1 >= ed->row_offset + (LINES - 3))
    ed->row_offset = ed->cursor_y - (LINES - 3);

  if (ed->cursor_x < ed->col_offset)
    ed->col_offset = ed->cursor_x;

  if (ed->cursor_x >= ed->col_offset + COLS)
    ed->col_offset = ed->cursor_x - COLS + 1;

  erase();

  ui_draw_header(ed->filename);
  ui_draw_buffer(ed);
  ui_draw_footer();

  move((ed->cursor_y - 1 - ed->row_offset) + 1, ed->cursor_x - ed->col_offset);

  refresh();
}
