#include "blackjack.h"
#include "render/blackjack_render.h"
#include "../blackjack/popup/player_action_popup/player_action_popup.h"
#include "../../liblcp/time/time.h"

#include <stdlib.h>
#include <string.h>

static const uint16_t delay_player_draw_ms = 500;
static const uint16_t delay_dealer_draw_ms = 1000;
static const float blackjack_win_factor = 2.5f;
static const uint8_t win_factor = 2;

static inline card_t draw(bj_state_t *state);
static void draw_state(bj_state_t *state);
static uint8_t get_total(card_t *cards, uint8_t count);

void bj_init(bj_state_t *state, uint64_t *money, uint64_t *bet)
{
    memset(state, 0, sizeof(*state));

    state->money = money;
    state->bet = bet;

    //initialisation du deck
    for (int i = 0; i < 52; i++)
    {
        uint8_t val = (i%13)+1;//+1 car as = 1 et pas 0
        uint8_t type = (i/13);
        state->deck[i] = card_create(val, type, CARD_FLAG_NONE);
    }

    //melange du deck
    for (int i = 51; i > 0; i--)
    {
        int j = rand() % (i + 1);
        card_t tmp = state->deck[i];
        state->deck[i] = state->deck[j];
        state->deck[j] = tmp;
    }
}

void bj_start(bj_state_t *state)
{
    //on retire la mise au debut de la partie
    *state->money -= *state->bet;

    draw_money(*state->money);
    draw_bet(*state->bet);

    //player pioche
    state->player_cards[state->player_index++] = draw(state);
    draw_state(state);
    time_wait_ms(delay_player_draw_ms);

    //dealer pioche
    state->dealer_cards[state->dealer_index++] = draw(state);
    draw_state(state);
    time_wait_ms(delay_dealer_draw_ms);

    //player pioche tant que :
    //  - total < 21
    //  - ne stand pas
    while (get_total(&state->player_cards[0], state->player_index) < 21)
    {
        player_action_e action;
        player_action_popup_show(&action);

        if (action == PLAYER_ACTION_STAND)
        {
            break;
        }

        state->player_cards[state->player_index++] = draw(state);
        draw_state(state);
        time_wait_ms(delay_player_draw_ms);
    }

    const uint8_t player_total = get_total(&state->player_cards[0], state->player_index);

    //player bust
    if (player_total > 21)
    {
        draw_big_text(BIG_TEXT_BUST);
        time_wait_ms(1000);
        return;
    }

    //bank pioche tant que :
    //  - total < 17
    while (get_total(&state->dealer_cards[0], state->dealer_index) < 17)
    {
        state->dealer_cards[state->dealer_index++] = draw(state);
        draw_state(state);
        time_wait_ms(delay_dealer_draw_ms);
    }

    const uint8_t dealer_total = get_total(&state->dealer_cards[0], state->dealer_index);

    if (player_total > dealer_total || dealer_total > 21)
    {
        if (player_total == 21 && state->player_index == 2)
        {
            *state->money += *state->bet * blackjack_win_factor;
            draw_big_text(BIG_TEXT_BLACKJACK);
            time_wait_ms(1000);
        }
        else
        {
            *state->money += *state->bet * win_factor;
            draw_big_text(BIG_TEXT_WIN);
            time_wait_ms(1000);
        }
    }
    else if (player_total < dealer_total)
    {
        draw_big_text(BIG_TEXT_LOSE);
        time_wait_ms(1000);
    }
    else
    {
        *state->money += *state->bet;
        draw_big_text(BIG_TEXT_PUSH);
        time_wait_ms(1000);
    }
}

static void draw_state(bj_state_t *state)
{
    const uint8_t player_total = get_total(&state->player_cards[0], state->player_index);
    const uint8_t dealer_total = get_total(&state->dealer_cards[0], state->dealer_index);

    draw_total(player_total, CARD_OWNER_PLAYER);
    draw_total(dealer_total, CARD_OWNER_DEALER);
    draw_cards(&state->player_cards[0], state->player_index, CARD_OWNER_PLAYER);
    draw_cards(&state->dealer_cards[0], state->dealer_index, CARD_OWNER_DEALER);
}

//draw en mode piocher pas dessiner
static inline card_t draw(bj_state_t *state)
{
    return state->deck[state->draw_index++];
}

static uint8_t get_total(card_t *cards, uint8_t count)
{
    uint8_t total = 0, aces = 0;

    for (uint8_t i = 0; i < count; i++)
    {
        uint8_t val = card_get_value(cards[i]);

        if (val >= 10)
        {
            //10, J, Q, K
            total += 10;
        }
        else if (val == 1)
        {
            total += 11;
            aces++;
        }
        else {
            //cartes [2-9]
            total += val;
        }
    }

    while (total > 21 && aces > 0)
    {
        total -= 10;
        aces--;
    }

    return total;
}
