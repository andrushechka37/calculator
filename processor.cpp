#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "processor.h"
//////////// valueble pushed to stack is multilpied 100
// TODO: WHY ARE YOU COMMITING BINARIES?
// TODO: ARE COMMIT MESSAGES A JOKE FOR YOU?
// dont comment text of programm


//norm funs that decides what to do   NOOOOOOOOOOOOOOOOOOOOOOOOOOOO
// input and asm change names

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
        *pfile = fopen("asm.txt", "r");
    } else if (bin_input == 1) {
        *pfile = fopen("asm_bin.bin", "rb");
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
int * command_understand_pop(int command, processor * proc, FILE * pfile, int caller) {
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
int command_understand_push(int command, processor * proc, FILE * pfile) {
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



/////////////////////////////-----------------------------------------------------------------------------------------
int Stack_Ctor(stack * stk) {
    stk->left_canary = 0xDEADBEEF;
    stk->right_canary = 0xDEADBEEF;
    stk->capacity = start_capacity;
    stk->size = 0;
    stk->data = (elem_t *)calloc(sizeof(elem_t) * start_capacity + 2 * sizeof(canary_t), 1);
    stk->data = (elem_t*)&(((canary_t*)stk->data)[1]);
    can(*stk, 'l');
    *(canary_t *)(stk->data + (stk->capacity)) = 0xDEADBEEF;
    stk->hash_data = calc_data(*stk);
    stk->hash_stack = calc_stack(*stk);
    return 0;
}

int stack_push(stack * stk, elem_t value) {
    verify(*stk);
    if (stk->size + 2 >= stk->capacity) {
        printf("push call realloc\n");
        stack_extension(stk);
    }
    stk->data[stk->size++] = value;
    // stk->hash_data = calc_data(*stk);
    // stk->hash_stack = calc_stack(*stk);
    // verify(*stk);
    return 0;
}

int stack_pop(stack * stk, elem_t * value) {
    verify(*stk);
    if (stk->size == 0 && dump_and_check == 1) {
        printf("pop with zero size\n");
        dump_stk(stk, __FILE__, __LINE__, __func__);
        exit(-1);
        return -1;
    }

    *value = (stk->data[--stk->size]);
    stk->data[stk->size] = -999;
    // stk->hash_data = calc_data(*stk);
    // stk->hash_stack = calc_stack(*stk);
    // if (stk->size < (stk->capacity) / 2) {
    //     stack_compression(stk);
    // }
    // stk->hash_data = calc_data(*stk);
    // stk->hash_stack = calc_stack(*stk);
    verify(*stk);
    return 0;
}

int stack_extension(stack * stk) {
    verify(*stk);
    stk->data = (elem_t*)&(((canary_t*)stk->data)[-1]);
    printf("adress of data was %p\n", stk->data);
    stk->data = (elem_t *) realloc(stk->data, sizeof(elem_t) * (stk->capacity * realloc_const) + 2 * sizeof(canary_t));
    stk->data = (elem_t*)&(((canary_t*)stk->data)[1]);
    printf("adress of data now %p\n", stk->data);
    can(*stk, 'r');
    stk->capacity *= realloc_const;
    stk->hash_data = calc_data(*stk);
    stk->hash_stack = calc_stack(*stk);
    verify(*stk);
    return 0;
}

int stack_compression(stack * stk) {
    verify(*stk);
    stk->data = (elem_t *)&(((canary_t*)stk->data)[-1]);
    stk->data = (elem_t *)realloc(stk->data, sizeof(elem_t) * (((stk->capacity) / realloc_const) + 3) + 2 * sizeof(canary_t));
    stk->data = (elem_t*)&(((canary_t*)stk->data)[1]);
    can(*stk, 's');
    stk->capacity = (stk->capacity / realloc_const) + 3;
    stk->hash_data = calc_data(*stk);
    stk->hash_stack = calc_stack(*stk);
    verify(*stk);
    return 0;
}

int put_canary(stack * stk, char type) {
    if (type == 'l') {
        ((canary_t*)stk->data)[-1] = 0xDEADBEEF;
    }

    if (type == 'r') {
        //*(canary_t *)(stk->data + (stk->capacity / 2) - 2) = 0;
        int fatnees_of_canary = sizeof(canary_t) / sizeof(elem_t);
        for (int i = 0; i < fatnees_of_canary; i++) {
            stk->data[stk->capacity + i] = 0;
        }

        *(canary_t *)(stk->data + (stk->capacity) * realloc_const) = 0xDEADBEEF;
    }
    if (type == 's') {
        int fatnees_of_canary = sizeof(canary_t) / sizeof(elem_t);
        for (int i = 0; i < fatnees_of_canary; i++) {
            stk->data[stk->capacity + i] = 0;
        }
        *(canary_t *)(stk->data + (stk->capacity) / realloc_const + 3) = 0xDEADBEEF;
    }
    return 0;
}

int verificator_of_stack(stack * stk, const char *file, int line, const char * func) {
    bool error = 0;
    if(stk->left_canary != 0xDEADBEEF && canary == 1) {
        printf("left canary of struct died\n");
        error = 1;
    }

    if(stk->right_canary != 0xDEADBEEF && canary == 1) {
        printf("right canary of struct died\n");
        error = 1;
    }

    if(((canary_t*)stk->data)[-1] != 0xDEADBEEF && canary == 1) {
        printf("left canary of array died\n");
        error = 1;
    }

    if(*(canary_t *)(stk->data + stk->capacity) != 0xDEADBEEF && canary == 1) {
        printf("right canary of array died\n");
        error = 1;
    }
    // if(check_hash(*stk) != 0) {
    //     printf("wrong hash\n");
    //     error = 1;
    // }

    if(stk == NULL) {
        printf("stk_zero_pointer\n");
        error = 1;
    }

    if (stk->size > stk->capacity) {
        printf("size_bigger_capacity\n");
        error = 1;
    }

    if (stk->capacity < 0) {
        printf("capacity_below_zero\n");
        error = 1;
    }

    if (stk->size < 0) {
        printf("size_below_zero\n");
        error = 1;
    }
    if(error == 1) {
        dump_stk(stk, file, line, func);
        exit(-1);
    }
    //if(//it was called from pop)
    //data 0
    return 0;
}

void dump_stk(stack * stk, const char *file, int line, const char * func) {
    printf("----------------------------------------------\n");
    printf("stack [%p]\n", stk);
    printf("called from file %s\n", file);
    printf("called from function %s\n", func);
    printf("called from line %d\n", line);
    printf("size = %llu\n", stk->size);
    printf("capacity = %llu\n", stk->capacity);
    if (hash == 1) {
        printf("data hash is %llu\n", stk->hash_data);
        printf("struct hash is %llu\n", stk->hash_stack);
    }
    printf("data [%p]\n", stk->data);
    if (canary == 1) {
        printf("left canary of array = 0x%llx\n", ((canary_t*)stk->data)[-1]);
    }
    for (int i = 0; i < stk->capacity; i++) {
        if (stk->data[i] == -999) {
            printf("*[%d] = -999(POISON)\n", i);
        } else {
            printf(" [%d] = %d\n", i, stk->data[i]);
        }
    }
    if (canary == 1) {
        printf("right canary of array = 0x%llx\n", *(canary_t *)(stk->data + stk->capacity));
    }
    printf("----------------------------------------------\n");
}

int hash_counter_stack(stack * stk) {
    return stk->capacity + stk->size;
}
int hash_counter_data(stack * stk) {
    int sum = 0;
    for(int i = 0; i <= stk->size; i++) {
        if(stk->data[i] != -999) {
            sum += stk->data[i];
        }
    }
    return sum;
}
int hash_check(stack * stk) {
    if (stk->hash_data != hash_counter_data(stk)) {
        printf("%d", hash_counter_data(stk));
        printf(" trouble with data\n");
        return -1;
    }
    if (stk->hash_stack != hash_counter_stack(stk)) {
        printf("trouble with stach struct\n");
        return 1;
    }
    return 0;
}

int stack_dtor(stack * stk) {
    free((elem_t *)&(((canary_t*)stk->data)[-1]));
    return 0;
}


