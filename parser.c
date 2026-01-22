#include <string.h>
#include "parser.h"
#include "debug.h"
#include "vm.h"
#include "compiler.h"

#define JMP_SIZE 4

enum{
    FAIL,
    RUN,
    COMPILE,
    LEX,
    DEBUG
}Mode;

Token* tokens;
unsigned int current;
unsigned int loopCount;
Chunk chunk;
LoopStack loopstack;
Token stack[255];
static unsigned short instructionOffsets[5000];
static unsigned char insts[10000];

static void initLoopStack(){
    loopstack.stack=stack;
    loopstack.sp=0;
}

static void push(){
    loopstack.sp++;
    loopstack.stack[loopstack.sp]=tokens[current];
}

static void pop(){
    if(loopstack.sp==0){
        fprintf(stderr, "Syntax Error: ']' at line %d pos. %d has no matching '['.\n",
        tokens[current].line,tokens[current].position);
        exit(1420);
    }
    tokens[loopstack.stack[loopstack.sp].offset].jumpTo=tokens[current].offset+1;
    tokens[current].jumpTo=loopstack.stack[loopstack.sp].offset+1;
    loopstack.sp--;
}

static void parseSimpleInstruction(){
    while(tokens[current].type != TOKEN_LBRACE && tokens[current].type !=TOKEN_EOF){
        switch(tokens[current].type){
            case TOKEN_PLUS:
            case TOKEN_MINUS:
            case TOKEN_COMMA:
            case TOKEN_DOT:
            case TOKEN_LEFT:
            case TOKEN_RIGHT:
                current++;
                break;
            case TOKEN_RBRACE:
                pop();
                current++;
                break;
            default:
                break;
        }
    }
}

static void parseLoop(){
    if(tokens[current].type==TOKEN_EOF)return;
    if(tokens[current].type==TOKEN_LBRACE){
        push();
        current++;
        loopCount++;
        parseLoop();
    }
    parseSimpleInstruction();
    if(tokens[current].type==TOKEN_EOF)return;
}

static void emitBytecode(){
    unsigned int chunkSize = current+(loopCount*JMP_SIZE)+1;
    unsigned int offsetSize = current*2;
    //unsigned short* instructionOffsets=(unsigned short*)malloc(current*2);
    current=0;
    chunk.instructions=insts;
    chunk.size=chunkSize;
    chunk.current=current;
    unsigned short jmpOffset=0;
    //ByteCode
    while(tokens[current].type !=TOKEN_EOF){
        switch(tokens[current].type){
            case TOKEN_PLUS:
                chunk.instructions[chunk.current]=OP_ADD;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                current++;
                break;
            case TOKEN_MINUS:
                chunk.instructions[chunk.current]=OP_SUB;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                current++;
                break;
            case TOKEN_COMMA:
                chunk.instructions[chunk.current]=OP_SCAN;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                current++;
                break;
            case TOKEN_DOT:
                chunk.instructions[chunk.current]=OP_PRINT;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                current++;
                break;
            case TOKEN_LEFT:
                chunk.instructions[chunk.current]=OP_LEFT;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                current++;
                break;
            case TOKEN_RIGHT:
                chunk.instructions[chunk.current]=OP_RIGHT;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                current++;
                break;
            case TOKEN_LBRACE:
                chunk.instructions[chunk.current]=OP_JZ;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                chunk.instructions[chunk.current]=tokens[current].jumpTo;
                chunk.current+=2;
                current++;
                break;
            case TOKEN_RBRACE:
                chunk.instructions[chunk.current]=OP_JNZ;
                instructionOffsets[current]=chunk.current;
                chunk.current++;
                jmpOffset=(unsigned short)instructionOffsets[tokens[current].jumpTo];
                memcpy((void*)chunk.instructions+chunk.current,(void*)&jmpOffset,2);         //Copia por 2 bytes
                chunk.current+=2;
                jmpOffset=chunk.current;
                memcpy(&chunk.instructions[instructionOffsets[tokens[current].jumpTo]-2],(void*)&jmpOffset,2);  //Back Patching
                current++;
            default:
            break;
        }
    }
    chunk.instructions[chunk.current]=OP_END;
    //free((void*)instructionOffsets);
}

Chunk* parse(Token* toks,int mode){
    tokens=toks;
    current=0;
    loopCount=0;
    //Inicializar el loop
    initLoopStack();
    //Parsear todos los tokens
    while (tokens[current].type !=TOKEN_EOF){
        parseLoop();
    }
    if(loopstack.sp !=0){
        for(int i=1;i<loopstack.sp+1;i++){
            fprintf(stderr, "Syntax Error: '[' at line %d pos. %d has no maching ']'.\n",
            loopstack.stack[i].line,loopstack.stack[i].position);
        }
        //free(loopstack.stack);
        exit(1420);
    }
    emitBytecode();
    switch(mode){
        case RUN:
            startVm(chunk.instructions,chunk.size,false);
        break;
        case COMPILE:
            compile(chunk.instructions);
        break;
        case DEBUG:
            startVm(chunk.instructions,chunk.size,true);
        break;
    }
    //startVm(chunk.instructions, chunk.size,false);
}

void printParsedToken(Token token){
    switch(token.type){
        case TOKEN_PLUS:
            printf("#%04d Token: '+'(increment)  \n",token.offset);
        break;
        case TOKEN_MINUS:
            printf("%04d Token '-'  (decrement)  \n",token.offset);
        break;
        case TOKEN_COMMA:
            printf("%04d Token ','  (scan)       \n",token.offset);
        break;
        case TOKEN_DOT:
            printf("%04d Token '.'  (print)      \n",token.offset);
        break;
        case TOKEN_LEFT:
            printf("%04d Token '<'  (left)       \n",token.offset);
        break;
        case TOKEN_RIGHT:
            printf("%04d Token '>'  (right)      \n",token.offset);
        break;
        case TOKEN_LBRACE:
            printf("%04d Token '['  (loop start) Jump to: %u\n",token.offset,token.jumpTo);
        break;
        case TOKEN_RBRACE:
            printf("%04d Token ']'  (loop end)   Jump to: %u\n",token.offset,token.jumpTo);
        break;  
        case TOKEN_EOF:
            printf("%04d Token 'EOF'             \n",token.offset);
        break;
        default:
        break;
    }
}