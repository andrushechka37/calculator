#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "processor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEF_CMD(name, num, have_arg, ...)                                     \
if (strcmp(str, #name) == 0) {                                                \
    int arg = 0;                                                              \
    char n_reg = 0;                                                           \
    char x_check = 0;                                                         \
    if (have_arg == 1) {                                                      \
        if (fscanf(input, "%d", &arg) == 1) {                                 \
            fprintf(pasm, "%d %d\n", ((1 << const_bit) | num), arg);          \
            proc->code_array[proc->ip++] = (1 << const_bit) | num;            \
            proc->code_array[proc->ip++] = arg;                               \
        } else if (fscanf(input, " r%c%c", &n_reg, &x_check) == 2) {          \
            fprintf(pasm, "%d ", ((1 << reg_bit) | num));                     \
            proc->code_array[proc->ip++] = (1 << reg_bit) | num;              \
            fscanf(input, " r%c%c", &n_reg, &x_check);                        \
            if (x_check == 'x') {                                             \
                fprintf(pasm, "%d \n", n_reg - 'a' + 1);                      \
                proc->code_array[proc->ip++] = n_reg - 'a' + 1;               \
            } else {                                                          \
                printf("error");                                              \
            }                                                                 \
        } else if (fscanf(input, " :%c", (char *)&n_reg) == 1) {                      \
            proc->code_array[proc->ip++] = num;                               \
            fprintf(pasm, "%d", num);                                       \
            if (proc->labels[n_reg - '0'] != 0) {                                   \
                proc->code_array[proc->ip++] = proc->labels[n_reg - '0'];           \
                fprintf(pasm, " %d\n", proc->labels[n_reg - '0']);                  \
            } else {                                                          \
                proc->code_array[proc->ip++] = -999;                          \
                fprintf(pasm, " -999\n");                                     \
            }                                                                 \
        }                                                                     \
        } else {                                                              \
        fprintf(pasm, "%d\n", num);                                           \
        proc->code_array[proc->ip++] = num;                                   \
    }                                                                         \
} else                                                                        \



void assembler(processor * proc) {
    FILE * input = fopen("input.txt", "r");
    FILE * pasm = fopen("asm.txt", "wt");/////////// costul 
    proc->code_array = (int *) calloc(get_size_of_file(input) * 4, 1);
    char str[100] = {0};
    while (fscanf(input, "%s", str) != EOF) {
        char * label_check = strchr(str, ':');
        #include "commands.h"
        #undef DEF_CMD
    /*else*/ if(str[0] == ':') {
        proc->labels[str[1] - '0'] = proc->ip;
        
        } else {
        printf("Syntax error");
        } 
    }
    fclose(pasm);
    fclose(input);

}
int main(void) {
    processor proc = {};
    //int arg = str_to_int(str);
    //proc->code_array[proc->ip++] = arg;

    assembler(&proc);
    proc.ip = 0;
    assembler(&proc);

    // func arg обработка //bad rewrite
    for(int i = 0; i < 10; i++) {
        printf("%d", proc.labels[i]);
    }

    FILE * pasm_bin = fopen("asm_bin.txt", "wb");
    fwrite(proc.code_array, sizeof(int), proc.ip - 1, pasm_bin);
    // while(proc.code_array[i] != 0) {
    //     printf("%d\n", proc.code_array[i]);
    //     i++;
    // }
}



int get_size_of_file(FILE * file) {
    struct stat buff;
    fstat(fileno(file), &buff);
    return buff.st_size;
}

int str_to_int(char str[]) { /////////strtoi
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

            // } else if(fscanf(input, "%c", &n_reg) == 1 && n_reg == ':') {         \
            //     fprintf(pasm, " %c\n", n_reg);                                    \
            // }                                                                     \



//  else if (label_check != 0) {
//             if (proc->labels[*(label_check + 1) - '0'] != 0) {
//                 proc->code_array[proc->ip++] = Cmd_jmp;
//                 proc->code_array[proc->ip++] = proc->labels[*(label_check + 1) - '0'];
//                 fprintf(pasm, "%d %d\n", Cmd_jmp, proc->labels[*(label_check + 1) - '0']);
//             } 




// if (strcmp(str, "add") == 0) {
//             fprintf(pasm, "%d\n", Cmd_add);
//             proc.code_array[proc.ip++] = Cmd_add;
//         } else if(strcmp(str, "sub") == 0) {
//             fprintf(pasm, "%d\n", Cmd_sub);
//             proc.code_array[proc.ip++] = Cmd_sub;
//         } else if(strcmp(str, "mul") == 0) {
//             fprintf(pasm, "%d\n", Cmd_mul);
//             proc.code_array[proc.ip++] = Cmd_mul;
//         } else if (strcmp(str, "div") == 0) {
//             fprintf(pasm, "%d\n", Cmd_div);
//             proc.code_array[proc.ip++] = Cmd_div;
//         } else if(strcmp(str, "push") == 0) {
//
//             int  argument = 0;
//             char n_reg = 0;
//             if (fscanf(input, "%d", &argument) == 1) {
//
//                 fprintf(pasm, "%d %d\n", ((1 << 4) | Cmd_push), argument);
//                 proc.code_array[proc.ip++] = (1 << 4) | Cmd_push;
//                 proc.code_array[proc.ip++] = argument;
//
//             } else {
//
//                 char x_check = 0;  //   ^ register
//                 fprintf(pasm, "%d ", ((1 << 5) | Cmd_push));
//                 proc.code_array[proc.ip++] = (1 << 5) | Cmd_push;
//                 fscanf(input, " r%c%c", &n_reg, &x_check);
//                 if (x_check == 'x') {
//                     fprintf(pasm, "%d \n", n_reg - 'a' + 1);
//                     proc.code_array[proc.ip++] = n_reg - 'a' + 1;
//                 } else {
//                     fprintf(pasm, "unknown command");
//                     proc.code_array[proc.ip++] = -999;
//                 }
//             }
//
//         } else if (strcmp(str, "sqrt") == 0) {
//             fprintf(pasm, "%d\n", Cmd_sqrt);
//             proc.code_array[proc.ip++] = Cmd_sqrt;
//         } else if (strcmp(str, "sin") == 0) {
//             fprintf(pasm, "%d\n", Cmd_sin);
//             proc.code_array[proc.ip++] = Cmd_sin;
//         } else if (strcmp(str, "cos") == 0) {
//             fprintf(pasm, "%d\n", Cmd_cos);
//             proc.code_array[proc.ip++] = Cmd_cos;
//         } else if (strcmp(str, "in") == 0) {
//             fprintf(pasm, "%d\n", Cmd_in);
//             proc.code_array[proc.ip++] = Cmd_in;
//         } else if (strcmp(str, "out") == 0) {
//             fprintf(pasm, "%d\n", Cmd_out);
//             proc.code_array[proc.ip++] = Cmd_out;
//         } else if (strcmp(str, "halt") == 0) {
//             fprintf(pasm, "%d\n", Cmd_hlt);
//             proc.code_array[proc.ip++] = Cmd_hlt;
//         } else if (strcmp(str, "pop") == 0) {
//             char n_reg = 0;
//             char x_check = 0;
//             fprintf(pasm, "%d ", ((1 << 5) | Cmd_pop));
//             proc.code_array[proc.ip++] = (1 << 5) | Cmd_pop;
//             fscanf(input, " r%c%c", &n_reg, &x_check);
//                 if (x_check == 'x') {
//                     fprintf(pasm, "%d \n", n_reg - 'a' + 1);
//                     proc.code_array[proc.ip++] = n_reg - 'a' + 1;
//                 } else {
//                     fprintf(pasm, "unknown command");
//                     proc.code_array[proc.ip++] = -999;
//                 }
//         } else {
//             fprintf(pasm, "unknown func");
//             proc.code_array[proc.ip++] = -999;
//         }
