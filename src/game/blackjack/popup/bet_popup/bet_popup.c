#include "bet_popup.h"

#include "../../../../liblcp/gpio/gpio_interrupts.h"
#include "../../../../liblcp/utils/string_utils/string_utils.h"
#include "../../../../liblcp/time/time.h"

//rendering
#include "../../../../liblcp/rendering/sprite/sprite.h"
#include "../../../../liblcp/rendering/drawing/draw_utils.h"
#include "../../../../liblcp/rendering/ui/elements/textbox/textbox.h"
#include "../../../../liblcp/rendering/ui/elements/trigger_zone/trigger_zone.h"

//sprite
#include "../../../../res/sprites/bet_popup.h"

#include <stdlib.h>
#include <stdbool.h>

extern const uint16_t game_bg_color;

static inline void draw_popup();
static inline void clear_popup();
static void enable_btn();
static void update_bet_tbox();

//btn
static void on_increment_click();
static void on_decrement_click();
static void on_25_percent_click();
static void on_50_percent_click();
static void on_75_percent_click();
static void on_100_percent_click();
static void on_ok_click();

//pointeur vers l'argent et la mise en global pour simplifier
static uint64_t *money_ptr = NULL;
static uint64_t *bet_ptr = NULL;
static bool ok_clicked = false;

//execution bloquante
void bet_popop_show(uint64_t *money, uint64_t *bet)
{
    *bet = 0;//peut etre faire en sorte que la mise soit la mise du tours d'avant

    money_ptr = money;
    bet_ptr = bet;
    draw_popup();
    enable_btn();
    update_bet_tbox();

    while (!ok_clicked)
    {
        gpio_int_handle();
        time_wait_ms(50);
    }

    clear_popup();
    trigger_zone_clear();
    ok_clicked = false;
    money_ptr = NULL;
    bet_ptr = NULL;
}

static inline void draw_popup()
{
    sprite_render(SPRITE_BET_POPUP, 20, 43);
}

static inline void clear_popup()
{
    draw_rect((rect_t){20,43,202,224}, game_bg_color);
}

static void enable_btn()
{
    trigger_zone_clear();//on clear avant pour eviter d'avoir d'autre boutton actifs

    //increment/decrement
    trigger_zone_add((trigger_zone_t){{171,  52, 44, 80}, on_increment_click});
    trigger_zone_add((trigger_zone_t){{171, 140, 44, 80}, on_decrement_click});

    //percent
    trigger_zone_add((trigger_zone_t){{ 31,  99, 60, 35}, on_25_percent_click});
    trigger_zone_add((trigger_zone_t){{ 31, 145, 60, 35}, on_50_percent_click});
    trigger_zone_add((trigger_zone_t){{104, 145, 60, 35}, on_75_percent_click});
    trigger_zone_add((trigger_zone_t){{104,  99, 60, 35}, on_100_percent_click});

    //ok
    trigger_zone_add((trigger_zone_t){{28,  226, 186, 30}, on_ok_click});
}


static void update_bet_tbox()
{
    char* bet_str = str_from_uint64(*bet_ptr);

    tbox_draw((tbox_t){
        .rect = {
            29,
            188, 
            135,
            30,
        },
        .color_bg = 0xDD9B,
        .color_fg = 0x0000,
        .color_border = 0x0000,
        .border = 0,
        .char_space = -2,
        .line_space = 0,
        .margin = 8,
        .font = font_small,
        .text = bet_str
    });

    free(bet_str);
}

static void on_increment_click()
{
    if (*bet_ptr < *money_ptr)
    {
        (*bet_ptr)++;
        update_bet_tbox();
    }
}

static void on_decrement_click()
{
    if (*bet_ptr > 0)
    {
        (*bet_ptr)--;
        update_bet_tbox();
    }
}

static void on_25_percent_click()
{
    *bet_ptr = *money_ptr / 4;
    update_bet_tbox();
}

static void on_50_percent_click()
{
    *bet_ptr = *money_ptr / 2;
    update_bet_tbox();
}

static void on_75_percent_click()
{
    *bet_ptr = *money_ptr * (3.0 / 4.0);
    update_bet_tbox();
}

static void on_100_percent_click()
{
    *bet_ptr = *money_ptr;
    update_bet_tbox();
}

static void on_ok_click()
{
    ok_clicked = true;
}

