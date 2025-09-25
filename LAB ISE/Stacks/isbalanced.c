#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Stack {
    int top;
    unsigned capacity;
    char *array;
};

struct Stack *createStack(unsigned capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void push(struct Stack *stack, char item) {
    if (!isFull(stack))
        stack->array[++stack->top] = item;
}

char pop(struct Stack *stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '\0';
}

char peek(struct Stack *stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return '\0';
}

void freeStack(struct Stack *stack) {
    free(stack->array);
    free(stack);
}

int isMatchingPair(char open, char close) {
    if (open == '(' && close == ')')
        return 1;
    if (open == '{' && close == '}')
        return 1;
    if (open == '[' && close == ']')
        return 1;
    return 0;
}

int areBracketsBalanced(char *exp) {
    int len = strlen(exp);
    struct Stack *stack = createStack(len);

    for (int i = 0; i < len; i++) {
        char c = exp[i];
        if (c == '(' || c == '{' || c == '[') {
            push(stack, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (isEmpty(stack)) {
                freeStack(stack);
                return 0;
            }
            char topChar = pop(stack);
            if (!isMatchingPair(topChar, c)) {
                freeStack(stack);
                return 0;
            }
        }
    }

    int balanced = isEmpty(stack);
    freeStack(stack);
    return balanced;
}

int main() {
    char expression[MAX];
    printf("Enter an expression: ");
    scanf(" %[^\n]", expression);  // Reads until newline, including spaces

    if (areBracketsBalanced(expression))
        printf("The expression is balanced.\n");
    else
        printf("The expression is NOT balanced.\n");

    return 0;
}
