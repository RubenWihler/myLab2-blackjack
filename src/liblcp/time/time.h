#pragma once 

#include <stdint.h>

void time_init_system_clock(uint32_t freq);
void time_wait_ms(uint16_t ms);

extern volatile uint32_t time_ms;

