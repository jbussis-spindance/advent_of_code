#include "stack.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PART 1
#define DEBUG false

#define LINE_LENGTH 64
#define NUM_STACKS 9

static Stack *_stack_list[NUM_STACKS];


void init_stacks(void) {
    for (int i = 0; i < NUM_STACKS; ++i) {
        _stack_list[i] = stack_init();
    }
}

// finds the values in the provided line and 
// returns the number of values found so we 
// know when to quit filling the stacks
int add_to_stacks(char *line) {
    int str_len_of_stack_entry = 4;
    int num_values_found = 0;
    for (int i = 0; i < NUM_STACKS; ++i) {
        int first_index = str_len_of_stack_entry * i;
        // if the first char is a space, just skip
        if (line[first_index] == ' ')
            continue;
        // there is a value, the next char will be the value
        // we want
        num_values_found++;
        char new_entry = line[first_index + 1];
        stack_push(&_stack_list[i], new_entry);
        // printf("index: %d, value: %c\n", i, new_entry);
    }

    return num_values_found;
}


void move_one_by_one(int from_stack, int to_stack, int num_crates) {
    char value;
    for (int i = 0; i < num_crates; ++i) {
        value = stack_pop(&_stack_list[from_stack]);
        stack_push(&_stack_list[to_stack], value);
    }
}


void move_by_group(int from_stack, int to_stack, char num_crates) {
    char values[num_crates];
    // pop off the values
    for (int i = 0; i < num_crates; ++i) {
        values[i] = stack_pop(&_stack_list[from_stack]);
    }

    // push them in reverse
    for (int i = num_crates-1; i >= 0; --i) {
        stack_push(&_stack_list[to_stack], values[i]);
    }
}


void execute_instructions(char *line) {
    if (line[0] != 'm') {
        // each instruction line starts with
        // the word 'move', so if the first char
        // isn't m, then just skip it
        return;
    }
    // get the amount of crates to move, start stack, end stack
    int num_crates = 0;
    int from_stack = 0;
    int to_stack = 0;
    int parsing_stage = 0;

    for (int i = 0; i < LINE_LENGTH; ++i) {
        // if reach the end of the data, we are 
        // done parsing
        if (line[i] == '\n' || line[i] == '\0')
            break;

        // these are the chars directly after the 
        // numbers in the instruction, so they are 
        // a good thing to check to increment the 
        // parsing stage
        if (line[i] == 'f' ||
            line[i] == 't') {
            parsing_stage++;
            continue;
        }

        if (!isdigit(line[i])) {
            // don't care
            continue;
        }

        // add the number to the correct variable
        // based on the 
        switch (parsing_stage) {
            case 0: // num_crates
                num_crates *= 10;
                num_crates += line[i] - '0';
                break;
            case 1: // from_stack
                from_stack *= 10;
                from_stack += line[i] - '0';
                break;
            case 2: // to_stack
                to_stack *= 10;
                to_stack += line[i] - '0';
                break;
            default: 
                break;
        }
    }

    // they labeled the stacks starting at 1
    from_stack--; 
    to_stack--;
#if(PART == 1)
    move_one_by_one(from_stack, to_stack, num_crates);
#else 
    move_by_group(from_stack, to_stack, num_crates);
#endif
}


void reverse_stacks(void) {;
    for (int i = 0; i < NUM_STACKS; ++i) {
        stack_reverse(&_stack_list[i]);
    }
}


void print_top_of_stacks(void) {
    char str[NUM_STACKS+1];
    memset(str, 0, sizeof(str));
    for (int i = 0; i < NUM_STACKS; ++i) {
        str[i] = stack_pop(&_stack_list[i]);
    }
    printf("top of stacks: %s\n", str);
}


void print_stacks(void) {
    for (int i = 0; i < NUM_STACKS; ++i) {
        while (_stack_list[i]) {
            printf(" %c \n", stack_pop(&_stack_list[i]));
        }
        printf("********\n");
    }
}


int main(void) {
    
#if(DEBUG == true)
    printf("Testing...\n"); 
    test_stack();
    printf("Done Testing.\n");
#endif

    printf("initializing stacks...\n");
    init_stacks();

    FILE *input = fopen("input.txt", "r");
    char buf[LINE_LENGTH] = {0};
    bool stacks_filled = false;

    while (fgets(buf, LINE_LENGTH, input)) {
        if (!stacks_filled) {
            if (add_to_stacks(buf) == 0) {
                reverse_stacks();
                stacks_filled = true;
            }
            continue;
        }

        execute_instructions(buf);
    }

    print_top_of_stacks();

    fclose(input);

    printf("done\n");

    return 0;
}
