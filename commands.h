DEF_CMD(push, 1, true, {
  stack_push(&proc->stk,
             command_understand(full_command, proc, pfile) * multiple);
})

DEF_CMD(sub, 2, false, {
    stack_pop(&proc->stk, &sec_arg);
    stack_pop(&proc->stk, &first_arg);
    stack_push(&proc->stk, (first_arg - sec_arg));
})

// TODO: Look what I've done. You can do it too!
DEF_CMD(mul, 3, false, {
    stack_pop(&proc->stk, &sec_arg);
    stack_pop(&proc->stk, &first_arg);
    stack_push(&proc->stk, (first_arg * sec_arg) / multiple);
})

DEF_CMD(div,  4, false, {stack_pop(&proc->stk, &sec_arg);
                         stack_pop(&proc->stk, &first_arg);
                         stack_push(&proc->stk, ((multiple*first_arg) / sec_arg));})
DEF_CMD(add,  5, false, {stack_pop(&proc->stk, &sec_arg);
                         stack_pop(&proc->stk, &first_arg);
                         stack_push(&proc->stk, (first_arg+sec_arg));})
DEF_CMD(sqrt, 6, false, {stack_pop(&proc->stk, &argument);
                         dump_stk(&proc->stk, " ", 1, " ");
                         stack_push(&proc->stk, (int)(sqrt((double) (argument/multiple)) * multiple));})
DEF_CMD(sin,  7, false, {stack_pop(&proc->stk, &argument);
                         stack_push(&proc->stk, (int)(sin((double) (argument/multiple)) * multiple));})
DEF_CMD(cos,  8, false, {stack_pop(&proc->stk, &argument);
                         stack_push(&proc->stk, (int)(cos((double) (argument/multiple)) * multiple));})
DEF_CMD(in,   9, false, {printf("type the number:\n");
                          scanf("%d", &argument);
                          stack_push(&proc->stk, argument * multiple);
                          dump_stk(&proc->stk, " ", 1, " ");})
DEF_CMD(out, 10, false, {stack_pop(&proc->stk, &argument);
                          printf("%.2lf\n", (double) argument / multiple);})
DEF_CMD(pop, 11, true,  {stack_pop(&proc->stk, command_understand_pop(full_command, proc, pfile));})
DEF_CMD(jmp, 12, true, {proc->ip = proc->code_array[proc->ip];})
DEF_CMD(hlt, -1, false, {return;})
DEF_CMD(jbe, 13, true, {stack_pop(&proc->stk, &argument);
                        stack_pop(&proc->stk, &first_arg);
                        if (argument >= first_arg) {
                            proc->ip = proc->code_array[proc->ip];
                        } else {
                            proc->ip++;
                        }}) // TODO: Ehhhh





