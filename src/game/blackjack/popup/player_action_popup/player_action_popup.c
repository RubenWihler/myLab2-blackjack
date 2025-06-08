#include "player_action_popup.h"

#include "../../../../liblcp/gpio/gpio_interrupts.h"
#include "../../../../liblcp/rendering/sprite/sprite.h"
#include "../../../../liblcp/rendering/drawing/draw_utils.h"
#include "../../../../liblcp/rendering/ui/elements/trigger_zone/trigger_zone.h"

//sprite
#include "../../../../res/sprites/hit_btn.h"
#include "../../../../res/sprites/stand_btn.h"

#include <stdbool.h>

extern const uint16_t game_bg_color;

static bool hit_clicked = false;
static bool stand_clicked = false;

static inline void draw_popup();
static inline void clear_popup();
static void enable_btn();

static void on_hit_click();
static void on_stand_click();

void player_action_popup_show(player_action_e *action)
{
    draw_popup();
    enable_btn();

    while (!hit_clicked && !stand_clicked)
    {
        gpio_int_handle();
    }

    *action = (hit_clicked) ? PLAYER_ACTION_HIT : PLAYER_ACTION_STAND;

    clear_popup();
    trigger_zone_clear();
    hit_clicked = false;
    stand_clicked = false;
}

static inline void draw_popup()
{
    sprite_render(SPRITE_BTN_STAND, 10, 130);
    sprite_render(SPRITE_BTN_HIT, 130, 130);
}

static inline void clear_popup()
{
    draw_rect((rect_t){10,130,220, 75}, game_bg_color);
}

static void enable_btn()
{
    trigger_zone_clear();
    trigger_zone_add((trigger_zone_t){{10,  130, 100, 75}, on_stand_click});
    trigger_zone_add((trigger_zone_t){{130, 130, 100, 75}, on_hit_click});
}

static void on_hit_click()
{
    hit_clicked = true;
    stand_clicked = false;//on s'assure que stand est a false
}

static void on_stand_click()
{
    stand_clicked = true;
    hit_clicked = false;//on s'assure que hit est a false
}
