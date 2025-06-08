#pragma once
#include "scene/scene.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    scene_t *scenes;
    uint8_t scene_index;
} game_t;

game_t *game_instance();

bool game_init(game_t *game);
void game_start(game_t *game);
void game_stop(game_t *game);
void game_destroy(game_t *game);

void game_load_scene(int index);
