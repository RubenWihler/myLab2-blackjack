#include "game.h"

#include "scene/scene.h"
#include "../liblcp/log/log.h"
#include "../liblcp/gpio/gpio_interrupts.h"

#include <stdlib.h>

static game_t *game_singleton = NULL;
static void game_loop(game_t *game);

game_t *game_instance()
{
    if (!game_singleton)
    {
        LOG_ERROR("Game is not initialized !", false);
        return NULL;
    }

    return game_singleton;
}

bool game_init(game_t *game)
{
    if (game_singleton) return false;
    game_singleton = game;

    game->scene_index = 0;

    game->scenes = malloc(SCENE_COUNT * sizeof(scene_t));
    if (!game->scenes) return false;

    scene_init(&game->scenes[SCENE_TITLE_SCREEN], SCENE_TITLE_SCREEN);
    scene_init(&game->scenes[SCENE_NEW_GAME],     SCENE_NEW_GAME);
    scene_init(&game->scenes[SCENE_CREDIT],       SCENE_CREDIT);
    scene_init(&game->scenes[SCENE_GAME],         SCENE_GAME);

    return true;
}

void game_start(game_t *game)
{
    scene_load(&game->scenes[game->scene_index]);
    game_loop(game);
}

void game_stop(game_t *game)
{
    scene_unload(&game->scenes[game->scene_index]);
}

void game_destroy(game_t *game)
{
    free(game->scenes);
    game->scenes = NULL;

    game_singleton = NULL;
}

void game_load_scene(int index)
{
    game_t *game = game_instance();

    if (index > SCENE_COUNT)
    {
        LOG_ERROR("Index out of bounds !", false);
        return;
    }

    game->scenes[game->scene_index].api.unload();
    game->scenes[index].api.load();
    game->scene_index = index;
}


static void game_loop(game_t *game)
{
    while (true)
    {
        scene_update(&game->scenes[game->scene_index]);
        gpio_int_handle();
    }
}
