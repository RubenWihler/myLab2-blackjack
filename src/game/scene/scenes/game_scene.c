#include "../scene.h"
#include "../../game.h"
#include "../../../liblcp/rendering/ui/elements/trigger_zone/trigger_zone.h"
#include "../../../liblcp/ledrgb/ledrgb.h"

#include "../../blackjack/blackjack.h"
#include "../../blackjack/render/blackjack_render.h"
#include "../../blackjack/popup/bet_popup/bet_popup.h"

extern const uint16_t game_bg_color;
extern const scene_api_t game_scene_api;
static const uint64_t initial_money = 10000;
static uint64_t current_money = 0;

static void game_load();
static void game_unload();
static void game_update();
static bool play_round();

const scene_api_t game_scene_api = {
    .load = game_load,
    .unload = game_unload,
    .update = game_update,
};

static void game_load()
{
    volatile bool playing = true;
    current_money = initial_money;

    while((playing = play_round()));

    game_load_scene(SCENE_TITLE_SCREEN);
}

static void game_unload()
{
    trigger_zone_clear();
}

static void game_update()
{
}

static bool play_round()
{
    uint64_t bet = 0;

    set_rgb_leds(0x00, 0x00, 0x00);
    draw_bg();
    draw_money(current_money);
    bet_popop_show(&current_money, &bet);

    if (bet == 0)
    {
        //fin de la partie
        return false;
    }

    bj_state_t round_state;
    bj_init(&round_state, &current_money, &bet);
    bj_start(&round_state);

    return current_money > 0;
}

