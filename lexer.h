#ifndef BF_LEXER_H
#define BF_LEXER_H

#include <stdlib.h>
#include <stdio.h>
//Header en la carpeta
#include "token.h"

Token* lex(char* sourceCode, int size);
void printToken(Token token);

#endif