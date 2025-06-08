#include "spi.h"
#include "../config_LPC1769.h"

#define SPIF ((S0SPSR >> 7) & 1)

void spi_send(uint8_t data)
{
    S0SPDR = data;//Ecrire dans le registre de données
    while(SPIF == 0) __asm("NOP");
}

