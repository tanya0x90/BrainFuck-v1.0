#include "compiler.h"


int compile(unsigned char* instructions){
    const char* filename = "assembly.asm";
    const char* mode = "w";
    int i = 0;

    FILE* file = fopen(filename,mode);
    if(file == NULL){
        fprintf(stderr,"Could not open file '%s'.\n",filename);
        exit(74);
    }

    //inicia archivo de ensamblador
    fputs("section .text\n\nglobal _start\n\n_start:\n",file);

    //inicializar tape pointer
    fputs("    mov rbx, buff\n",file);
    fputs("    add rbx, 15000\n",file);

    emitAssembly(file,instructions);

    //exit
    fputs("    xor rdi, rdi\n    mov rax, 60\n    syscall\n",file);

    //scan func
    fputs("scan:\n    xor rax, rax\n    xor rdi, rdi\n    mov rsi, tempbuff\n    mov rdx, 0x1\n    syscall\n\n",file);
    fputs("    mov rdx, tempbuff\n    mov rcx, [rdx]\n    cmp rcx, 0xa\n    je scan\n    mov[rbx], rcx\n    xor rcx, rcx\n    ret\n\n",file);

    //print func 
    fputs("print:\n    mov rax, 0x1\n    mov rdi, 0x1\n    mov rsi, rbx\n    mov rdx, 0x1\n    syscall\n    xor rcx, rcx\n    ret\n\n",file);

    //data sections
    fputs("section .data\n    buff db 30000 dup(0)\n\n",file);
    fputs("section .bss\n    tempbuff resb 0x0\n",file);

    fclose(file);

    system("nasm -f elf64 -o obj.o assembly.asm");
    system("ld -o a.out obj.o");
    system("rm -f obj.o");
    return 0;
}

static int peek(unsigned char* instructions, unsigned int instruction){
    unsigned int reps = 0;
    while(instructions[reps] == instruction){
        reps++;
    }
    return reps;
}

void emitAssembly(FILE* file, unsigned char* instructions){
    int i = 0;
    char symbolA[] = {0,0,0,0,0,0};
    char symbolB[] = {0,0,0,0,0,0};
    int previousInstruction = OP_INT;

    while(instructions[i] != OP_END){
        switch (instructions[i]){
        case OP_ADD:{
            int j = 1;
            j += peek(instructions+i+1,OP_ADD);
            previousInstruction = OP_ADD;
            if(j > 1){
                fprintf(file,"    mov cl,[rbx]\n    add cl, %d\n    mov [rbx], cl\n",j);
                i += j;
                break;
            }
            fputs("    mov cl, [rbx]\n    inc cl\n    mov [rbx], cl\n",file);
            i++;
        }
        break;
        case OP_SUB:{
            int j = 1;
            j += peek(instructions+i+1,OP_SUB);
            previousInstruction = OP_SUB;
            if(j > 1){
                fprintf(file,"    mov cl,[rbx]\n    sub cl, %d\n    mov [rbx], cl\n",j);
                i += j;
                break;
            }
            fputs("    mov cl, [rbx]\n    dec cl\n    mov [rbx], cl\n",file);
            i++;
        }
        break;
        case OP_LEFT:{
            int j = 1;
            j += peek(instructions+i+1,OP_LEFT);
            previousInstruction = OP_LEFT;
            if(j > 1){
                fprintf(file,"    sub rbx, %d\n",j);
                i += j;
                break;
            }
            fputs("    dec rbx\n",file);
            i++;
        }
        break;
        case OP_RIGHT:{
            int j = 1;
            j += peek(instructions+i+1,OP_RIGHT);
            previousInstruction = OP_RIGHT;
            if(j > 1){
                fprintf(file,"    add rbx, %d\n",j);
                i += j;
                break;
            }
            fputs("    inc rbx\n",file);
            i++;
        }
        break;
        case OP_SCAN:
            fputs("    call scan\n",file);
            previousInstruction = OP_SCAN;
            i++;
        break;
        case OP_PRINT:
            fputs("    call print\n",file);
            previousInstruction = OP_PRINT;
            i++;
        break;
        case OP_JZ:{
            unsigned short jmpOffset = 0;
            memcpy(&jmpOffset,instructions+i+1,2);
            if(previousInstruction != OP_ADD && previousInstruction != OP_SUB){
                fprintf(file, "    mov cl, [rbx]\n");
            }
            fprintf(file, "    cmp rcx, 0\n    je %s\n%s:\n",
            generateSymbol(jmpOffset,symbolA),generateSymbol(i+3,symbolB));
            i+=3;
        }
        break;
        case OP_JNZ:{
            unsigned short jmpOffset = 0;
            memcpy(&jmpOffset,instructions+i+1,2);
            if(previousInstruction != OP_ADD && previousInstruction != OP_SUB){
                fprintf(file, "    mov cl, [rbx]\n");
            }
            fprintf(file, "    cmp rcx, 0\n    jne %s\n%s:\n",
            generateSymbol(jmpOffset,symbolA),generateSymbol(i+3,symbolB));
            i+=3;
        }
        break;
        default:
            break;
        }
    }
}

char* generateSymbol(unsigned short offset, char* symbol){
    memset(symbol,0,5);

    while (offset > 9999)
    {
        symbol[0]++;
        offset -= 10000;
    }
    while (offset > 999)
    {
        symbol[1]++;
        offset -= 1000;
    }
    while (offset > 99)
    {
        symbol[2]++;
        offset -= 100;
    }
    while ( offset > 9)
    {
        symbol[3]++;
        offset -= 10;
    }
    while (offset > 0)
    {
        symbol[4]++;
        offset--;
    }
    for(int i = 0; i< 5;i++){
        symbol[i]+= 'A';
    }
    
    return symbol;
    
    
}
