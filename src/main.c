#include "includes/editor.h"
#include "includes/input.h"
#include "includes/ui.h"
#include "includes/util.h"

int main(int argc, char **argv) {
  Editor editor = {
      .filename = (argc > 1) ? argv[1] : "[Untitled]",
      .cursor_x = 0,
      .cursor_y = 1,
      .row_offset = 0,
      .col_offset = 0,
  };

  load_file(&editor);

  ui_init();

  ui_refresh(&editor);

  while (read_keys(&editor)) {
    ui_refresh(&editor);
  }

  ui_destroy();

  return 0;
}
