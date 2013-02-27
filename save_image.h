#include <vector>

#ifndef SAVE_IMAGE__H
#define SAVE_IMAGE__H

#include "window.h"

void plot(window<int> &scr, std::vector<int> &colors, int iter_max, const char *fname, bool smooth_color);

#endif
