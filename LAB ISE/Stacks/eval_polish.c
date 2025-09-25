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

int evaluatePrefix(char *exp) {
    struct Stack *stack = createStack(strlen(exp));
    int len = strlen(exp);

    for (int i = len - 1; i >= 0; i--) {
        char c = exp[i];
        if (c == ' ' || c == '\t') continue;

        if (isdigit(c)) {
            push(stack, c - '0');
        } else {
            int op1 = pop(stack);
            int op2 = pop(stack);
            int result = 0;

            if (c == '+') result = op1 + op2;
            else if (c == '-') result = op1 - op2;
            else if (c == '*') result = op1 * op2;
            else if (c == '/') result = op1 / op2;

            push(stack, result);
        }
    }

    int res = pop(stack);
    freeStack(stack);
    return res;
}

int main() {
    char expression[MAX];
    printf("Enter prefix expression (single-digit operands): ");
    fgets(expression, MAX, stdin);
    expression[strcspn(expression, "\n")] = 0;

    int result = evaluatePrefix(expression);
    printf("Evaluation result: %d\n", result);

    return 0;
}
