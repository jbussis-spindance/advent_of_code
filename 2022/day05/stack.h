/**
 * @brief simple stack implementation
 * 
 */

#ifndef STACK__H_
#define STACK__H_

typedef struct Stack {
    char value;
    struct Stack *next;
} Stack;

Stack *stack_init(void);
void stack_push(Stack **head, char value);
char stack_pop(Stack **head);
void stack_reverse(Stack **head);
void stack_free(Stack **head);
void test_stack(void);

#endif // STACK__H_
