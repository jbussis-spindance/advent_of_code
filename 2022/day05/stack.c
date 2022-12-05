#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

Stack *stack_init(void) {
    Stack *head = NULL;
    return head;
}

void stack_push(Stack **head, char value) {
    Stack *stack = *head;
    Stack *new_entry = (Stack *)malloc(sizeof(Stack));
    new_entry->value = value;
    new_entry->next = stack;
    *head = new_entry;
}

char stack_pop(Stack **head) {
    assert(*head != NULL);
    Stack *stack = *head;
    Stack *temp = *head;
    char return_value = stack->value;
    stack = stack->next;
    *head = stack;
    free(temp);
    return return_value;
}

void stack_reverse(Stack **head) {
    Stack *stack = *head;
    Stack *new_stack = stack_init();
    char value;
    while (stack) {
        value = stack_pop(&stack);
        stack_push(&new_stack, value);
    }
    *head = new_stack;
}

void stack_free(Stack **head) {
    // pop the rest of the values off and 
    // discard the returned values. pop 
    // frees the memory as it goes
    Stack *stack = *head;
    while (stack) {
        (void)stack_pop(&stack);
    }
}

void test_stack(void) {
    printf(" [+] init\n");
    Stack *stack = stack_init();
    printf(" [+] push\n");
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);
    stack_push(&stack, 4);

    printf(" [+] pop\n");
    char value = stack_pop(&stack);
    assert(value == 4);
    value = stack_pop(&stack);
    assert(value == 3);
    value = stack_pop(&stack);
    assert(value == 2);
    value = stack_pop(&stack);
    assert(value == 1);

    printf(" [+] free\n");
    stack_free(&stack);
    assert(stack == NULL);
}
