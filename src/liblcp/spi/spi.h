#pragma once

#include <stdint.h>

typedef enum {
    SPI_COMMAND,
    SPI_DATA,
} spi_communication_mode_e;

void spi_send(uint8_t data);

