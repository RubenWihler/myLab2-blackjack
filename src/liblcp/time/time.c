#include "time.h"
#include "../config_LPC1769.h"

volatile uint32_t time_ms = 0;

//interruption clock
void SysTick_Handler(void)
{
    time_ms++;
}

void time_init_system_clock(uint32_t freq)
{
    //on configure pour que la clock fasse une interruptions
    //chaque millisecondes. (freqence / 1000)

    STCTRL = 0x7;
    STRELOAD = (freq / 1000) - 1;
}


void time_wait_ms(uint16_t ms)
{
    const uint32_t target_time = time_ms + ms;
    while(time_ms < target_time);
}

