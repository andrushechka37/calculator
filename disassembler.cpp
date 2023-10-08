#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum commands {
    Cmd_halt    =   -1,
    Cmd_add     =    1,
    Cmd_sub     =    2,
    Cmd_mul     =    3,
    Cmd_div   =    4,
    push    =    5,
    Cmd_sqrt  =    6,
    Cmd_sin   =    7,
    Cmd_cos   =    8,
    Cmd_in      =    9,
    Cmd_out     =   10
};

int main(void) {
    FILE * pasm = fopen("asm.txt", "r");
    FILE * input = fopen("check.txt", "wt");
    int x = 0;
    while (fscanf(pasm, "%d", &x) != EOF) {
        switch(x) {
            case Cmd_halt:
                fprintf(input, "%s", "Cmd_halt\n");
                break;
            case Cmd_add:
                fprintf(input, "%s", "Cmd_add\n");
                break;
            case Cmd_sub:
                fprintf(input, "%s", "Cmd_sub\n");
                break;
            case Cmd_mul:
                fprintf(input, "%s", "Cmd_mul\n");
                break;
            case Cmd_div:
                fprintf(input, "%s", "div\n");
                break;
            case push:
                fprintf(input, "%s", "push ");
                fscanf(pasm, "%d", &x);
                fprintf(input, "%d\n", x);
                break;
            case Cmd_sqrt:
                fprintf(input, "%s", "sqrt\n");
                break;
            case Cmd_sin:
                fprintf(input, "%s", "sin\n");
                break;
            case Cmd_cos:
                fprintf(input, "%s", "cos\n");
                break;
            case Cmd_in:
                fprintf(input, "%s", "Cmd_in\n");
                break;
            case Cmd_out:
                fprintf(input, "%s", "out\n");
                break;
            default:
                fprintf(input, "%s", "troubles");
        }
    }
}
