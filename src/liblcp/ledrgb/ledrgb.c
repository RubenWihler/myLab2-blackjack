#include "ledrgb.h"
#include "../time/time.h"
#include <string.h>

static void encode(const bool val, bool *encoded);

void set_rgb_leds(uint8_t r, uint8_t g, uint8_t b)
{
    const uint8_t rgb[3] = {g, r, b};
    bool color[97*2];
    color[0] = 1;

    bool *ptr = &color[1];

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            encode((rgb[i] >> j) & 1, ptr);
            ptr += 4;
        }
    }

    memcpy(color+97, color, 97 * sizeof(bool));

    set_rgb_leds_color(color);
    time_wait_ms(10);
}

static void encode(const bool val, bool *encoded)
{
    if (val)
    {
        encoded[0] = false;
        encoded[1] = false;
        encoded[2] = true;
        encoded[3] = true;
    }
    else 
    {
        encoded[0] = false;
        encoded[1] = true;
        encoded[2] = true;
        encoded[3] = true;
    }
}
