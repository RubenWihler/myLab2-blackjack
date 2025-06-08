#pragma once

#include "../utils/rect.h"

#include <stdint.h>

typedef struct {
    const uint16_t width, height;
    const uint8_t *data;
} sprite_t;

typedef struct {
    rect_t rect;
    const sprite_t *sprite;
} sprite_renderer_t;

void sprite_render(const sprite_t sprite, const uint16_t pos_x, const uint16_t pos_y);
