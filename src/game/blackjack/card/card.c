#include "card.h"


card_t card_create(const uint8_t value, const card_suit_e suit, const card_flag_e flag)
{
    return (flag & 0xC0) | ((suit & 0x03) << 4) | (value & 0x0F);
}

bool card_is_valid(const card_t card)
{
    uint8_t value = card_get_value(card);
    return (value >= 1 && value <= 13);
}

card_suit_e card_get_suit(const card_t card)
{
    return (card >> 4) & 0x03;
}

uint8_t card_get_value(const card_t card)
{
    return card & 0x0F;
}

bool card_is_player(const card_t card)
{
    return card & CARD_FLAG_PLAYER;
}

bool card_is_dealer(const card_t card)
{
    return card & CARD_FLAG_DEALER;
}
