#pragma once

#include "../card/card.h"

typedef enum {
    CARD_OWNER_PLAYER,
    CARD_OWNER_DEALER
} card_owner_e;

typedef enum {
    BIG_TEXT_BUST,
    BIG_TEXT_LOSE,
    BIG_TEXT_WIN,
    BIG_TEXT_BLACKJACK,
    BIG_TEXT_PUSH
} big_text_e;

extern const uint16_t game_bg_color;

void draw_cards(card_t *cards, const uint8_t count, const card_owner_e owner);
void draw_total(const uint8_t total, const card_owner_e owner);
void draw_bet(const uint64_t bet);
void draw_money(const uint64_t money);
void draw_big_text(const big_text_e btext);
void draw_bg();

