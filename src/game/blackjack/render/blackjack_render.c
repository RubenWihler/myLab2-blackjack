#include "blackjack_render.h"

#include "../../../liblcp/rendering/sprite/sprite.h"
#include "../../../liblcp/rendering/drawing/draw_utils.h"
#include "../../../liblcp/rendering/ui/elements/textbox/textbox.h"
#include "../../../liblcp/utils/string_utils/string_utils.h"
#include "../../../liblcp/ledrgb/ledrgb.h"

//sprites
#include "../../../res/sprites/card_icons/diamonds.h"
#include "../../../res/sprites/card_icons/hearts.h"
#include "../../../res/sprites/card_icons/clubs.h"
#include "../../../res/sprites/card_icons/spades.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern uint16_t screen_width;
extern uint16_t screen_height;

const uint16_t game_bg_color = 0x3568;
static const uint16_t text_color = 0xfe05; 

static const uint16_t card_offset_y = 90;
static const uint16_t card_width = 40;
static const uint16_t card_height = 56;
static const uint16_t card_color_red = 0xf945;
static const uint16_t card_color_black = 0x0000;
static const uint16_t card_icon_sprite_width  = 16;
static const uint16_t card_icon_sprite_height = 16;

static const uint16_t total_dealer_tbox_y = 111;
static const uint16_t total_player_tbox_y = 210;

//espace negatif entre les cartes
//expl: carte[2].pos_x = carte[1].pos_x + card_gap 
static const uint16_t card_gap = card_width/2;

static void draw_card(const card_t card, const uint16_t x, const uint16_t y);
static void draw_card_icon(const card_suit_e suit, const uint16_t x, const uint16_t y);
static void draw_card_value(const uint8_t value, const card_suit_e type, const uint16_t x, const uint16_t y);
static char* get_card_value_str(const uint8_t value);
static const sprite_t get_card_icon_sprite(const card_suit_e card_suit);
static const char* get_big_text_text(const big_text_e btext);

void draw_cards(card_t *cards, const uint8_t count, const card_owner_e owner)
{
    if (count < 1) return;

    const uint16_t pos_y = (owner == CARD_OWNER_PLAYER) ? screen_height - card_offset_y : card_offset_y/2;

    const uint16_t total_width = (card_gap * (count-1)) + card_width;
    const uint16_t offset_x = (screen_width - (total_width)) / 2;

    for (uint8_t i = 0; i < count; i++)
    {
        const uint16_t pos_x = offset_x + (card_gap * i);
        draw_card(cards[i], pos_x, pos_y);
    }
}

void draw_total(const uint8_t total, const card_owner_e owner)
{
    const uint16_t pos_y = (owner == CARD_OWNER_PLAYER) ? total_player_tbox_y : total_dealer_tbox_y;
    const uint16_t pos_x = (screen_width/2) - 75;

    const uint16_t width = 150;
    const uint16_t height = 15;

    char str[10];
    strcpy(str, (owner == CARD_OWNER_PLAYER) ? "player:" : "dealer:");
    char* total_str = str_from_uint16(total); 
    strcpy(str+7, total_str);

    tbox_draw((tbox_t){
        .rect = {
            pos_x,
            pos_y, 
            width,
            height,
        },
        .color_bg = game_bg_color,
        .color_fg = text_color,
        .color_border = 0x0000,
        .border = 0,
        .char_space = -2,
        .line_space = 0,
        .margin = 0,
        .font = font_large,
        .text = str
    });

    free(total_str);
}

void draw_bet(const uint64_t bet)
{
    const uint16_t width = 240;
    const uint16_t height = 15;

    char str[4+20+2];//20 car log10((1<<64)-1) ~= 20 
    strcpy(str, "Bet:");
    char* bet_str = str_from_uint64(bet); 
    strcpy(str+4, bet_str);
    strcpy(str+4+strlen(bet_str), "$");

    tbox_draw((tbox_t){
        .rect = {
            8,
            26, 
            width,
            height,
        },
        .color_bg = game_bg_color,
        .color_fg = text_color,
        .color_border = 0x0000,
        .border = 0,
        .char_space = -2,
        .line_space = 0,
        .margin = 0,
        .font =  font_small,
        .text = str
    });

    free(bet_str);
}

void draw_money(const uint64_t money)
{
    const uint16_t width = 240;
    const uint16_t height = 20;

    char str[6+20+2];//20 car log10(1<<64)+1 = 20 
    strcpy(str, "Money:");
    char* money_str = str_from_uint64(money); 
    strcpy(str+6, money_str);
    strcpy(str+6+strlen(money_str), "$");

    tbox_draw((tbox_t){
        .rect = {
            8,
            8, 
            width,
            height,
        },
        .color_bg = game_bg_color,
        .color_fg = text_color,
        .color_border = 0x0000,
        .border = 0,
        .char_space = -2,
        .line_space = 0,
        .margin = 0,
        .font = font_small,
        .text = str
    });

    free(money_str);
} 

