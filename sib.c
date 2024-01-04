#include "sib.h"
#include "emulator_func.h"
#include "emulator.h"

void parse_sib(Emulator* emu, SIB* sib)
{
    uint8_t sib_byte = get_code8(emu, 0);
    sib->scale = (sib_byte & 0xC0) >> 6;
    sib->index = (sib_byte & 0x38) >> 3;
    sib->base = sib_byte & 0x07;

    emu->eip += 1;
}

uint32_t calc_sib_addr(Emulator* emu, SIB* sib) {
    uint32_t base = get_register32(emu, sib->base);

    if (sib->index == ESP) {
        return base;
    }

    uint32_t index = get_register32(emu, sib->index);
    uint32_t scale_factor = 1 << sib->scale;
    base += index * scale_factor;

    return base;
}