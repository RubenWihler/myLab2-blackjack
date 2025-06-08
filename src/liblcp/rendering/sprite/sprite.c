#include "sprite.h"
#include "../screen/screen.h"

void sprite_render(const sprite_t sprite, const uint16_t pos_x, const uint16_t pos_y)
{
    rect_t rect = {
        .x = pos_x,
        .y = pos_y,
        .w = sprite.width,
        .h = sprite.height
    };

    screen_set_vzone(rect);
    screen_write_command(0x2c);
    screen_write_start(SPI_DATA);

    uint8_t *ptr = (uint8_t*)sprite.data;
    uint8_t *end_ptr = (uint8_t*)sprite.data + ((rect.h * rect.w) * 2);

    while (ptr < end_ptr)
    {
        uint16_t pxcolor = (*ptr << 8) | *(ptr+1);
        screen_write_16b(pxcolor);
        ptr += 2;
    }
}
