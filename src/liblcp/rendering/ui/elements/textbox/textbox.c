#include "textbox.h"

#include "../../../screen/screen.h"
#include "../../../drawing/draw_utils.h"

#include <stdint.h>
#include <string.h>

typedef unsigned char uchar;

static void draw_char(const rect_t rect, const font_t *char_data, const uint16_t color_fg, const uint16_t color_bg);

void tbox_draw(const tbox_t tbox)
{
    //border
    if (tbox.border > 0)
    {
        rect_t border_rect = tbox.rect;
        border_rect.x -= tbox.border;
        border_rect.y -= tbox.border;
        border_rect.w += tbox.border * 2;
        border_rect.h += tbox.border * 2;
        draw_rect(border_rect, tbox.color_border);
    }

    //background
    draw_rect(tbox.rect, tbox.color_bg);

    const uint16_t text_len = strlen(tbox.text);
    const uint16_t char_w = tbox.font[0], 
                char_h = tbox.font[1],
                offset = tbox.font[2], 
                char_n = tbox.font[3];

    //nibble count: le nombre d'elements(valeur de tbox.font) qui composent un caractere
    const uchar nibble_size_bits = sizeof(*tbox.font) * 8;
    const uchar nibble_count = char_w / nibble_size_bits;

    //position du charactere
    uint16_t x = tbox.rect.x + tbox.margin, 
             y = tbox.rect.y + tbox.margin;

    for (int i = 0; i < text_len; i++)
    {
        //on verifie que le caractere est dans la plage de caracteres
        if((tbox.text[i] > offset) && (tbox.text[i] < (offset + char_n)))
        {
            //calcul de la position du caractere dans le tableau de caracteres
            //+4 car les 4 premiers elements de tbox.font sont des meta-donnees
            const uint16_t index = ((tbox.text[i] - offset) * char_h * nibble_count) + 4;
            draw_char((rect_t){x, y, char_w, char_h},
                    tbox.font+index,
                    tbox.color_fg,
                    tbox.color_bg
            );
        }

        //charactere speciaux
        if(tbox.text[i] == '\n') x += tbox.rect.w; //force le retour a la ligne

        //text wrap:
        // si le caractere suivant depasse la largeur de la boite de texte, on passe a la ligne suivante
        // on pourrait ameliorer en sautant a la ligne si le mot suivant depasse la largeur de la boite de texte
        x += char_w + tbox.char_space;
        if(x > ((tbox.rect.x + tbox.rect.w) - tbox.margin))
        {
            x = tbox.rect.x + tbox.margin;
            y += char_h + tbox.line_space;
        }
    }
}

static void draw_char(const rect_t rect, const font_t *char_data, const uint16_t color_fg, const uint16_t color_bg)
{
    const uint16_t row_size_bit = sizeof(*char_data) * 8;

    screen_set_vzone(rect);

    screen_write_command(0x2c);
    screen_write_start(SPI_DATA);

    font_t *ptr = char_data;
    const font_t *end_ptr = char_data + (rect.h * (rect.w / row_size_bit));

    while(ptr < end_ptr)
    {
        for (int i = row_size_bit-1; i >= 0; i--)
        {
            uint16_t color = ((*ptr >> i) & 1) ? 
                color_fg : color_bg;

            screen_write_16b(color);
        }

        ptr++;
    }
}

