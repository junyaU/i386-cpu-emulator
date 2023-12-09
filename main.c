#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MEMORY_SIZE (1024 * 1024)

enum Register { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTERS_COUNT };
char *registers_names[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };

typedef struct {
    uint32_t registers[REGISTERS_COUNT];
    uint32_t eflags;
    uint8_t* memory;
    // PC
    uint32_t eip;
} Emulator;

static Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp)
{
    Emulator* emu = malloc(sizeof(Emulator));
    emu->memory = malloc(size);

    memset(emu->registers, 0, sizeof(emu->registers));

    emu->eip = eip;
    emu->registers[ESP] = esp;

    return emu;
}

int main(int argc, char* argv[]) {
    FILE* binary;
    Emulator* emu;

    if (argc != 2) {
        printf("usage: px86 filename\n");
        return 1;
    }

    emu = create_emu(MEMORY_SIZE, 0x0000, 0x7c00);

    binary = fopen(argv[1], "rb");
    if (binary == NULL) {
        printf("%s cannot open file\n", argv[1]);
    }

    return 0;
}
