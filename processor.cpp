#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"


int main(void) {
    stack stk = {};
    stack_ctor(&stk);
    for(unsigned long long i = 3; i < 9999; i++) {
        stack_push(&stk, i);
        int t = i;
        stack_pop(&stk, &t);
        dump_stk(&stk, " ", 1," ");
        stk.capacity = 9;
        dump_stk(&stk, " ", 1," ");
    }
    dump_stk(&stk, " ", 1," ");

    // for(int i = 15; i > 5; i--) {
    //     int t = i;
    //     stack_pop(&stk, &t);
    //     printf("%d\n", t);
    //     dump_stk(&stk, " ", 1," ");
    // }

    stack_dtor(&stk);
}

