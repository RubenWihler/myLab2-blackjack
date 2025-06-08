#include "../scene.h"
#include "../../game.h"
#include "../../../liblcp/rendering/sprite/sprite.h"
#include "../../../liblcp/rendering/drawing/draw_utils.h"
#include "../../../liblcp/rendering/ui/elements/trigger_zone/trigger_zone.h"
#include "../../../res/sprites/credit.h"
#include "../../../liblcp/ledrgb/ledrgb.h"
#include "../../../liblcp/rendering/utils/color_utils.h"
#include "../../../liblcp/time/time.h"

#include <stdlib.h>

extern const scene_api_t credit_scene_api;
extern const uint16_t screen_width, screen_height;
extern const uint16_t game_bg_color;

static void credit_load();
static void credit_unload();
static void credit_update();
static void on_back_click();

const scene_api_t credit_scene_api = {
    .load = credit_load,
    .unload = credit_unload,
    .update = credit_update,
};

static void credit_load()
{
    const rect_t btn_back_rect = {30, 244,175, 40};

    draw_rect((rect_t){0,0, screen_width, screen_height}, game_bg_color);
    sprite_render(SPRITE_CREDIT, 15, 20);

    trigger_zone_clear();
    trigger_zone_add((trigger_zone_t){btn_back_rect, on_back_click});
}

static void credit_unload()
{
    trigger_zone_clear();
}

static void credit_update()
{
    //led arc-en-ciel generer par ChatGPT (fonction hsv_to_rgb)
    static float hue = 0.0f;
    static uint8_t r, g, b;

    //time_ms vient de #include "/liblcp/time/time.h"
    if ((time_ms % 37) == 0)
    {
        hsv_to_rgb(hue, 1.0f, 1.0f, &r, &g, &b);
        set_rgb_leds(r, g, b);
    }

    hue += 0.7f;
    if (hue >= 360.0f) hue = 0.0f;
}

static void on_back_click()
{
    game_load_scene(SCENE_TITLE_SCREEN);
}
