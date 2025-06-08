#include "../scene.h"
#include "../../game.h"
#include "../../../liblcp/rendering/sprite/sprite.h"
#include "../../../liblcp/rendering/drawing/draw_utils.h"
#include "../../../liblcp/rendering/ui/elements/trigger_zone/trigger_zone.h"
#include "../../../liblcp/ledrgb/ledrgb.h"
#include "../../../liblcp/time/time.h"

#include "../../../res/sprites/title.h"
#include "../../../res/sprites/new_game_btn.h"
#include "../../../res/sprites/credit_btn.h"

extern const scene_api_t title_screen_scene_api;
extern const uint16_t screen_width, screen_height;
extern const uint16_t game_bg_color;

static void title_screen_load();
static void title_screen_unload();
static void title_screen_update();

static void on_new_game_click();
static void on_credit_click();

const scene_api_t title_screen_scene_api = {
    .load = title_screen_load,
    .unload = title_screen_unload,
    .update = title_screen_update,
};

static void title_screen_load()
{
    const rect_t btn_new_game_rect = {37, 182, SPRITE_BTN_NEW_GAME.width, SPRITE_BTN_NEW_GAME.height},
                 btn_credit_rect   = {37, 233, SPRITE_BTN_CREDIT.width,   SPRITE_BTN_CREDIT.height},
                 title_rect        = {24,  61, SPRITE_TITLE.width,        SPRITE_TITLE.height};

    draw_rect((rect_t){0,0, screen_width, screen_height}, game_bg_color);
    sprite_render(SPRITE_TITLE, title_rect.x, title_rect.y);
    sprite_render(SPRITE_BTN_NEW_GAME, btn_new_game_rect.x, btn_new_game_rect.y);
    sprite_render(SPRITE_BTN_CREDIT, btn_credit_rect.x, btn_credit_rect.y);

    trigger_zone_clear();
    trigger_zone_add((trigger_zone_t){btn_new_game_rect, on_new_game_click});
    trigger_zone_add((trigger_zone_t){btn_credit_rect, on_credit_click});
}

static void title_screen_unload()
{
    trigger_zone_clear();
}

static void title_screen_update()
{
    const uint32_t delay_between_change_led_ms = 500;

    static uint32_t target_time_change_led = 0;
    static uint64_t colors[] = {0xff0000, 0x00ff00};
    static uint8_t color_index = 0;

    if (target_time_change_led < time_ms)
    {
        target_time_change_led = time_ms + delay_between_change_led_ms;
        uint64_t color = colors[color_index];
        set_rgb_leds(color >> 16, color >> 8, color & 0xff);

        color_index++;
        if (color_index > sizeof(colors)/sizeof(colors[0]) - 1)
        {
            color_index = 0;
        }
    }
}

static void on_new_game_click()
{
    set_rgb_leds(0xff, 0xff, 0x00);
    game_load_scene(SCENE_NEW_GAME);
}

static void on_credit_click()
{
    game_load_scene(SCENE_CREDIT);
}
