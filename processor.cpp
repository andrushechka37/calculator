#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "processor.h"
// valueble pushed to stack is multilpied 100
// TODO: WHY ARE YOU COMMITING BINARIES?
// TODO: ARE COMMIT MESSAGES A JOKE FOR YOU?
// dont comment text of programm


// norm funs that decides what to do   NOOOOOOOOOOOOOOOOOOOOOOOOOOOO


void CPU(FILE * pfile, processor * proc) {
    while ((proc->code_array[proc->ip]) != 0) {
        int command = (proc->code_array[proc->ip++]);
        int operation = command & command_bits;

        if (command == -1) {
            break;
        }
        int argument = 0;
        int reg_number = 0;
        int first_arg = 0;
        int sec_arg = 0;
        switch(operation) {
            #define DEF_CMD(name, num, have_arg, code, ...)                      \
            case Cmd_ ## name: {code} break;                                     \

            #include "commands.h"
            default:
                printf("unknown commad rewrite %d - operation, %d - argument", operation, argument);
                return;
        }
    }
}

void CPU_Ctor(FILE ** pfile, processor * proc) {
    Stack_Ctor(&proc->stk);
    Stack_Ctor(&proc->execution_context);
    if(bin_input == 0) {
        *pfile = fopen("input.txt", "r");
    } else if (bin_input == 1) {
        *pfile = fopen("input_bin.bin", "rb");
    }
}

void CPU_Dtor(FILE * pfile, processor * proc) {
    fclose(pfile);
    free(proc->code_array);
    stack_dtor(&proc->stk);
    stack_dtor(&proc->execution_context);
}
int main(void) {
    processor proc = {};
    FILE * pfile = 0;
    CPU_Ctor(&pfile, &proc);
    code_array_gen(&proc, pfile);
    dump_stk(&proc.stk, " ", 1, " ");
    CPU(pfile, &proc);
    dump_stk(&proc.stk, " ", 1, " ");
    int x = 0;
    CPU_Dtor(pfile, &proc);
    
}
////////////////////////-----------------------------------------------------------------------------------------------------
int * get_arg(int command, processor * proc, FILE * pfile, int caller) {
    if ((command & (1 << const_bit)) != 0) {
        proc->registers[0] = (proc->code_array[proc->ip++]);
        return &proc->registers[0];
    }
    if((command & (1 << reg_bit)) != 0) {
        int reg_num = (proc->code_array[proc->ip++]);
        return &(proc->registers[reg_num]);
    }
    if ((command & (1 << ram_bit)) != 0) {
        int ram_num = (proc->code_array[proc->ip++]);
        return &(proc->RAM[ram_num]);
    }
    return 0;
} 
int put_arg(int command, processor * proc, FILE * pfile) {
    if((command & (1 << reg_bit)) != 0) {
        int reg_num = (proc->code_array[proc->ip++]);
        return (proc->registers[reg_num] / multiple);
    }
    if ((command & (1 << const_bit)) != 0) {
        int argument = (proc->code_array[proc->ip++]);
        return argument;
    }
    if ((command & (1 << ram_bit)) != 0) {
        int ram_num = (proc->code_array[proc->ip++]);
        return (proc->RAM[ram_num] / multiple);
    }
    return poison_value;
}


void code_array_gen(processor * proc, FILE * pfile) {
    proc->code_array = (int *) calloc(get_size_of_file(pfile) * sizeof(int), 1);
    if (bin_input == 0) {
    proc->ip = 0;
    char str[str_len] = {0};
    int arg = 0;
    while(fscanf(pfile, "%s", str) != EOF) {
        arg = str_to_int(str);
        proc->code_array[proc->ip++] = arg;
    }
    proc->ip = 0;
    int i = 0;
    while(proc->code_array[i] != 0) {
        printf("%d\n", proc->code_array[i]);
        i++;
    }
    } else {
        fread(proc->code_array, sizeof(int), get_size_of_file(pfile) * sizeof(int), pfile);
    }
}

int get_size_of_file(FILE * file) {
    struct stat buff;
    fstat(fileno(file), &buff);
    return buff.st_size;
}

int str_to_int(char str[]) {
    int x = 0;
    int sign = 1;
    for(int i = 0; str[i] != 0; i++) {
        if(str[i] == '-') {
            sign = -1;
            continue;
        }
        x = x * 10 + (str[i] - '0');
    }
    return x * sign;
}


