#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    JOYSTICK_NONE = 0,
    JOYSTICK_PRESS = 1,
    JOYSTICK_NORTH = 2,
    JOYSTICK_EAST = 4,
    JOYSTICK_SUD = 8,
    JOYSTICK_WEST = 16
} joystick_state_e;

void gpio_led_set(uint8_t led, bool state);
void gpio_led_set_all(uint8_t value);

/// @brief Retourn l'etat du joystick
/// -  0 : aucuns boutons n'est appuyé
/// -  1 : le joystick est pressé
/// -  2 : (N) Joystick vers le haut
/// -  4 : (E) Joystick vers la droite
/// -  8 : (S) Joystick vers le bas
/// - 16 : (W) Joystick vers la gauche
joystick_state_e gpio_joystick_get_state(void);
bool gpio_joystick_test_state(joystick_state_e state);

