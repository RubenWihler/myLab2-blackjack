#pragma once

#include <stdint.h>
#include <stdbool.h>

void lcp_init_gpio(const int dir[5]);
void lcp_init_interruption(const int enable[2]);
void lcp_init_timer(void);
void lcp_init_screen(void);

/// @brief Allume ou eteint une led
/// @param led est le numero de la led (0 - 7)
/// @param state true: allume, false eteint
void lcp_gpio_set_led(uint8_t led, bool state);

/// @brief Allume ou eteint toutes les leds
/// @param leds est un entier de 8 bits ou chaque bit represente une led
/// @details Le bit 0 represente la led 0, le bit 1 la led 1, etc.
void lcp_gpio_set_leds(uint8_t leds);

/// @brief Retourne l'etat du joystick
/// @return un entier de 8 bits :
///     0 : si pas appuye ni deplace
///     1 : si le bouton est appuye
///     2 : si le joystick est deplace vers le nord
///     4 : si le joystick est deplace vers l'ouest
///     8 : si le joystick est deplace vers le sud
///     16 : si le joystick est deplace vers l'est
///
/// @note Il n'est mecanniquement pas possible d'avoir 2 posisitons en meme temps (diagonale)
uint8_t lcp_gpio_get_joystick(void);

bool lcp_gpio_test_joystick_state(uint8_t pos);

void lcp_delay_ms(int ms);

void lcp_spi_send(uint8_t data);
void lcp_spi_write_command(uint8_t command);
void lcp_spi_write_data(uint8_t data);
void lcp_spi_write_color(uint16_t color);


