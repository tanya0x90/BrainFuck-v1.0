#ifndef BF_DEBUG_H
#define BF_DEBUG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "chunk.h"
#include "vm.h"

void debugger(VM* vm, unsigned char* tape);
void disassembleVM(VM* vm,bool fillTable);
void disassembleInstruction(unsigned char opcode);
void printTape(VM* vm);

//void disassembleChunk(Chunk chunk);

#endif