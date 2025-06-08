
#include "draw_utils.h"
#include "../utils/lerp.h"
#include "../screen/screen.h"

void draw_rect(const rect_t rect, const uint16_t color)
{
    screen_set_vzone(rect);

    screen_write_command(0x2C);
    screen_write_start(SPI_DATA);

    for (int y = 0; y < rect.h; y++)
    {
        for (int x = 0; x < rect.w; x++)
        {
            screen_write_16b(color);
        }
    }

    screen_write_end();
}

void draw_gradient(const rect_t rect, const uint16_t color_start, const uint16_t color_end, const char axe)
{
    screen_set_vzone(rect);

    screen_write_command(0x2C);
    screen_write_start(SPI_DATA);

    for (int y = 0; y < rect.h; y++)
    {
        for (int x = 0; x < rect.w; x++)
        {
            float ratio = (axe == 'V') ? ((float)y / rect.h) : ((float)x / rect.w);
            uint16_t color = lerp_color(color_start, color_end, ratio);
            screen_write_16b(color);
        }
    }

    screen_write_end();
}
