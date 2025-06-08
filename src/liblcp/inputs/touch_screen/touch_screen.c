#include "touch_screen.h"
#include "../../i2c/i2c.h"
#include "../../config_LPC1769.h"
#include "../../rendering/screen/screen.h"

static const uint8_t touch_screen_slave_addr = 0x38 << 1;

bool touch_screen_init()
{
    init_i2c(0, 100000);//1kHz

    PINSEL4 &= ~(3 << 22);
    FIO2DIR &= ~(1 << 11);

    return true;
}

uint8_t touch_screen_get_position(uint16_t *x_f1, uint16_t *y_f1, uint16_t *x_f2, uint16_t *y_f2)
{
    uint8_t data[15] = {0};
    I2C_master_write(touch_screen_slave_addr, &(uint8_t){0x0}, 1);
    I2C_master_read(touch_screen_slave_addr, data, sizeof(data)/sizeof(data[0]));

    const uint8_t finger_count = data[0x2];
    uint8_t x = 0, y = 0;

    if (finger_count > 0)
    {
        x = ((data[0x3] << 8) | data[0x4]);
        y = ((data[0x5] << 8) | data[0x6]);
        *x_f1 = screen_width  - x;
        *y_f1 = screen_height - y;
    }

    if (finger_count > 1)
    {
        x = ((data[0x9] << 8) | data[0xa]);
        y = ((data[0xb] << 8) | data[0xc]);
        *x_f2 = screen_width  - x;
        *y_f2 = screen_height - y;
    }

    return finger_count;
}
