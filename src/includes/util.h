#ifndef UTIL_H
#define UTIL_H

#include "editor.h"

int load_file(Editor *ed);
void save_file(Editor *ed);
void del_char(Editor *ed);
void insert_char(Editor *ed, char c);

#endif
