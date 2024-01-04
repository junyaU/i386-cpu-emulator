#ifndef MODRM_H_
#define MODRM_H_

#include <stdint.h>

#include "emulator.h"
#include "sib.h"

enum AddressingMode {
    ADDRESSING_MODE_MEMORY = 0,
    ADDRESSING_MODE_DISP8 = 1,
    ADDRESSING_MODE_DISP32 = 2,
    ADDRESSING_MODE_REGISTER = 3,
};

typedef struct {
    uint8_t mod;

    union {
        uint8_t opecode;
        uint8_t reg_index;
    };

    uint8_t rm;

    SIB sib;

    union {
        int8_t disp8;
        uint32_t disp32;
    };
} ModRM;

void parse_modrm(Emulator* emu, ModRM* modrm);

uint32_t calc_memory_address(Emulator* emu, ModRM* modrm);

uint32_t get_rm32(Emulator* emu, ModRM* modrm);

void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value);

uint32_t get_r32(Emulator* emu, ModRM* modrm);

void set_r32(Emulator* emu, ModRM* modrm, uint32_t value);

#endif