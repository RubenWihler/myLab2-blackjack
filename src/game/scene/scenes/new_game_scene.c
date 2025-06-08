#include "../scene.h"
#include "../../game.h"
#include "../../../liblcp/rendering/sprite/sprite.h"
#include "../../../liblcp/rendering/ui/elements/trigger_zone/trigger_zone.h"
#include "../../../res/sprites/new_game_bg.h"
#include "../../../liblcp/rendering/ui/elements/textbox/textbox.h"
#include "../../../liblcp/time/time.h"
#include "../../../liblcp/ledrgb/ledrgb.h"

extern const scene_api_t new_game_scene_api;

static void new_game_load();
static void new_game_unload();
static void new_game_update();

static void on_start_click();
static void on_back_click();
static void on_character_arrow_left_click();
static void on_character_arrow_right_click();
static void draw_character_name();

//generer par chatgpt (JetonMan tres drole)
static char* character_names[] = {
    "BlackjackPro432", "AceDealer21", "_LuckyChip_", "MisterVegas",
    "Jack21", "QueenOfClubs", "TheDealer", "AsDePique",
    "JetonMan", "Jetonathan", "JackLeNoir"
};
static int character_name_index = 0;
static const int character_name_count = sizeof(character_names)/sizeof(character_names[0]);

const scene_api_t new_game_scene_api = {
    .load = new_game_load,
    .unload = new_game_unload,
    .update = new_game_update,
};

static void new_game_load()
{
    sprite_render(SPRITE_NEW_GAME_BG, 0, 0);
    draw_character_name();

    trigger_zone_add((trigger_zone_t){{37, 207, 165, 38}, on_start_click});
    trigger_zone_add((trigger_zone_t){{37, 255, 165, 38}, on_back_click});
    trigger_zone_add((trigger_zone_t){{34, 120, 50, 50}, on_character_arrow_left_click});
    trigger_zone_add((trigger_zone_t){{156, 120, 50, 50}, on_character_arrow_right_click});

    set_rgb_leds(0x00, 0xff, 0x00); 
}

static void new_game_unload()
{
    trigger_zone_clear();
}

static void new_game_update()
{
}

static void on_start_click()
{
    game_load_scene(SCENE_GAME);
}

static void on_back_click()
{
    game_load_scene(SCENE_TITLE_SCREEN);
}


static void on_character_arrow_left_click()
{
    if (character_name_index == 0) character_name_index = character_name_count - 1;
    else character_name_index--;
    draw_character_name();
    time_wait_ms(50);
}

static void on_character_arrow_right_click()
{
    character_name_index = (character_name_index + 1) % character_name_count;
    draw_character_name();
    time_wait_ms(50);
}

static void draw_character_name()
{
    tbox_draw((tbox_t){
        .rect = {
            70,
            140, 
            100,
            25,
        },
        .color_bg = 0x8E4F,
        .color_fg = 0x0000,
        .color_border = 0x0000,
        .border = 0,
        .char_space = -2,
        .line_space = 0,
        .margin = 0,
        .font = font_small,
        .text = character_names[character_name_index]
    });
}
