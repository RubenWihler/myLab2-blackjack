#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
    *  Carte: 1 octet
    *  
    *  | FLAGS | TYPE | Value | 
    *  |   00  |  00  |  0000 |
    *
    *
    * flags:
    *   00 : Nothing
    *   01 : Carte a Joueur
    *   10 : Carte a Croupier
    *   11 : DONT'CARE
    *
    * type :
    *   00|DIAMONDS
    *   01|HEARTS
    *   10|CLUBS
    *   11|SPADES
    *
    * value:
    *    1|AS
    *    2| 2
    *    3| 3
    *    ...
    *   10|10
    *   11| J
    *   12| Q
    *   13| K
*/

typedef uint8_t card_t;

typedef enum {
    CARD_SUIT_DIAMONDS = 0x0, //00
    CARD_SUIT_HEARTS   = 0x1, //01
    CARD_SUIT_CLUBS    = 0x2, //10
    CARD_SUIT_SPADES   = 0x3  //11
} card_suit_e;

typedef enum {
    CARD_FLAG_NONE = 0x00,
    CARD_FLAG_PLAYER = 1<<6,
    CARD_FLAG_DEALER   = 1<<7
} card_flag_e;

card_t card_create(const uint8_t value, const card_suit_e suit, const card_flag_e flag);
bool card_is_valid(const card_t card);
card_suit_e card_get_suit(const card_t card);
uint8_t card_get_value(const card_t card);
bool card_is_player(const card_t card);
bool card_is_dealer(const card_t card);
