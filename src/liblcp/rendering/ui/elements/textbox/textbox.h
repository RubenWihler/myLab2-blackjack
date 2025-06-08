#pragma once

#include "../../../utils/rect.h"
#include "../../fonts/fonts.h"

typedef struct {
    rect_t rect;
    uint16_t color_fg, color_bg, color_border;
    uint16_t margin, border, line_space, char_space;
    char *text;
    font_t* font;
} tbox_t;

void tbox_draw(tbox_t tbox);
