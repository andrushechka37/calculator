#include "stack_func.h"

enum bin {
    command_bits = 31,
    const_bit    =  5,
    reg_bit      =  6,
    ram_bit      =  7
};




enum commands {
    #define DEF_CMD(name, num, ...)            \
    Cmd_ ## name = num,                        \

    #include "commands.h"
};
int const pop          =    3;
int const push         =    2;
int const str_len      =  100;
int const bin_input    =    0;
int const multiple     =  100;
int const poison_value = -999;
struct processor {
    int registers[5];
    stack stk;
    int * code_array;
    int ip;
    int labels[10];
    int RAM[str_len];
};

int get_size_of_file(FILE * file);

int str_to_int(char str[]);

void code_array_gen(processor * proc, FILE * pfile);

int command_understand_push(int command, processor * proc, FILE * pfile);
int * command_understand_pop(int command, processor * proc, FILE * pfile, int caller);

void put_argument(processor * proc, FILE * input, FILE * pasm, int num, int have_arg);