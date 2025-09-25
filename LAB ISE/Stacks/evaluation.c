#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

struct Stack {
    int top;
    unsigned capacity;
    int *array;
};

struct Stack *createStack(unsigned capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void push(struct Stack *stack, int item) {
    if (!isFull(stack))
        stack->array[++stack->top] = item;
}

int pop(struct Stack *stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1;  // error value
}

void freeStack(struct Stack *stack) {
    free(stack->array);
    free(stack);
}

int evaluatePostfix(char *exp) {
    struct Stack *stack = createStack(strlen(exp));
    int i;
    for (i = 0; exp[i]; i++) {
        char c = exp[i];
        if (c == ' ' || c == '\t') {
            continue;
        }
        if (isdigit(c)) {
            push(stack, c - '0');
        } else {
            int val2 = pop(stack);
            int val1 = pop(stack);
            int result = 0;
            if (c == '+')
                result = val1 + val2;
            else if (c == '-')
                result = val1 - val2;
            else if (c == '*')
                result = val1 * val2;
            else if (c == '/')
                result = val1 / val2;
            push(stack, result);
        }
    }
    int res = pop(stack);
    freeStack(stack);
    return res;
}

int main() {
    char expression[MAX];
    printf("Enter postfix expression (single-digit operands and operators): ");
    fgets(expression, MAX, stdin);
    expression[strcspn(expression, "\n")] = 0;

    int result = evaluatePostfix(expression);
    printf("Evaluation result: %d\n", result);
    return 0;
}
