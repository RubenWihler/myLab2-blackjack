#include "liblcp/config_LPC1769.h"
#include "liblcp/rendering/ui/elements/trigger_zone/trigger_zone.h"
#include "liblcp/rendering/screen/screen.h"
#include "liblcp/utils/utils.h"
#include "liblcp/inputs/input_manager.h"
#include "liblcp/time/time.h"
#include "liblcp/ledrgb/ledrgb.h"
#include "game/game.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

static void init(void);

void on_touch_screen(uint8_t finger_count, uint16_t x_f1, uint16_t y_f1, uint16_t x_f2, uint16_t y_f2)
{
    //eviter les warnings
    (void)finger_count;
    (void)x_f2;
    (void)y_f2;

    //tester si le joueur a cliquee sur un bouton
    trigger_zone_test( x_f1, y_f1);
}

int main(void)
{
    init();
    game_t game;
    game_init(&game);
    game_start(&game);

    //ne s'execute jamais car le jeu tourne a l'infini
    game_stop(&game);
    game_destroy(&game);
    input_manager_destroy();
    return 0;
}

static void init(void)
{
    SystemInit();
    srand(time(NULL));

    //leds (meme si pas utilisee)
	FIO2MASK = 0;
    FIO2DIR = 0xff;

    //joystick (meme si pas utilisee)
    FIO1DIR = ~(0x1f << 19);

    //inputs
    input_manager_init();
    input_manager_add_listener(TOUCH_SCREEN, &on_touch_screen);
    // input_manager_add_listener(BUTTON_A, &on_btn_a);
    // input_manager_add_listener(BUTTON_B, &on_btn_b);

    //clock
    time_init_system_clock(SYSCLOCK);

    init_rgb();
    set_rgb_leds(0x00, 0x00, 0x00);

    screen_init();

    trigger_zone_init();
}

