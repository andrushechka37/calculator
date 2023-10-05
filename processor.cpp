#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "processor.h"
int const multiple = 100;
enum commands {
    halt    =   -1,
    add     =    1,
    sub     =    2,
    mul     =    3,
    div_c   =    4,
    push    =    5,
    sqrt_c  =    6,
    sin_c   =    7,
    cos_c   =    8,
    in      =    9,
    out     =   10
};
//////////// valueble pushed to stack is multilpied 100
//out
void comander(FILE * pfile, stack * stk) {
    char command[5] = {0};
    char argument[100] = {0};
    int status = 0;
    while (((status = fscanf(pfile, "%s %s", command, argument))) != EOF && (command != halt)) {
        if (status == 1 && (command[0] - '0') <= 4) {
            int x = 0;
            int y = 0;
            stack_pop(stk, &y);
            stack_pop(stk, &x);
            switch(command[0] - '0') {
                case add:
                    stack_push(stk, (x+y));
                    break;
                case sub:
                    stack_push(stk, (x-y));
                    break;
                case mul:
                    stack_push(stk, (x*y) / 100);
                    break;
                case div_c:
                    stack_push(stk, ((100*x) / y));
                    break;

            }
        } else {
            int x = 0;
            if (command[0] - '0' != push && command[0] - '0' != in){
                stack_pop(stk, &x);
            }
            switch(command[0] - '0') {
                case push:
                    for(int i = 0; argument[i] != 0; i++) {
                        x = x * 10 + (argument[i] - '0');
                    }
                    stack_push(stk, x * multiple);
                    //dump_stk(stk, " ", 1, " ");
                    break;
                case sqrt_c:
                    dump_stk(stk, " ", 1, " ");
                    stack_push(stk, (int)(sqrt((double) (x/100)) * 100));
                    break;
                case sin_c:
                    stack_push(stk, (int)(sin((double) (x/100)) * 100));
                    break;
                case cos_c:
                    stack_push(stk, (int)(cos((double) (x/100)) * 100));
                    break;
                case in:
                    printf("type the number:\n");
                    scanf("%s", argument);
                    for(int i = 0; argument[i] != 0; i++) {
                        x = x * 10 + (argument[i] - '0');
                    }
                    stack_push(stk, x * multiple);
                    //dump_stk(stk, " ", 1, " ");
                    break;
                case out:
                    printf("f");
                    printf("%.2lf", (double) x / 100);
                    break;
            }
        }
    }
}
int main(void) {
    stack stk = {};
    FILE * pfile = fopen("asm.txt", "r");
    stack_ctor(&stk);


    // stack_push(&stk, 1);
    // stack_push(&stk, 2);
    dump_stk(&stk, " ", 1, " ");
    comander(pfile, &stk);
    int x = 0;
    dump_stk(&stk, " ", 1, " ");
    stack_pop(&stk, &x);

    //printf("%.2lf", (double) x / 100);
    stack_dtor(&stk);
}

/////////////////////////////////////////////-----------------------------------------------------------------------------

int stack_ctor(stack * stk) {
    stk->left_canary = 0xDEADBEEF;
    stk->right_canary = 0xDEADBEEF;
    stk->capacity = start_capacity;
    stk->size = 0;
    stk->data = (elem_t *)calloc(sizeof(elem_t) * start_capacity + 2 * sizeof(canary_t), 1);
    can(*stk, 'l');
    *(canary_t *)(stk->data + (stk->capacity)) = 0xDEADBEEF;
    stk->hash_data = calc_data(*stk);
    stk->hash_stack = calc_stack(*stk);
    return 0;
}

int stack_push(stack * stk, elem_t value) {
    //verify(*stk);
    if (stk->size + 2 >= stk->capacity) {
        printf("push call realloc\n");
        stack_extension(stk);
    }
    stk->data[stk->size++] = value;
    // stk->hash_data = calc_data(*stk);
    // stk->hash_stack = calc_stack(*stk);
    //verify(*stk);
    return 0;
}

int stack_pop(stack * stk, elem_t * value) {
    // verify(*stk);
    // if (stk->size == 0 && dump_and_check == 1) {
    //     printf("pop with zero size\n");
    //     dump_stk(stk, __FILE__, __LINE__, __func__);
    //     exit(-1);
    //     return -1;
    // }

    *value = stk->data[--stk->size];
    stk->data[stk->size] = -999;
    // stk->hash_data = calc_data(*stk);
    // stk->hash_stack = calc_stack(*stk);
    if (stk->size < (stk->capacity) / 2) {
        stack_compression(stk);
    }
    // stk->hash_data = calc_data(*stk);
    // stk->hash_stack = calc_stack(*stk);
    // verify(*stk);
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
        ((canary_t*)stk->data)[0] = 0xDEADBEEF;
        stk->data = (elem_t*)&(((canary_t*)stk->data)[1]);
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
    if(stk->left_canary != 0xDEADBEEF) {
        printf("left canary of struct died\n");
        error = 1;
    }

    if(stk->right_canary != 0xDEADBEEF) {
        printf("right canary of struct died\n");
        error = 1;
    }

    if(((canary_t*)stk->data)[-1] != 0xDEADBEEF) {
        printf("left canary of array died\n");
        error = 1;
    }

    if(*(canary_t *)(stk->data + stk->capacity) != 0xDEADBEEF) {
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
