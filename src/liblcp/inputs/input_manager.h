#pragma once

#include "../utils/dyn_array/dyn_array.h"
#include <stdint.h>

typedef enum {
    BUTTON_A = 0,
    BUTTON_B = 1,
    JOYSTICK = 2,
    TOUCH_SCREEN = 3,
} input_type_e;

typedef struct {
    dyn_array_t **input_handlers;
} input_manager_t;

#define INPUT_MANAGER ((input_manager_t*)input_manager_get_instance())

input_manager_t *input_manager_get_instance();
input_manager_t *input_manager_init();
void input_manager_destroy();
void input_manager_add_listener(const input_type_e type, void* fn_listener);
