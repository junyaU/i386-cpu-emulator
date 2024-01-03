#include "emulator_func.h"

uint32_t get_code8(Emulator* emu, int index)
{
    return emu->memory[emu->eip + index];
}

int32_t get_sign_code8(Emulator* emu, int index)
{
    return (int8_t)emu->memory[emu->eip + index];
}

uint32_t get_code32(Emulator* emu, int index)
{
    uint32_t ret = 0;

    int i;
    for (i = 0; i < 4; i++) {
        ret |= get_code8(emu, index + i) << (i * 8);
    }

    return ret;
}

int32_t get_sign_code32(Emulator* emu, int index)
{
    return (int32_t) get_code32(emu, index);
}

uint8_t get_register8(Emulator* emu, int index)
{
    if (index < 4) {
        return emu->registers[index] & 0xFF;
    } else {
        return (emu->registers[index - 4] >> 8) & 0xFF;
    }
}

uint32_t get_register32(Emulator* emu, int index)
{
    return emu->registers[index];
}

void set_register8(Emulator* emu, int index, uint8_t value)
{
    if (index < 4) {
        uint32_t r = get_register32(emu, index) & 0xffffff00;
        emu->registers[index] = r | (uint32_t)value;
    } else {
        uint32_t r = emu->registers[index -4] & 0xffff00ff;
        emu->registers[index - 4] = r | ((int32_t)value << 8);
    }
}

void set_register32(Emulator* emu, int index, uint32_t value)
{
    emu->registers[index] = value;
}

void set_memory8(Emulator* emu, uint32_t addr, uint32_t value)
{
    emu->memory[addr] = value & 0xFF;
}

void set_memory32(Emulator* emu, uint32_t addr, uint32_t value)
{
    int i;
    for (i = 0; i < 4; i++) {
        set_memory8(emu, addr + i, value >> (i * 8));
    }
}

uint32_t get_memory8(Emulator* emu, uint32_t addr)
{
    return emu->memory[addr];
}

uint32_t get_memory32(Emulator* emu, uint32_t addr)
{
    int i;
    uint32_t ret = 0;

    for (i = 0; i < 4; i++) {
        ret |= get_memory8(emu, addr + i) << (i * 8);
    }

    return ret;
}

void push32(Emulator* emu, uint32_t value)
{
    int32_t addr = get_register32(emu, ESP) - 4;
    set_register32(emu, ESP, addr);
    set_memory32(emu, addr, value);
}

uint32_t pop32(Emulator* emu)
{
    uint32_t addr = get_register32(emu, ESP);
    set_register32(emu, ESP, addr + 4);
    return get_memory32(emu, addr);
}
