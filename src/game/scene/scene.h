#pragma once

#include <stdbool.h>

extern const int SCENE_COUNT;

typedef enum {
    SCENE_TITLE_SCREEN = 0,
    SCENE_CREDIT = 1,
    SCENE_NEW_GAME = 2,
    SCENE_GAME = 3,
} scenes_e;

typedef struct {
    void (*load)();
    void (*unload)();
    void (*update)();
} scene_api_t;

typedef struct {
    scene_api_t api;
    scenes_e id;
} scene_t;

bool scene_init(scene_t *scene, scenes_e scene_id);
void scene_load(scene_t *scene);
void scene_unload(scene_t *scene);
void scene_update(scene_t *scene);

