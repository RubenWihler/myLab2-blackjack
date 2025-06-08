#include "screen.h"
#include "../../config_LPC1769.h"
#include "../../time/time.h"
#include "../../spi/spi.h"

#include <stdint.h>

const uint16_t screen_width = 240;
const uint16_t screen_height = 320;

static void ILI9341_Initial(void);

void screen_init(void)
{
    //Chip Select Lcp => nCS_LCD => P0.16
    
    /* Section setup */
    FIO0MASK &= ~(1 << 16);
	FIO1MASK &= ~(1 << 30);
	FIO1MASK &= ~(1 << 18);

	//Chip select (selection de l'ecran)
	FIO0DIR |= (1 << 16);   // nCS_LCD -> out
	// Backligth control (activation ou non)
	FIO1DIR |= (1 << 18);   // BL_ctrl -> out
	// Data/Command control 0 = commande, 1 = data
	FIO1DIR |= (1 << 30);   // LCD_DC -> out

	// Backligth activation
	FIO1SET = (1 << 18);

	// FIO0PIN |= (1 << 16);

	/* Section SPI */
    PINSEL0 |= (0b11 << 30);  // P0.15 -> SSP0_CLK
    PINSEL1 |= (0b11 << 2);   // P0.17 => SSP0_MISO
    PINSEL1 |= (0b11 << 4);   // P0.18 -> SSP0_MOSI

    //On est en MASTER
    S0SPCR |= (1 << 5);
    // frequence du SPI (ici PCLK/8)
    S0SPCCR = 8;

    ILI9341_Initial();
    time_wait_ms(100);

    //scrolling a 0
    screen_write_command(0x33);
    screen_write_16b(0);
    screen_write_16b(0x140);
    screen_write_16b(0);

    screen_write_command(0x37);
	screen_write_16b(0);
}

void screen_write_start(spi_communication_mode_e mode)
{
    FIO0CLR = (1 << 16);//Mettre le bit nCS_LCD à 0 pour démarrer la communication

    if(mode == SPI_COMMAND)
        FIO1CLR = (1 << 30);//Mettre le bit LCD_DC à 0 car on envoie une commande
    else
        FIO1SET = (1 << 30);//Mettre le bit LCD_DC à 1 car on envoie des données
}

void screen_write(uint8_t data_cmd)
{
    spi_send(data_cmd);
}

void screen_write_end()
{
    FIO0SET = (1 << 16);//Mettre le bit nCS_LCD à 1 pour terminer la communication
}

void screen_write_16b(uint16_t data)
{
    //doit etre en mode data
    screen_write(data >> 8);  //MSB - Most Significant Byte
    screen_write(data & 0xFF);//LSB - Least Significant Byte
}

void screen_write_command(uint8_t command)
{
    screen_write_start(SPI_COMMAND);
    screen_write(command);
    screen_write_end();
}

void screen_write_data(uint8_t data)
{
    screen_write_start(SPI_DATA);
    screen_write(data);
    screen_write_end();
}

void screen_set_vzone(rect_t rect)
{
    screen_write_command(0x2A); //Column address set
    screen_write_start(SPI_DATA);
    screen_write_16b(rect.x);
    screen_write_16b(rect.x + rect.w - 1);

    screen_write_command(0x2B); //Row address set
    screen_write_start(SPI_DATA);
    screen_write_16b(rect.y);
    screen_write_16b(rect.y + rect.h - 1);
    screen_write_end();
}

static void ILI9341_Initial(void)
{
	screen_write_command(0x01); //software reset
    time_wait_ms(5);

	screen_write_command(0x11);
    time_wait_ms(120);

 	screen_write_command(0xCF);
	screen_write_data(0x00);
	screen_write_data(0x83);
	screen_write_data(0X30);

 	screen_write_command(0xED);
	screen_write_data(0x64);
	screen_write_data(0x03);
	screen_write_data(0X12);
	screen_write_data(0X81);

 	screen_write_command(0xE8);
	screen_write_data(0x85);
	screen_write_data(0x01);
	screen_write_data(0x79);

 	screen_write_command(0xCB);
	screen_write_data(0x39);
	screen_write_data(0x2C);
	screen_write_data(0x00);
	screen_write_data(0x34);
	screen_write_data(0x02);

 	screen_write_command(0xF7);
	screen_write_data(0x20);

 	screen_write_command(0xEA);
	screen_write_data(0x00);
	screen_write_data(0x00);

 	screen_write_command(0xC1); //Power control
	screen_write_data(0x11);    //SAP[2:0];BT[3:0]

 	screen_write_command(0xC5); //VCM control 1
	screen_write_data(0x34);
	screen_write_data(0x3D);

 	screen_write_command(0xC7); //VCM control 2
	screen_write_data(0xC0);

 	screen_write_command(0x36); //Memory Access Control
	screen_write_data(0x08);

 	screen_write_command(0x3A); //Pixel format
	screen_write_data(0x55);    //16bit

 	screen_write_command(0xB1); // Frame rate
	screen_write_data(0x00);
	screen_write_data(0x1D);    //65Hz

 	screen_write_command(0xB6); // Display Function Control
	screen_write_data(0x0A);
	screen_write_data(0xA2);
	screen_write_data(0x27);
	screen_write_data(0x00);

	screen_write_command(0xb7); //Entry mode
	screen_write_data(0x07);


 	screen_write_command(0xF2); // 3Gamma Function Disable
	screen_write_data(0x08);

 	screen_write_command(0x26); //Gamma curve selected
	screen_write_data(0x01);


	screen_write_command(0xE0); //positive gamma correction
	screen_write_data(0x1f);
	screen_write_data(0x1a);
	screen_write_data(0x18);
	screen_write_data(0x0a);
	screen_write_data(0x0f);
	screen_write_data(0x06);
	screen_write_data(0x45);
	screen_write_data(0x87);
	screen_write_data(0x32);
	screen_write_data(0x0a);
	screen_write_data(0x07);
	screen_write_data(0x02);
	screen_write_data(0x07);
	screen_write_data(0x05);
	screen_write_data(0x00);

	screen_write_command(0xE1); //negamma correction
	screen_write_data(0x00);
	screen_write_data(0x25);
	screen_write_data(0x27);
	screen_write_data(0x05);
	screen_write_data(0x10);
	screen_write_data(0x09);
	screen_write_data(0x3a);
	screen_write_data(0x78);
	screen_write_data(0x4d);
	screen_write_data(0x05);
	screen_write_data(0x18);
	screen_write_data(0x0d);
	screen_write_data(0x38);
	screen_write_data(0x3a);
	screen_write_data(0x1f);

 	screen_write_command(0x11); //Exit Sleep
 	time_wait_ms(120);
 	screen_write_command(0x29); //Display on
 	time_wait_ms(50);
}

