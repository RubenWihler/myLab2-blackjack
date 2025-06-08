#pragma once

#include "../utils/dyn_array/dyn_array.h"
#include <stdint.h>
#include <stdbool.h>

typedef void(*int_fn_t)(void);

bool gpio_int_init();
void gpio_int_free();
void gpio_int_handle();
void gpio_int_enable();
void gpio_int_set_fn(const uint8_t port, const uint8_t pin, const unsigned char mode, int_fn_t fn);


