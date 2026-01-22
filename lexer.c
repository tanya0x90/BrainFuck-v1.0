#include <stdbool.h>
#include "lexer.h"

static bool checkValid(char byte){
    if(byte == '+' || byte == '-' || byte == '.' || byte == ','
    || byte == '<' || byte == '>' || byte == '[' || byte == ']' || byte == 0){
        return true;
    }
    return false;
}

Token* lex(char* sourceCode,int size){
    int line=1;
    int col=1;
    int currentToken=0;
    //Reservar memoria
    Token* tokens = (Token*)malloc(size*sizeof(Token)+2);
    
    for(int position = 0; position < size+1;position++){
        if(checkValid(sourceCode[position])){
            switch(sourceCode[position]){
                case '\0':
                    tokens[currentToken].type = TOKEN_EOF;
                break;
                case '+':
                    tokens[currentToken].type = TOKEN_PLUS;
                    break;
                case '-':
                    tokens[currentToken].type = TOKEN_MINUS;
                    break;
                case ',':
                    tokens[currentToken].type = TOKEN_COMMA;
                    break;
                case '.':
                    tokens[currentToken].type = TOKEN_DOT;
                    break;
                case '<':
                    tokens[currentToken].type = TOKEN_LEFT;
                    break;
                case '>':
                    tokens[currentToken].type = TOKEN_RIGHT;
                    break;
                case '[':
                    tokens[currentToken].type = TOKEN_LBRACE;
                    break;
                case ']':
                    tokens[currentToken].type = TOKEN_RBRACE;
                    break;
                default:
                break;
            }
            tokens[currentToken].line=line;
            tokens[currentToken].position=col;
            tokens[currentToken].offset=currentToken;
            tokens[currentToken].jumpTo=0;
            currentToken++;
            col++;  
        }
        if(sourceCode[position]=='\n'){
            line++;
            col = 1;
        }
    }
    return tokens;
}

void printToken(Token token){
    switch(token.type){
        case TOKEN_PLUS:
            printf("#%04d Token: '+'(increment) Line:%d Position: %d\n" ,token.offset,token.line,token.position);
        break;
        case TOKEN_MINUS:
            printf("%04d Token '-' (decrement)  Line: %d Position: %d\n",token.offset,token.line,token.position);
        break;
        case TOKEN_COMMA:
            printf("%04d Token ',' (scan)       Line: %d Position: %d\n",token.offset,token.line,token.position);
        break;
        case TOKEN_DOT:
            printf("%04d Token '.' (print)      Line: %d Position: %d\n",token.offset,token.line,token.position);
        break;
        case TOKEN_LEFT:
            printf("%04d Token '<' (left)       Line: %d Position: %d\n",token.offset,token.line,token.position);
        break;
        case TOKEN_RIGHT:
            printf("%04d Token '>' (right)      Line: %d Position: %d\n",token.offset,token.line,token.position);
        break;
        case TOKEN_LBRACE:
            printf("%04d Token '[' (loop start) Line: %d Position: %d\n",token.offset,token.line,token.position);
        break;
        case TOKEN_RBRACE:
            printf("%04d Token ']' (loop end)   Line: %d Position: %d\n",token.offset,token.line,token.position);
        break;
        case TOKEN_EOF:
            printf("%04d Token 'EOF'            Line: % d Position:%d\n",token.offset,token.line,token.position);
        break;
        default:
        break;
    }
}