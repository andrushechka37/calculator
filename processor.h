#include "stack_func.h"

// TODO: add a comment
enum bin { // TODO: what is bin? I think you misunderstand what enums are for
    command_bits = 31,
    const_bit    =  5,
    reg_bit      =  6,
    ram_bit      =  7
};




enum commands { // TODO: singular for enum?
    #define DEF_CMD(name, num, ...)            \
    Cmd_ ## name = num,                        \

    #include "commands.h"
};

int const pop          =    3; // TODO: what is this for?
int const push         =    2;
int const str_len      =  100;
int const bin_input    =    0;
int const multiple     =  100;
int const poison_value = -999; // TODO: space?
struct processor {
    int registers[5]; // TODO: 5?
    stack stk; // TODO: stk?
    int * code_array;
    int ip;
    int labels[10]; // TODO: you already told what you need to do  
    int RAM[str_len]; // TODO: str_len?
    stack execution_context;

    // TODO: if you strategically

    // int registers_[5];
    // stack data_stack_;
    // int RAM_[str_len];

    // int *current_executable_;
    // int ip_;

    // stack execution_context_;

};

int get_size_of_file(FILE * file); // TODO: why are we still here? Just to suffer!

int str_to_int(char str[]); // TODO: why are we still here? Just to suffer!

void code_array_gen(processor * proc, FILE * pfile);

int put_arg(int command, processor * proc, FILE * pfile);
int * get_arg(int command, processor * proc, FILE * pfile, int caller);

void put_argument(processor * proc, FILE * input, FILE * pasm, int num, int have_arg);
