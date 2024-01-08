#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "modrm.h"
#include "emulator_func.h"
#include "sib.h"

void parse_modrm(Emulator* emu, ModRM* modrm)
{
    assert(emu != NULL && modrm != NULL);

    memset(modrm, 0, sizeof(ModRM));

    uint8_t code = get_code8(emu, 0);
    modrm->mod = ((code & 0xC0) >> 6);
    modrm->opecode = ((code & 0x38) >> 3);
    modrm->rm = code & 0x07;

    emu->eip += 1;

    if (modrm->mod != ADDRESSING_MODE_REGISTER && modrm->rm == 4) {
        SIB sib;
        parse_sib(emu, &sib);
        modrm->sib = sib;
    }

    if ((modrm->mod == ADDRESSING_MODE_MEMORY && modrm->rm == 5) || modrm->mod == ADDRESSING_MODE_DISP32) {
        modrm->disp32 = get_sign_code32(emu, 0);
        emu->eip += 4;
    } else if (modrm->mod == ADDRESSING_MODE_DISP8) {
        modrm->disp8 = get_sign_code8(emu, 0);
        emu->eip += 1;
    }
}

uint32_t calc_memory_address(Emulator* emu, ModRM* modrm)
{
    switch  (modrm->mod) {
        case ADDRESSING_MODE_MEMORY:
            if (modrm->rm == 4) {
                uint32_t sib_addr = calc_sib_addr(emu, &modrm->sib);
                return sib_addr;
            } else if (modrm->rm == 5) {
                return modrm->disp32;
            }

            return get_register32(emu, modrm->rm);

        case ADDRESSING_MODE_DISP8:
            if (modrm->rm == 4) {
                uint32_t sib_addr = calc_sib_addr(emu, &modrm->sib);
                return sib_addr + modrm->disp8;
            }

            return get_register32(emu, modrm->rm) + modrm->disp8;

        case ADDRESSING_MODE_DISP32:
            if (modrm->rm == 4) {
                uint32_t sib_addr = calc_sib_addr(emu, &modrm->sib);
                return sib_addr + modrm->disp32;
            }

            return get_register32(emu, modrm->rm) + modrm->disp32;

        default:
            printf("not implemented ModRM mod = %d\n", modrm->mod);
            exit(0);
    }
}

void set_rm8(Emulator* emu, ModRM* modrm, uint8_t value)
{
    if (modrm->mod == ADDRESSING_MODE_REGISTER) {
        set_register8(emu, modrm->rm, value);
        return;
    }

    uint32_t address = calc_memory_address(emu, modrm);
    set_memory8(emu, address, value);
}

void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value)
{
    if (modrm->mod == ADDRESSING_MODE_REGISTER) {
        set_register32(emu, modrm->rm, value);
        return;
    }


    uint32_t address = calc_memory_address(emu, modrm);


    set_memory32(emu, address, value);
}

uint8_t get_rm8(Emulator* emu, ModRM*  modrm)
{
    if (modrm->mod == ADDRESSING_MODE_REGISTER) {
        return get_register8(emu, modrm->rm);
    }

    uint32_t address = calc_memory_address(emu, modrm);
    return get_memory8(emu, address);
}

uint32_t get_rm32(Emulator* emu, ModRM* modrm)
{
    if (modrm->mod == ADDRESSING_MODE_REGISTER) {
        return get_register32(emu, modrm->rm);
    }

    uint32_t address = calc_memory_address(emu, modrm);
    return get_memory32(emu, address);
}

void set_r8(Emulator* emu, ModRM* modrm, uint8_t value)
{
    set_register8(emu, modrm->reg_index, value);
}

void set_r32(Emulator* emu, ModRM* modrm, uint32_t value)
{
    set_register32(emu, modrm->reg_index, value);
}

uint8_t get_r8(Emulator* emu, ModRM* modrm)
{
    return get_register8(emu, modrm->reg_index);
}

uint32_t get_r32(Emulator* emu, ModRM* modrm)
{
    return get_register32(emu, modrm->reg_index);
}
