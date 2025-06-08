#pragma once

#include "../../spi/spi.h"
#include "../utils/rect.h"

extern const uint16_t screen_width;
extern const uint16_t screen_height;

void screen_init(void);

void screen_write_start(spi_communication_mode_e mode);
void screen_write(uint8_t data_cmd);
void screen_write_16b(uint16_t data);
void screen_write_end();

void screen_write_command(uint8_t command);
void screen_write_data(uint8_t data);


void screen_set_vzone(rect_t rect);
void screen_reset_vzone();
