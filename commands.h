

DEF_CMD(push, 1, true, {
    stack_push(&proc->stk,
             (put_arg(command, proc, pfile)) * multiple);
})


// TODO: Why didn't you generalize some of this functions?
//       Like so:

// #define BINARY_OPERATOR(operation_name, operation) \
       DEF_CMD(operation_name, 2, false, {            \
           stack_pop(&proc->stk, &sec_arg);           \
           stack_pop(&proc->stk, &first_arg);         \
           stack_push(&proc->stk, (operation));       \
       })
// 
// 
// BINARY_OPERATOR(sub, first_arg - sec_arg)
// BINARY_OPERATOR(add, first_arg + sec_arg)
// BINARY_OPERATOR(mul, first_arg * sec_arg)
// BINARY_OPERATOR(div, first_arg / sec_arg)

DEF_CMD(sub, 2, false, {
    stack_pop(&proc->stk, &sec_arg);
    stack_pop(&proc->stk, &first_arg);
    stack_push(&proc->stk, (first_arg - sec_arg));
})

DEF_CMD(mul, 3, false, {
    stack_pop(&proc->stk, &sec_arg);
    stack_pop(&proc->stk, &first_arg);
    stack_push(&proc->stk, (first_arg * sec_arg) / multiple);
})

DEF_CMD(div,  4, false, {
    stack_pop(&proc->stk, &sec_arg);
    stack_pop(&proc->stk, &first_arg);
    stack_push(&proc->stk, ((multiple*first_arg) / sec_arg));
})

DEF_CMD(add,  5, false, {
    stack_pop(&proc->stk, &sec_arg);
    stack_pop(&proc->stk, &first_arg);
    stack_push(&proc->stk, (first_arg+sec_arg));
})

DEF_CMD(sqrt, 6, false, {
    stack_pop(&proc->stk, &argument);
    dump_stk(&proc->stk, " ", 1, " "); // TODO: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHH
    stack_push(&proc->stk, (int)(sqrt((double) (argument/multiple)) * multiple));
})

DEF_CMD(sin,  7, false, {
    stack_pop(&proc->stk, &argument);
    stack_push(&proc->stk, (int)(sin((double) (argument/multiple)) * multiple));
})

DEF_CMD(cos,  8, false, {
    stack_pop(&proc->stk, &argument);
    stack_push(&proc->stk, (int)(cos((double) (argument/multiple)) * multiple));
})

DEF_CMD(in,   9, false, {
    printf("type the number:\n");
    scanf("%d", &argument);
    stack_push(&proc->stk, argument * multiple);
    dump_stk(&proc->stk, " ", 1, " ");
})

DEF_CMD(out, 10, false, {
    stack_pop(&proc->stk, &argument);
    printf("%.2lf\n", (double) argument / multiple);
})

DEF_CMD(pop, 11, true,  {
    stack_pop(&proc->stk, 
                get_arg(command, proc, pfile, pop));
})

DEF_CMD(jmp, 12, true, {
    proc->ip = proc->code_array[proc->ip];
})

DEF_CMD(hlt, -1, false, {
    return;
})

DEF_CMD(jbe, 13, true, {
    stack_pop(&proc->stk, &argument);
    stack_pop(&proc->stk, &first_arg);
    if (argument >= first_arg) {
        proc->ip = proc->code_array[proc->ip];
    } else {
        proc->ip++;
    }
})


DEF_CMD(call, 14, true, 
    stack_push(&proc->execution_context, proc->ip + 1);
    proc->ip = proc->code_array[proc->ip];
)
DEF_CMD(ret, 15, false, 
    stack_pop(&proc->execution_context, &(proc->ip));
)

DEF_CMD(je, 16, true, {
    stack_pop(&proc->stk, &argument);
    stack_pop(&proc->stk, &first_arg);
    if (argument == first_arg) {
        proc->ip = proc->code_array[proc->ip];
    } else {
        proc->ip++;
    }
})


DEF_CMD(ja, 17, true, {
    stack_pop(&proc->stk, &argument);
    stack_pop(&proc->stk, &first_arg);
    if (argument < first_arg) {
        proc->ip = proc->code_array[proc->ip];
    } else {
        proc->ip++;
    }
})

DEF_CMD(jb, 18, true, {
    stack_pop(&proc->stk, &argument);
    stack_pop(&proc->stk, &first_arg);
    if (argument > first_arg) {
        proc->ip = proc->code_array[proc->ip];
    } else {
        proc->ip++;
    }
})
DEF_CMD(jne, 19, true, {
    stack_pop(&proc->stk, &argument);
    stack_pop(&proc->stk, &first_arg);
    if (argument != first_arg) {
        proc->ip = proc->code_array[proc->ip];
    } else {
        proc->ip++;
    }
})



#undef DEF_CMD
