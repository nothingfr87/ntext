#include "includes/util.h"
#include "includes/editor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_file(Editor *ed) {
  ed->buffer.lines = malloc(sizeof(char *));
  ed->buffer.lines[0] = strdup("");
  ed->buffer.line_count = 1;

  FILE *fp = fopen(ed->filename, "r");
  if (!fp)
    return -1;

  free(ed->buffer.lines[0]);
  free(ed->buffer.lines);

  char line[4096];

  ed->buffer.lines = NULL;
  ed->buffer.line_count = 0;

  while (fgets(line, sizeof(line), fp)) {
    line[strcspn(line, "\n")] = '\0';

    ed->buffer.lines =
        realloc(ed->buffer.lines, (ed->buffer.line_count + 1) * sizeof(char *));

    ed->buffer.lines[ed->buffer.line_count] = strdup(line);
    ed->buffer.line_count++;
  }

  if (ed->buffer.line_count == 0) {
    ed->buffer.lines = malloc(sizeof(char *));
    ed->buffer.lines[0] = strdup("");
    ed->buffer.line_count = 1;
  }

  fclose(fp);
  return 0;
}

void save_file(Editor *ed) {
  FILE *fp = fopen(ed->filename, "w");
  if (!fp)
    return;

  for (size_t i = 0; i < ed->buffer.line_count; i++) {
    fputs(ed->buffer.lines[i], fp);
    fputc('\n', fp);
  }

  fclose(fp);
}

void del_char(Editor *ed) {
  char *line = ed->buffer.lines[ed->cursor_y - 1];

  size_t len = strlen(line);

  if (ed->cursor_x == 0)
    return;

  ed->cursor_x--;

  memmove(&line[ed->cursor_x], &line[ed->cursor_x + 1], len - ed->cursor_x);

  line = realloc(line, len);
  ed->buffer.lines[ed->cursor_y - 1] = line;
}

void insert_char(Editor *ed, char c) {
  char *line = ed->buffer.lines[ed->cursor_y - 1];

  size_t len = strlen(line);

  line = realloc(line, len + 2);

  memmove(&line[ed->cursor_x + 1], &line[ed->cursor_x], len - ed->cursor_x + 1);

  line[ed->cursor_x] = c;

  ed->buffer.lines[ed->cursor_y - 1] = line;
  ed->cursor_x++;
}

void insert_newline(Editor *ed) {
  char *line = ed->buffer.lines[ed->cursor_y - 1];

  char *left = strndup(line, ed->cursor_x);
  char *right = strdup(line + ed->cursor_x);

  free(line);
  ed->buffer.lines[ed->cursor_y - 1] = left;

  ed->buffer.lines =
      realloc(ed->buffer.lines, (ed->buffer.line_count + 1) * sizeof(char *));

  memmove(&ed->buffer.lines[ed->cursor_y + 1], &ed->buffer.lines[ed->cursor_y],
          (ed->buffer.line_count - ed->cursor_y) * sizeof(char *));

  ed->buffer.lines[ed->cursor_y] = right;
  ed->buffer.line_count++;

  ed->cursor_y++;
  ed->cursor_x = 0;
}

void del_newline(Editor *ed) {
  if (ed->cursor_y == 1)
    return;

  char *prev = ed->buffer.lines[ed->cursor_y - 2];
  char *curr = ed->buffer.lines[ed->cursor_y - 1];

  size_t prev_len = strlen(prev);
  size_t curr_len = strlen(curr);

  prev = realloc(prev, prev_len + curr_len + 1);
  memcpy(prev + prev_len, curr, curr_len + 1);

  ed->buffer.lines[ed->cursor_y - 2] = prev;

  free(curr);

  memmove(&ed->buffer.lines[ed->cursor_y - 1], &ed->buffer.lines[ed->cursor_y],
          (ed->buffer.line_count - ed->cursor_y) * sizeof(char *));

  ed->buffer.line_count--;

  ed->buffer.lines =
      realloc(ed->buffer.lines, ed->buffer.line_count * sizeof(char *));

  ed->cursor_y--;
  ed->cursor_x = prev_len;
}
