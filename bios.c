#include "bios.h"

#include <stdio.h>
#include <stdint.h>
#include "emulator_func.h"
#include "io.h"

static int bios_to_terminal[8] = { 30 /* black */, 34 /* blue */, 32 /* green */, 36 /* cyan */, 31 /* red */, 35 /* magenta */, 33 /* brown */, 37 /* white */ };

static void put_string(const char* s, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++) {
        io_out8(0x03f8, s[i]);
    }
}

static void bios_video_teletype(Emulator* emu)
{
    uint8_t color = get_register8(emu, BL) & 0x0f;
    uint8_t ch = get_register8(emu, AL);

    char buf[32];
    int terminal_color = bios_to_terminal[color & 0x07];
    int bright = (color & 0x08) ? 1 : 0;
    int len = sprintf(buf, "\x1b[%d;%dm%c\x1b[0m", bright, terminal_color, ch);
    put_string(buf, len);
}

void bios_video(Emulator* emu)
{
    uint8_t bios_func = get_register8(emu, AH);
    switch (bios_func) {
        case 0x0e:
            bios_video_teletype(emu);
            break;
        default:
            printf("not implemented BIOS video function: 0x%02x\n", bios_func);
    }
}

