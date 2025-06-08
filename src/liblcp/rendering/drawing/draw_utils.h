#pragma once

#include <stdint.h>

#include "../utils/rect.h"

void draw_rect(const rect_t rect, const uint16_t color);
void draw_gradient(const rect_t rect, const uint16_t color_start, const uint16_t color_end, const char axe);



