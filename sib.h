#ifndef SIB_H_
#define SIB_H_

#include <stdint.h>

#include "emulator.h"

typedef struct {
    uint8_t scale;
    uint8_t index;
    uint8_t base;
} SIB;

void parse_sib(Emulator* emu, SIB* sib);

#endif