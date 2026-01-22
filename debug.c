#include "debug.h"

typedef struct{
    unsigned int offset;
    unsigned char opcode;
    bool set;
}Breakpoint;

Breakpoint bpTable[10000];
unsigned int chunkSize=0;

static bool isBpValid(unsigned int offset){
    if(offset == bpTable[offset].offset){
        return true;
    }
    return false;
}

static void recoverBp(VM* vm, unsigned int offset){
    if(isBpValid(offset)&& bpTable[offset].set == true){
        vm->instructions[offset]=OP_INT;
        printf("Breakpoint recovered at %u\n",offset);
    }
}

static void toggleBreakpoint(VM* vm, int bpAdress){
    if(bpTable[bpAdress].set==true){
        puts("Breakpoint removed");
        vm->instructions[bpAdress]=bpTable[bpAdress].opcode;
        bpTable[bpAdress].set=false;
        return;
    }
}

void debugger(VM* vm, unsigned char* tape){
    char action=0;
    int bpAdress=0;         //Experimental
    int vmStatus=2;
    bool fillTable=true;
    int currentBreakpoint=0;    //Experimental
    int bpRecovery=0;
    bool printDisassembly=true;
    memset(bpTable,0,sizeof(bpTable));
    chunkSize=vm->size;
    puts("Debugger ready!\n");
    puts("Commands: c=continue, n=next, b=toggle breack point, p=print dissambly");
    //Leector del debugger
    while (vmStatus !=0){
        bpRecovery=vm->ip;
        if (printDisassembly){
            printf("%s","IP>");
            disassembleVM(vm,fillTable);
            printTape(vm);
        }
        fillTable=false;
        if(vmStatus==1){
            vm->instructions[vm->ip]=bpTable[vm->ip].opcode;
        }
        printf("%s",">>");
        action=getchar();
        switch(action){
            case 'c':
                vm->debugged=true;
                vmStatus=runVm();
                recoverBp(vm,bpRecovery);
                vm->debugged=false;
                vmStatus=runVm();
                printDisassembly=true;
                break;
            case 'n':
                vm->debugged=true;
                vmStatus=runVm();
                recoverBp(vm,bpRecovery);
                vm->debugged=false;
                printDisassembly=true;
                break;
            case 'b':
                printDisassembly=false;
                puts("Enter address to togle breakpoint:");
                scanf("%05d",&bpAdress);
                if(isBpValid){
                    toggleBreakpoint(vm,bpAdress);
                }
                puts("Invalid Address");
                break;
            case 'p':
                printDisassembly=true;
                break;
            default:
                break;
        }
    }
}

void disassembleVM(VM* vm, bool fillTable){
    unsigned int i=vm->ip;
    unsigned short jmpOffset=0;
    while (vm->instructions[i] !=OP_END){
        switch (vm->instructions[i]){
            case OP_ADD:
                printf("#%04u OP_ADD\n",i);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_ADD;
                }
                i++;
                break;
            case OP_SUB:
                printf("#%04u OP_SUB\n",i);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_SUB;
                }
                i++;
                break;
            case OP_LEFT:
                printf("#%04u OP_LEFT\n",i);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_LEFT;
                }
                i++;
                break;
            case OP_RIGHT:
                printf("#%04u OP_RIGHT\n",i);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_RIGHT;
                }
                i++;
                break;
            case OP_SCAN:
                printf("#%04u OP_SCAN\n",i);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_SCAN;
                }
                i++;
                break;
            case OP_PRINT:
                printf("#%04u OP_PRINT\n",i);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_PRINT;
                }
                i++;
                break;
            case OP_JZ:
                printf("#%04u OP_JZ",i);
                memcpy((void*)&jmpOffset,(void*)vm->instructions+i+1,2);
                printf("%05u\n", jmpOffset);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_JZ;
                }
                i+=3;
                break;
            case OP_JNZ:
                printf("#%04u OP_JNZ ",i);
                memcpy((void*)&jmpOffset,(void*)vm->instructions+i+1,2);
                printf("%05u\n", jmpOffset);
                if ((fillTable)){
                    bpTable[i].offset=i;
                    bpTable[i].opcode=OP_JNZ;
                }
                i+=3;
            case OP_INT:
                unsigned char currentInstruccion=bpTable[i].opcode;
                printf(" * #%04u OP_",i);
                disassembleInstruction(currentInstruccion);
                if(currentInstruccion==OP_JZ || currentInstruccion==OP_JNZ){
                    printf("%05u", (unsigned short)vm->instructions[i+1]);
                    i+=2;
                }
                i++;
                break;
            default:
                printf("Error: Invalid instroccion. \n");
                exit(143);
                break;
        }
    }
    printf("#%04u OP_END\n",i);
}

