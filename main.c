#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//Headear en la carpeta
#include "token.h"
#include "lexer.h"
#include "chunk.h"
#include "parser.h"

enum{
    FAIL,
    RUN,
    COMPILE,
    LEX,
    DEBUG
}Modes;

char* readFile(const char* filename, unsigned int* codeSize);
void callCompiler(int mode, char* filename);
Chunk* elchunk;

int main(int argc, char** argv){
    //Revision
    if(argc <2){
        printf("%s", "Error. Usage:\n brainfuck [-r/-c/-d] <filename.bf>\n");
        return 1;
    }
    int mode = FAIL;
    if(strcmp (argv[1],"-r")==0) mode = RUN;
    if(strcmp (argv[1],"-c")==0) mode = COMPILE;
    if(strcmp (argv[1],"-l")==0) mode = LEX;    //Flag oculto
    if(strcmp (argv[1],"-d")==0) mode = DEBUG;
    if(mode == FAIL){
        printf("%s", "Error. Bad flag. Usage:\n brainfuck [-r/-c/-d] <filename.bf>\n");
        return 1;
    }
    callCompiler(mode,argv[2]);
    return 0;
}

void callCompiler(int mode, char* filename){
    unsigned int codeSize = 0;
    char* sourceCode = readFile(filename,&codeSize);
    //Creacion de tokens
    Token* tokens = lex(sourceCode,codeSize);
    //Print tokens
    if(mode==LEX){
        for(int i=0;i<codeSize;i++){
            printToken(tokens[i]);
            if(tokens[i].type == TOKEN_EOF)break;
        }
        //Limpiar memoria
        free((void*)tokens);
        free((void*)sourceCode);
        return;
    }
    elchunk = parse(tokens,mode);
    /*for(int i=0;i<codeSize;i++){
        printParsedToken(tokens[i]);
        if(tokens[i].type==TOKEN_EOF)break;
    }*/
    free((void*)tokens);
    free((void*)sourceCode);
}

char* readFile(const char* filename, unsigned int* codeSize){
    FILE* file = fopen(filename,"rb");
    //Abrir archivo
    if(file==NULL){
        fprintf(stderr, "Could not open file'%s'.\n",filename);
        exit(74);
    }
    fseek(file,0L,SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    //Leer archivo
    char*buffer = (char*)malloc(fileSize+1);
    if(buffer==NULL){
        fprintf(stderr, "Not enough memory to read '%s'.\n",filename);
        exit(74);
    }
    size_t bytestRead = fread(buffer,sizeof(char), fileSize, file);
    //Validacion
    if(bytestRead < fileSize){
        fprintf(stderr, "Could not read file'%s'.\n",filename);
        exit(74);
    }
    *codeSize = bytestRead;
    buffer[bytestRead]=0;
    //Cerrar archivo
    fclose(file);
    return buffer;
}