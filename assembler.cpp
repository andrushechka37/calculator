// TODO: what is this file doing here?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "processor.h"

int main(void) {
    FILE * input = fopen("input.txt", "r");
    FILE * pasm = fopen("asm.txt", "wt");

    char str[100] = {0};
    while (fscanf(input, "%s", str) != EOF) {
        if (strcmp(str, "add") == 0) {
            fprintf(pasm, "%d\n", Cmd_add);
        } else if(strcmp(str, "sub") == 0) {
            fprintf(pasm, "%d\n", Cmd_sub);
        } else if(strcmp(str, "mul") == 0) {
            fprintf(pasm, "%d\n", Cmd_mul);
        } else if (strcmp(str, "div") == 0) {
            fprintf(pasm, "%d\n", Cmd_div);
        } else if(strcmp(str, "push") == 0) {

            int  argument = 0;
            char n_reg = 0;
            if (fscanf(input, "%d", &argument) == 1) {

                fprintf(pasm, "%d %d\n", ((1 << 4) | Cmd_push), argument);

            } else {

                char x_check = 0;  //   ^ register
                fprintf(pasm, "%d ", ((1 << 5) | Cmd_push));
                fscanf(input, " r%c%c", &n_reg, &x_check);
                if (x_check == 'x') {
                    fprintf(pasm, "%d \n", n_reg - 'a' + 1);
                } else {
                    fprintf(pasm, "unknown command");
                }
            }

        } else if (strcmp(str, "sqrt") == 0) {
            fprintf(pasm, "%d\n", Cmd_sqrt);
        } else if (strcmp(str, "sin") == 0) {
            fprintf(pasm, "%d\n", Cmd_sin);
        } else if (strcmp(str, "cos") == 0) {
            fprintf(pasm, "%d\n", Cmd_cos);
        } else if (strcmp(str, "in") == 0) {
            fprintf(pasm, "%d\n", Cmd_in);
        } else if (strcmp(str, "out") == 0) {
            fprintf(pasm, "%d\n", Cmd_out);
        } else if (strcmp(str, "halt") == 0) {
            fprintf(pasm, "%d\n", CMD_hlt);
        } else if (strcmp(str, "pop") == 0) {
            char n_reg = 0;
            char x_check = 0;
            fprintf(pasm, "%d ", ((1 << 5) | Cmd_pop));
            fscanf(input, " r%c%c", &n_reg, &x_check);
                if (x_check == 'x') {
                    fprintf(pasm, "%d \n", n_reg - 'a' + 1);
                } else {
                    fprintf(pasm, "unknown command");
                }
        } else {
            fprintf(pasm, "unknown func");
        }

    }
    fclose(pasm);
    fclose(input);
}



