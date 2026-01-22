#ifndef BF_PARSER_H
#define BF_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "chunk.h"

typedef struct{
    Token* stack;
    unsigned int sp;
}LoopStack;

Chunk* parse(Token* toks,int mode);
void printParsedToken(Token token);

#endif