#ifndef SIB_H_
#define SIB_H_

#include <stdint.h>

#include "emulator.h"

enum ScaleFactor {
    SCALE_1 = 0,
    SCALE_2 = 1,
    SCALE_4 = 2,
    SCALE_8 = 3,
};

typedef struct {
    uint8_t scale;
    uint8_t index;
    uint8_t base;
} SIB;

void parse_sib(Emulator* emu, SIB* sib);

uint32_t calc_sib_addr(Emulator* emu, SIB* sib);

#endif