void disassembleInstruction(unsigned char opcode){
    switch (opcode){
        case OP_ADD:
            printf("%s","ADD");
            break;
        case OP_SUB:
            printf("%s","SUB");
            break;
        case OP_LEFT:
            printf("%s","LEFT");
            break;
        case OP_RIGHT:
            printf("%s","RIGHT");
            break;
        case OP_SCAN:
            printf("%s","SCAN");
            break;
        case OP_PRINT:
            printf("%s","PRINT");
            break;
        case OP_JZ:
            printf("%s","JZ");
            break;
        case OP_JNZ:
            printf("%s","JNZ");
            break;
        default:
            break;
    }
}

void printTape(VM* vm){
    printf("%s","\n");
    if (vm->tp-5>0){
        printf("%s",vm->tape[vm->tp-5]);
    }
    if (vm->tp-4>0){
        printf("%s",vm->tape[vm->tp-4]);
    }
    if (vm->tp-3>0){
        printf("%s",vm->tape[vm->tp-3]);
    }
    if (vm->tp-2>0){
        printf("%s",vm->tape[vm->tp-2]);
    }
    if (vm->tp-1>0){
        printf("%s",vm->tape[vm->tp-1]);
    }

    printf("%s",vm->tape[vm->tp]);

    if(vm->tp+1 < 30000){
        printf("|%d|",vm->tape[vm->tp+1]);
    }
    if(vm->tp+2 < 30000){
        printf("|%d|",vm->tape[vm->tp+2]);
    }
    if(vm->tp+3 < 30000){
        printf("|%d|",vm->tape[vm->tp+3]);
    }
    if(vm->tp+4 < 30000){
        printf("|%d|",vm->tape[vm->tp+4]);
    }
    if(vm->tp+5 < 30000){
        printf("|%d|",vm->tape[vm->tp+5]);
    }
    printf("%s","\n");
}


/*void disassembleChunk(Chunk chunk){
    unsigned int i=0;
    unsigned short jmpOffset=0;
    while (chunk.instructions[i] !=OP_END){
        switch (chunk.instructions[i]){
            case OP_ADD:
                printf("#%04u OP_ADD\n",i);
                i++;
                break;
            case OP_SUB:
                printf("#%04u OP_SUB\n",i);
                i++;
                break;
            case OP_LEFT:
                printf("#%04u OP_LEFT\n",i);
                i++;
                break;
            case OP_RIGHT:
                printf("#%04u OP_RIGHT\n",i);
                i++;
                break;
            case OP_SCAN:
                printf("#%04u OP_SCAN\n",i);
                i++;
                break;
            case OP_PRINT:
                printf("#%04u OP_PRINT\n",i);
                i++;
                break;
            case OP_JZ:
                printf("#%04u OP_JZ %05u\n",i,(unsigned short)chunk.instructions[i+1]);
                i+=3;
                break;
            case OP_JNZ:
                printf("#%04u OP_JNZ ",i);
                memcpy((void*)&jmpOffset,(void*)chunk.instructions+i+1,2);
                printf("%05u\n", jmpOffset);
                i+=3;
            case OP_INT:
                printf("#%04u OP_INT\n",i);
                i++;
                break;
            default:
                printf("Error: Invalid instroccion. \n");
                exit(143);
                break;
        }
    }
    printf("#%04u OP_END\n",i);
}*/