void draw_big_text(const big_text_e btext)
{
    uint16_t color_bg;
    uint16_t color_fg;

    if (btext == BIG_TEXT_BUST || btext == BIG_TEXT_LOSE)
    {
        color_bg = 0x5082;
        color_fg = 0xf904;
        set_rgb_leds(0xff, 0x00, 0x00);
    }
    else if (btext == BIG_TEXT_BLACKJACK || btext == BIG_TEXT_WIN)
    {
        color_bg = 0x2262;
        color_fg = 0x2fe4;
        set_rgb_leds(0x0, 0xff, 0x00);
    }
    else 
    {
        color_bg = 0x2125;
        color_fg = 0xcebc;
        set_rgb_leds(0xf0, 0xf8, 0xff);
    }

    draw_rect((rect_t){0,0,screen_width,screen_height}, color_bg);
    const char* str = get_big_text_text(btext);
    uint16_t text_width = strlen(str)*16;

    tbox_draw((tbox_t){
        .rect = {
            (240-text_width)/2,
            (screen_height/2)-15, 
            text_width,
            30,
        },
        .color_bg = color_bg,
        .color_fg = color_fg,
        .color_border = 0x0000,
        .border = 0,
        .char_space = 0,
        .line_space = 0,
        .margin = 0,
        .font = font_large,
        .text = (char*)str
    });
}


void draw_bg()
{
    draw_rect((rect_t){0,0,screen_width,screen_height}, game_bg_color);
}

//position en haut a gauche de la cates (pas au milieu)
static void draw_card(const card_t card, const uint16_t x, const uint16_t y)
{
    const card_suit_e card_suit = card_get_suit(card);
    const uint8_t card_value = card_get_value(card);

    draw_rect((rect_t){x,y,card_width,card_height}, 0xFFFF);
    draw_card_value(card_value, card_suit, x, y);
    draw_card_icon(card_suit, x, y);
}

//position x,y de la carte pas du text
static void draw_card_icon(const card_suit_e suit, const uint16_t x, const uint16_t y)
{
    const uint16_t icon_x = x + (card_width/2) - (card_icon_sprite_width/2);
    const uint16_t icon_y = y + (card_height/2) - (card_icon_sprite_height/2);
    const sprite_t icon_sprite = get_card_icon_sprite(suit);
    sprite_render(icon_sprite, icon_x, icon_y);
}

//position x,y de la carte pas du text
static void draw_card_value(const uint8_t value, const card_suit_e suit, const uint16_t x, const uint16_t y)
{
    const uint16_t color = (suit == CARD_SUIT_HEARTS || suit == CARD_SUIT_DIAMONDS) ? card_color_red : card_color_black;
    char *card_value_str = get_card_value_str(value);

    tbox_draw((tbox_t){
        .rect = {
            x,
            y, 
            20,
            20,
        },
        .color_bg = 0xffff,
        .color_fg = color,
        .color_border = 0x0000,
        .border = 0,
        .char_space = -6,
        .line_space = 0,
        .margin = 2,
        .font = font_large,
        .text = card_value_str
    });

    free(card_value_str);
}

static char* get_card_value_str(const uint8_t value)
{
    if (value > 1 && value < 11)
    {
        return str_from_uint16(value);
    }

    //obliger d'alloue sur le heap car on free apres
    //(on pourrais faire autrement genre mettre un boolean a true 
    //si on doit free mais ca complique un peu pour rien)
    char * str = malloc(2 * sizeof(char));

    if      (value ==  1) str[0] = 'A';
    else if (value == 11) str[0] = 'J';
    else if (value == 12) str[0] = 'Q';
    else if (value == 13) str[0] = 'K';

    str[1] = '\0';
    return str;
}

static const sprite_t get_card_icon_sprite(const card_suit_e card_suit)
{
    switch (card_suit)
    {
    case CARD_SUIT_DIAMONDS: return SPRITE_DIAMONDS;
    case CARD_SUIT_HEARTS:   return SPRITE_HEARTS;
    case CARD_SUIT_CLUBS:    return SPRITE_CLUBS;
    case CARD_SUIT_SPADES:   return SPRITE_SPADES;
    }
}

static const char* get_big_text_text(const big_text_e btext)
{
    switch (btext)
    {
    case BIG_TEXT_BUST:      return "BUST";
    case BIG_TEXT_LOSE:      return "LOSE";
    case BIG_TEXT_WIN:       return "WIN";
    case BIG_TEXT_BLACKJACK: return "BLACKJACK";
    case BIG_TEXT_PUSH:      return "PUSH";

    default: return NULL;
    }
}
