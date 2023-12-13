#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "emulator.h"
#include "instructions.h"
#include "emulator_func.h"

instruction_func_t *instructions[256];

static void mov_r32_imm32(Emulator* emu)
{
    uint8_t reg = get_code8(emu, 0) - 0xB8;
    uint32_t value = get_code32(emu, 1);
    set_register32(emu, reg, value);
    emu->eip += 5;
}

static void short_jump(Emulator* emu)
{
    int8_t diff = get_sign_code8(emu, 1);
    emu->eip += (diff + 2);
}

static void near_jump(Emulator* emu)
{
    int32_t diff = get_sign_code32(emu, 1);
    emu->eip += (diff + 5);
}

void init_instructions(void)
{
    memset(instructions, 0, sizeof(instructions));

    int i;
    for (i = 0; i < 8; i++) {
        instructions[0xB8 + i] = mov_r32_imm32;
    }

    instructions[0xE9] = near_jump;
    instructions[0xEB] = short_jump;
}