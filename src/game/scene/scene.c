#include "scene.h"
#include "../../liblcp/log/log.h"

const int SCENE_COUNT = 4;
extern const scene_api_t title_screen_scene_api;
extern const scene_api_t credit_scene_api;
extern const scene_api_t new_game_scene_api;
extern const scene_api_t game_scene_api;

static scene_api_t get_scene_api(scenes_e id);

bool scene_init(scene_t *scene, scenes_e scene_id)
{
    scene->id = scene_id;
    scene->api = get_scene_api(scene_id);
    return true;
}

void scene_load(scene_t *scene)
{
    scene->api.load();
}

void scene_unload(scene_t *scene)
{
    scene->api.unload();
}

void scene_update(scene_t *scene)
{
    scene->api.update();
}

static scene_api_t get_scene_api(scenes_e id)
{
    switch (id)
    {
    case SCENE_TITLE_SCREEN: return title_screen_scene_api;
    case SCENE_NEW_GAME: return new_game_scene_api;
    case SCENE_CREDIT: return credit_scene_api;
    case SCENE_GAME: return game_scene_api;

    default: LOG_ERROR("Unknown scene", true);
    }

    return (scene_api_t){0};
}
