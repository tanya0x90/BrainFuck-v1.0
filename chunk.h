#ifndef BF_CHUNK_H
#define BF_CHUNK_H

typedef enum{
    OP_ADD,
    OP_SUB,
    OP_LEFT,
    OP_RIGHT,
    OP_SCAN,
    OP_PRINT,
    OP_JZ,
    OP_JNZ,
    OP_INT,
    OP_END
}Opcode;

typedef struct{
    unsigned char* instructions;
    unsigned int current;
    unsigned int size;
}Chunk;

#endif