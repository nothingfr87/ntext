#ifndef UI_H
#define UI_H

#include "editor.h"

extern int cursor_y;
extern int cursor_x;

void ui_init(void);
void ui_destroy(void);

void ui_draw_header(const char *filename);
void ui_draw_buffer(Editor *ed);
void ui_draw_footer(void);

void ui_refresh(Editor *ed);

#endif
