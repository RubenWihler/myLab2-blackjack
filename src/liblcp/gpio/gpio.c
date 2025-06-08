#include "gpio.h"
#include "../config_LPC1769.h"

#include <stddef.h>
#include <stdbool.h>

void gpio_led_set(uint8_t led, bool state)
{
    if(led > 7) return;

    FIO2MASK = ~(1 << led);
    FIO2PIN = (state) ? 0xff : 0xff;
}

void gpio_led_set_all(uint8_t value)
{
    FIO2MASK = ~(0xff);
    FIO2PIN = value;
}

joystick_state_e gpio_joystick_get_state(void)
{
    FIO1MASK = ~(0x1f << 19);
    return ((FIO1PIN >> 19) ^ 0x1f);
}

bool gpio_joystick_test_state(joystick_state_e state)
{
    return gpio_joystick_get_state() == state;
}

