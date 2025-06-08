
#include "log.h"
#include <stddef.h>

#include "../time/time.h"
#include "../ledrgb/ledrgb.h"
#include "../rendering/ui/elements/textbox/textbox.h"

typedef struct {
    char* msg;
    const char* func;
    const char* file;
    int line;
} debug_error_t;

static void create_error_message(char* msg, const char* func, const char* file, const int line, char* buffer);

void log_error(char* msg, const char* func, const char* file, const int line, bool fatal)
{
    const debug_error_t error = {
        .msg = msg,
        .func = func,
        .file = file,
        .line = line
    };

    char error_msg[512];
    create_error_message(error.msg, error.func, error.file, error.line, error_msg);

    tbox_draw((tbox_t){
        .rect = {
            20,
            20, 
            240-40,
            320-40,
        },
        .color_bg = 0xffff,
        .color_fg = 0xf945,
        .color_border = 0xf945,
        .border = 2,
        .char_space = -4,
        .line_space = 0,
        .margin = 10,
        .font = font_large,
        .text = "Error occured !"
    });

    tbox_draw((tbox_t){
        .rect = {
            20,
            50, 
            240-40,
            320-70,
        },
        .color_bg = 0xffff,
        .color_fg = 0x0000,
        .color_border = 0xf945,
        .border = 0,
        .char_space = -2,
        .line_space = 0,
        .margin = 10,
        .font = font_small,
        .text = error_msg
    });

    set_rgb_leds(0xff, 0x00, 0x00);

    if (fatal)
    {
        /*les info de debug sont ici ->*/(void)error;
        __asm volatile ("BKPT #0");
        __asm volatile ("NOP");
    }
    else 
    {
        time_wait_ms(2000);
    }

    set_rgb_leds(0x00, 0x00, 0x00);

    //genere une interruption hardfault
    if(fatal) (*(volatile int*)0 = 0);
}

static void create_error_message(char* msg, const char* func, const char* file, const int line, char* buffer) {
    if (!msg || !func || !file || !buffer) {
        return; // Ensure all inputs are valid
    }

    // Copy the error message
    char* ptr = buffer;

    // Add separator and function name
    const char* separator = "Function: ";
    while (*separator) {
        *ptr++ = *separator++;
    }
    while (*func) {
        *ptr++ = *func++;
    }

    // Add separator and file name
    separator = "\nFile: ";
    while (*separator) {
        *ptr++ = *separator++;
    }
    while (*file) {
        *ptr++ = *file++;
    }

    // Add separator and line number
    separator = "\nLine: ";
    while (*separator) {
        *ptr++ = *separator++;
    }

    // Convert line number to string
    char line_str[12]; // Enough to hold any 32-bit integer
    char* line_ptr = line_str + sizeof(line_str) - 1;
    *line_ptr = '\0';
    int temp_line = line;
    do {
        *--line_ptr = '0' + (temp_line % 10);
        temp_line /= 10;
    } while (temp_line > 0);

    while (*line_ptr) {
        *ptr++ = *line_ptr++;
    }
    
    // Add separator and line number
    separator = "\n\n";
    while (*separator) {
        *ptr++ = *separator++;
    }
    while (*msg) {
        *ptr++ = *msg++;
    }

    // Null-terminate the buffer
    *ptr = '\0';
}

