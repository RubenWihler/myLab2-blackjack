#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t x, y;
    uint16_t w, h;
} rect_t;

bool in_rect(const rect_t rect, const uint16_t x, const uint16_t y);


