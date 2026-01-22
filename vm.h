#ifndef BF_VM_H
#define BF_VM_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "chunk.h"

typedef struct{
    unsigned int ip;
    unsigned int tp;
    unsigned int size;
    unsigned char* instructions;
    unsigned char* tape;
    bool debugged;
}VM;

void startVm(unsigned char* instructions, unsigned int size, bool debug);
int runVm();

#endif