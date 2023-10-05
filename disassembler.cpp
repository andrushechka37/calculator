#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int main(void) {
    FILE * pasm = fopen("asm.txt", "r");
    FILE * input = fopen("check.txt", "wt");
    int x = 0;
    while (fscanf(pasm, "%d", &x) != EOF) {
        switch(x) {
            case halt:
                fprintf(input, "%s", "halt\n");
                break;
            case add:
                fprintf(input, "%s", "add\n");
                break;
            case sub:
                fprintf(input, "%s", "sub\n");
                break;
            case mul:
                fprintf(input, "%s", "mul\n");
                break;
            case div_c:
                fprintf(input, "%s", "div\n");
                break;
            case push:
                fprintf(input, "%s", "push ");
                fscanf(pasm, "%d", &x);
                fprintf(input, "%d\n", x);
                break;
            case sqrt_c:
                fprintf(input, "%s", "sqrt\n");
                break;
            case sin_c:
                fprintf(input, "%s", "sin\n");
                break;
            case cos_c:
                fprintf(input, "%s", "cos\n");
                break;
            case in:
                fprintf(input, "%s", "in\n");
                break;
            case out:
                fprintf(input, "%s", "out\n");
                break;
            default:
                fprintf(input, "%s", "troubles");
        }
    }
}
