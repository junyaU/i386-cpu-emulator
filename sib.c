#include "sib.h"
#include "emulator_func.h"

void parse_sib(Emulator* emu, SIB* sib)
{
    uint8_t sib_byte = get_code8(emu, 0);
    sib->scale = (sib_byte & 0xC0) >> 6;
    sib->index = (sib_byte & 0x38) >> 3;
    sib->base = sib_byte & 0x07;

    emu->eip += 1;
}