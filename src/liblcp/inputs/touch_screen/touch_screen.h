#pragma once

#include <stdint.h>
#include <stdbool.h>

bool touch_screen_init();
uint8_t touch_screen_get_position(uint16_t *x_f1, uint16_t *y_f1, uint16_t *x_f2, uint16_t *y_f2);
