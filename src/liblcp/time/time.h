#pragma once 

#include <stdint.h>

void time_init_system_clock(uint32_t freq);
void time_wait_ms(uint16_t ms);

// entier qui s'increment chaque 1ms via une interruption systick
extern volatile uint32_t time_ms;

