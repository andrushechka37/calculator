#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "processor.h"


/// изменить константы на енам
// для попа и пуша расчет команд
// функция которая анализирует пуш и поп и ретернет то что нужно пушать или попать

int main(void) {
    FILE * input = fopen("input.txt", "r");
    FILE * pasm = fopen("asm.txt", "wt");
    char str[100] = {0};
    while (fscanf(input, "%s", str) != EOF) {
        if (strcmp(str, "add") == 0) {
            fprintf(pasm, "1\n");
        } else if(strcmp(str, "sub") == 0) {
            fprintf(pasm, "2\n");
        } else if(strcmp(str, "mul") == 0) {
            fprintf(pasm, "3\n");
        } else if (strcmp(str, "div") == 0) {
            fprintf(pasm, "4\n");
        } else if(strcmp(str, "push") == 0) {

            int  argument = 0;
            char n_reg = 0;
            if (fscanf(input, "%d", &argument) == 1) {

                fprintf(pasm, "%d %d\n", Cmd_push, argument);

            } else {

                int command = ((1 << 5) | 1); // 0010|0001
                                              //   ^ register
                fprintf(pasm, "%d ", command);
                fscanf(input, " r%cx", &n_reg);  // check x
                fprintf(pasm, "%d \n", n_reg - 'a' + 1);
            }

        } else if (strcmp(str, "sqrt") == 0) {
            fprintf(pasm, "6\n");
        } else if (strcmp(str, "sin") == 0) {
            fprintf(pasm, "7\n");
        } else if (strcmp(str, "cos") == 0) {
            fprintf(pasm, "8\n");
        } else if (strcmp(str, "in") == 0) {
            fprintf(pasm, "9\n");
        } else if (strcmp(str, "out") == 0) {
            fprintf(pasm, "10\n");
        } else if (strcmp(str, "halt") == 0) {
            fprintf(pasm, "-1\n");
        } else if (strcmp(str, "pop") == 0) {
            char n_reg = 0;
            fprintf(pasm, "43 ");
            fscanf(input, " r%cx", &n_reg);
            fprintf(pasm, "%d \n", n_reg - 'a' + 1);
        } else {
            fprintf(pasm, "unknown func");
        }

    }
}
