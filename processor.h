#define bin_input 0

#define canary 0
#define dump_and_check 1
#define hash 0

#if dump_and_check
#define verify(stk) verificator_of_stack(&stk, __FILE__, __LINE__, __func__)
#else
#define verify(stk) ;
#endif

#if canary
#define can(stk, t) put_canary(&stk, t)
#else
#define can(stk, t) ;
#endif

#if hash
#define check_hash(stk) hash_check(&stk)
#define calc_data(stk) hash_counter_data(&stk)
#define calc_stack(stk) hash_counter_stack(&stk)
#else
#define check_hash(stk) ;
#define calc_data(stk) 0;
#define calc_stack(stk) 0;
#endif

enum bin {
    command_bit = 31,
    const_bit = 5,
    reg_bit = 6
};


typedef int elem_t;
typedef unsigned long long canary_t;

const int start_capacity = 7;
const int realloc_const = 2;

enum errors {
    pop_with_0_size = 1,
    stk_zero_pointer = 2,
    size_bigger_capacity = 3,
    size_below_zero = 4,
    capacity_below_zero = 5,
    dead_canary = 6
};
struct stack {
    unsigned long long left_canary;

    elem_t * data;
    unsigned long long int size;
    unsigned long long int capacity;
    unsigned long long int hash_data;
    unsigned long long int hash_stack;

    unsigned long long  right_canary;
};
enum commands {
    #define DEF_CMD(name, num, ...)            \
    Cmd_ ## name = num,                        \

    #include "commands.h"
    #undef DEF_CMD
};
int Stack_Ctor(stack * stk);

int stack_push(stack * stk, elem_t value);
int stack_pop(stack * stk, elem_t * value);

int stack_extension(stack * stk);
int stack_compression(stack * stk);
int put_canary(stack * stk, char type);

int verificator_of_stack(stack * stk, const char *file, int line, const char * func);
void dump_stk(stack * stk, const char *file, int line, const char * func);
int hash_counter_stack(stack * stk);
int hash_counter_data(stack * stk);
int hash_check(stack * stk);

int stack_dtor(stack * stk);
/////////-processor funcs-//////

int const multiple = 100;
int const poison_value = -999;

struct processor {
    int registers[5];
    stack stk;
    int * code_array;
    int ip;
    int labels[10];
};

int get_size_of_file(FILE * file);
int str_to_int(char str[]);
void code_array_gen(processor * proc, FILE * pfile);
int * command_understand_pop(int full_command, processor * proc, FILE * pfile);
int command_understand(int full_command, processor * proc, FILE * pfile);












    // CMD_hlt    =   -1,
    // Cmd_push    =    1,
    // Cmd_sub     =    2,
    // Cmd_mul     =    3,
    // Cmd_div     =    4,
    // Cmd_add     =    5,
    // Cmd_sqrt    =    6,
    // Cmd_sin     =    7,
    // Cmd_cos     =    8,
    // Cmd_in      =    9,
    // Cmd_out     =   10,
    // Cmd_pop     =   11
