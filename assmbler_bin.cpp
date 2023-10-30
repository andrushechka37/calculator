#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "processor.h"

// TODO: why don't you have assembler header?


// TODO: you can make it smaller, and ... just delete this and write it better
// func arg ��������� //bad rewrite

// TODO: you can place it where you use it
#define DEF_CMD(name, num, have_arg, ...)                                     \
if (strcmp(str, #name) == 0) {                                                \
    put_argument(proc, input, pasm, num, have_arg);                           \
} else                                                                        \



// TODO: assemble_single_pass? <assemble>?
void assembler(processor * proc) {
    FILE * input = fopen("asm.txt", "r");
    FILE * pasm = fopen("input.txt", "wt");/////////// costul // TODO: Agreed

    proc->code_array = (int *) calloc(get_size_of_file(input) * 4, 1);
    // TODO:                                                               ^

    char str[100] = {0};
    //       ^~~ TODO: what is this?

    while (fscanf(input, "%s", str) != EOF) {
        char * label_check = strchr(str, ':');
        #include "commands.h"
    /*else*/ if(str[0] == ':') {
            proc->labels[str[1] - '0'] = proc->ip;      
        } else {
            printf("Syntax error %s - error cause", str);
        } 
    }
    fclose(pasm);
    fclose(input);

}
int main(void) {
    // TODO: at least make this a function...
    processor proc = {};     // -----+
    assembler(&proc);   //      | This whole thing should be a function
    proc.ip = 0;             //      |
    assembler(&proc);   // -----+

    // TODO: where is proc destructor?

    for(int i = 0; i < 10; i++) {
        printf("%d", proc.labels[i]);
    }

    // TODO: a function?
    FILE * pasm_bin = fopen("input_bin.bin", "wb");
    fwrite(proc.code_array, sizeof(int), proc.ip - 1, pasm_bin);
    // while(proc.code_array[i] != 0) {
    //     printf("%d\n", proc.code_array[i]);
    //     i++;
    // }
}

void put_argument(processor * proc, FILE * input, FILE * pasm, int num, int have_arg) {
    int arg = 0;                                                              
    char n_reg = 0;                                                           
    char x_check = 0;  
    if (have_arg == 1) {                                                      
        if (fscanf(input, "%d", &arg) == 1) {                                 
            fprintf(pasm, "%d %d\n", ((1 << const_bit) | num), arg);         
            proc->code_array[proc->ip++] = (1 << const_bit) | num;            
            proc->code_array[proc->ip++] = arg;                               
        } else if (fscanf(input, " r%c%c", &n_reg, &x_check) == 2) {          
            fprintf(pasm, "%d ", ((1 << reg_bit) | num));                     
            proc->code_array[proc->ip++] = (1 << reg_bit) | num;              
            fscanf(input, " r%c%c", &n_reg, &x_check);                        
            if (x_check == 'x') {                                             
                fprintf(pasm, "%d \n", n_reg - 'a' + 1);                      
                proc->code_array[proc->ip++] = n_reg - 'a' + 1;               
            } else {                                                          
                printf("error");                                              
            }                                                                 
        } else if (fscanf(input, " :%c", (char *)&n_reg) == 1) {                      
            proc->code_array[proc->ip++] = num;                              
            fprintf(pasm, "%d", num);                                      
            if (proc->labels[n_reg - '0'] != 0) {                                   
                proc->code_array[proc->ip++] = proc->labels[n_reg - '0'];          
                fprintf(pasm, " %d\n", proc->labels[n_reg - '0']);                  
            } else {                                                          
                proc->code_array[proc->ip++] = -999;                          
                fprintf(pasm, " -999\n");                                     
            }                                                                 
        } else if (fscanf(input, " [ %d ]", &arg) == 1) {
            fprintf(pasm, "%d %d\n", ((1 << ram_bit) | num), arg);
            proc->code_array[proc->ip++] = (1 << ram_bit) | num;
            proc->code_array[proc->ip++] = arg;
        }                                                                
        } else {                                                              
        fprintf(pasm, "%d\n", num);                                           
        proc->code_array[proc->ip++] = num;                                   
    }     
}

// TODO: why don't you just include textlib.h-like thing from Onegin as a separate header?
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
// TODO: WHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAT?

// #%&&@&&####%&&&@&&%&&&&@&&&&%%####%%%%####%%##((((%%%%%%%%%%%%%%%%%#&&&&&&&&%%&%
// &&@@&&%%%%#%##%##########&&&%%%#####%%%%%%%#((((////%%%%%%%%%%######&##%&%#####%
// @@@@@&&&&%%%######((####(#&&#%#######&#%&&#(((((#(##%@@&%%%%%%#####%%##&#####%##
// &@@@@&@@&%%%%#####(#######/(%&%%%%%##((*.     ,*((#(&%%%&%%%%%#%%##&%#%%%###%%#%
// &@&&@&@@@(/(#&###%%%%#%#%(/*//#%##(*,.           , *&&%%%%%%%%%&&%%&&&%%%%%%%##%
// &@&@@@%#(*(@&&@%##(((((#&/////*///*.     .****,,,*   #%&&&&&&&&&&&&@&&&&&&%&&&&%
// %%#/*/////#@&&#%@&@@&&%////*//////,  . *((((((((((/,  #%&@&@@&%&&&&&&@@&%&&&&&&%
// %#(%@%&&&&&@@@&#(&@&&&%&,(/(#(*///#.,,/((####(((#((/,.*%%%%@@@&&%&@@@&&&&&&&&&&%
// &@@@@&&&@&&&&@@&&&&&&@%#&,//(&(((*#%*/((((###((##(((**%%&&%@&&&&@@@@@@&@@@@@&&&%
// &&@@@@@&@&#@&&&&&&&&&&&##&##(%#//%%%,/(((((((((#(((//#%%&&&&&&&&&&&&&@@@@@@&&&&%
// &@@@@@@@&&@@&&&&&&&&&&&%%%&%#%&((#%#.////(((#####(//#%%%%%#%&&&&&&&&&&&&@@&&&@&%
// &@@@@@@@&@@@@&&&&&&@&&&&&&&@&#&#(##(,////(((((//(//(&%%%%##&&&&&&&&&@@@&@&&&&@&%
// &@@@@@@@@@@@&&&&&&&&@&&&&&&&&@#.    /((///////////. /&%%%##@&&&&&@@@@@&&&@@@@@&%
// &&&@@@@@@@@@@&&&&&&&&&&&&&&.     ...##(((((///////(/    .%%&&&&&&@@@@@&&&&@@&&&%
// &@&@@@@@@@@@&&&&&&&&@&&@,    ...,.,,/%(#(#((((((/(((*..  . ,%&&&&@&@@&&&&&&&&&%%
 // ../&@@@@@@@&&&&&@@&@(. . ,,/#(..,**(#(#####((((####/,,,,,,,,*&&&&&&&&&&&@@&&&%%
   // .,,,#@@@@@@@@@@@#.   ,#,,/(#*,,**/(/(####/(####*/(*.... .,..*&@&&&&&&&&&&&&%&
  // ,*.,*/(##((#((#(., .,*##(*/,/(**,*/  .   #*/, %, /(#,..   .*/,.#&&&&&&@&&&&&%%
    // .,*/((#(((((..*/((,*(#(((*/(#/(,/(*%**#*/*#*&(*/%*...**,*#*,,/.@@@@@&&&&&&%%
 // .,*.,*(%#&&&@&%,(*///*/*%#%#(#(#/*/(#(((***///(#(((////,,/((/**/,/,#@&&&&&&%%%%
// ****,,*/#(#&&&@*/*(/////*(#%%(%#%(*,**,    .#####((((//*(./(/**#*/*/*#&&&&&&&%%&
// //(*.,*(##%#&&&*///(#//((/(%###%#/..,*(%&%&&%/..*****//, ., */(#/#*//*#@@@&%%%%&

// TODO: in case this ASCII art is not readable, follow this link
// https://www.google.com/url?sa=i&url=https%3A%2F%2Fknowyourmeme.com%2Fmemes%2Fwat&psig=AOvVaw3ht41L-36NEwSBjqXbf-HU&ust=1697918732921000&source=images&cd=vfe&ved=0CBEQjRxqFwoTCKi3-6i2hYIDFQAAAAAdAAAAABAE
// (also, cheers to all guys from future, where this link is long
// dead, sorry, I couldn't have predicted that. Oh wait, I did. Still,
// I'm to lazy to do anything about it, if you are really curious,
// google "WAT MEME", probably in your era it's still available from
// archives of the old internet).

// P.S. It'd be funny if Google is dead in your time and you can't
//      "google", good luck then.
