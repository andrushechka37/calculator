// TODO: If this is used for conditional compilation, than
//       just use #ifdef and #ifndef and parametrize on 
//       define's existance, not it's value, this way
//       you don't need to mention it in any header file ever.
#define canary 0
#define dump_and_check 0
#define hash 0

#if dump_and_check
#define verify(stk) verificator_of_stack(&stk, __FILE__, __LINE__, __func__)
#else
// TODO: using ";" for an empty stmt is a bad idea. Think why.
#define verify(stk) ;
#endif

#if canary // TODO: can? Can not
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
// TODO: And now it's "0;", why?
#define calc_data(stk) 0;
#define calc_stack(stk) 0;
#endif




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