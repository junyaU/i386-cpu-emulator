#include "io.h"

#include <stdio.h>

uint8_t  io_in8(uint16_t addr)
{
    switch (addr) {
        case 0x03f8:
            return getchar();
            break;
        default:
            return 0;
    }
}

void io_out8(uint16_t addr, uint8_t value)
{
    switch (addr) {
        case 0x03f8:
            putchar(value);
            break;
    }
}