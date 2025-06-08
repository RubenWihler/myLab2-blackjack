#pragma once

#include "card/card.h"

#include <stdint.h>
#include <stdbool.h>

typedef card_t deck_t[52];

typedef struct {
    deck_t deck;
    card_t player_cards[11]; //11 carte max (4*1+4*2+3*3=21)
    card_t dealer_cards[10];   //10 carte max car bank peut pas hit apres 17
    uint8_t draw_index, player_index, dealer_index;
    uint64_t *money, *bet;
} bj_state_t;

void bj_init(bj_state_t *state, uint64_t *money, uint64_t *bet);
void bj_start(bj_state_t *state);

