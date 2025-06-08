#pragma once

#include "../../../utils/rect.h"
#include "../../../../utils/dyn_array/dyn_array.h"
#include <stdbool.h>

typedef struct {
    dyn_array_t *zones;
} trigger_zone_manager_t;

typedef struct {
    rect_t rect;
    void (*on_trigger)(void);
} trigger_zone_t;

bool trigger_zone_init();
void trigger_zone_add(const trigger_zone_t tzone);
void trigger_zone_clear();
void trigger_zone_test(const uint16_t x, const uint16_t y);
