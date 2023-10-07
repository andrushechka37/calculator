#define canary 1
#define dump_and_check 1
#define hash 0

#ifdef dump_and_check
#define verify(stk) verificator_of_stack(&stk, __FILE__, __LINE__, __func__)
#endif

#ifdef canary
#define can(stk, t) put_canary(&stk, t)
#endif

#ifdef hash
#define check_hash(stk) hash_check(&stk)
#define calc_data(stk) hash_counter_data(&stk)
#define calc_stack(stk) hash_counter_stack(&stk)
#endif





typedef int elem_t;
typedef unsigned long long canary_t;

const int start_capacity = 3;
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
    halt    =   -1,
    add     =    1,
    sub     =    2,
    mul     =    3,
    div_c   =    4,
    Cmd_push    =    5,
    sqrt_c  =    6,
    sin_c   =    7,
    cos_c   =    8,
    in      =    9,
    out     =   10,
    pop_r   =   43,
    push_r  =   33


};
int stack_ctor(stack * stk);

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
