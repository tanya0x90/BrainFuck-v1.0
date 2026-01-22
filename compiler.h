#ifndef BF_COMPILER_H
#define BF_COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chunk.h"

void emitAssembly(FILE* file, unsigned char* instructions);
char* generateSymbol(unsigned short offset, char* symbol);
int compile(unsigned char* instructions);

#endif