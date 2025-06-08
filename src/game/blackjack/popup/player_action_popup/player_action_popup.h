#pragma once

typedef enum {
    PLAYER_ACTION_HIT,
    PLAYER_ACTION_STAND
} player_action_e;

void player_action_popup_show(player_action_e *action);

