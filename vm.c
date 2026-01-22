#include "vm.h"
#include "debug.h"

unsigned char tape[30000];
VM vm;

void startVm(unsigned char* instructions, unsigned int size, bool debug){
    vm.instructions = instructions;
    vm.tape = tape;
    vm.ip=0;
    vm.tp=sizeof(tape)/2;
    vm.debugged = debug;
    memset(tape,0,sizeof(tape));
    runVm();
}
int runVm(){
    unsigned short jumTo=0;
    bool breakpoint= vm.debugged;
    while (vm.instructions[vm.ip] !=OP_END){
        switch (vm.instructions[vm.ip]){
            case OP_ADD:
                vm.tape[vm.tp]++;
                vm.ip++;
                break;
            case OP_SUB:
                vm.tape[vm.tp]--;
                vm.ip++;
                break;
            case OP_LEFT:
                vm.tp--;
                vm.ip++;
                break;
            case OP_RIGHT:
                vm.tp++;
                vm.ip++;
                break;
            case OP_SCAN:
                scanf("%c",&vm.tape[vm.tp]);
                vm.ip++;
                break;
            case OP_PRINT:
                putchar(vm.tape[vm.tp]);
                vm.ip++;
                break;
            case OP_JZ:
                vm.ip++;
                if (vm.tape[vm.tp]==0){
                    //vm.ip = (unsigned short)vm.instructions[vm.ip];
                    memcpy(&jumTo, vm.instructions+vm.ip,2);
                    vm.ip = jumTo;
                    break;
                }
                vm.ip+=2;
                break;
            case OP_JNZ:
                vm.ip++;
                if (vm.tape[vm.tp] !=0){
                    //vm.ip = (unsigned short)vm.instructions[vm.ip];
                    memcpy(&jumTo,vm.instructions+vm.ip,2);
                    vm.ip = jumTo;
                    break;
                }
                vm.ip+=2;
                break;
            case OP_INT:
                breakpoint=true;
                break;
            default:
                printf("Run time error: Invalid intruction: %u\n",vm.instructions[vm.ip]);
                exit(143);
                break;
        }
        if(breakpoint==true){
            return 1;
        }
    }
    return 0;
}
