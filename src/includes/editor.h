#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>

typedef struct {
  char **lines;
  size_t line_count;
} Buffer;

typedef struct {
  const char *filename;

  int cursor_x;
  int cursor_y;

  int row_offset;
  int col_offset;

  Buffer buffer;
} Editor;

#endif
