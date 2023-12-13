#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "emulator.h"

void init_instructions(void);

typedef void instruction_func_t(Emulator*);

// index is the value of the opcode
extern instruction_func_t* instructions[256];

#endif