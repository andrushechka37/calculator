#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
            fprintf(pasm, "5 ");
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
        } else {
            fprintf(pasm, "%s\n", str);
        }

    }
}
