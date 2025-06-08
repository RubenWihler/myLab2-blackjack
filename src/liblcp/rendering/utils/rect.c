#include "rect.h"


bool in_rect(const rect_t rect, const uint16_t x, const uint16_t y)
{
    return x >= rect.x
        && y >= rect.y
        && x <= (rect.x + rect.w)
        && y <= (rect.y + rect.h);
}
