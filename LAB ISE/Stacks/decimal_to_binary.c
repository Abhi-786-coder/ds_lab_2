#include <stdio.h>
#include <stdlib.h>
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
    return -1; // error code
}

void freeStack(struct Stack *stack) {
    free(stack->array);
    free(stack);
}

void decimalToBinary(int num) {
    struct Stack *stack = createStack(MAX);

    if (num == 0) {
        printf("Binary: 0\n");
        freeStack(stack);
        return;
    }

    while (num > 0) {
        push(stack, num % 2);
        num /= 2;
    }

    printf("Binary: ");
    while (!isEmpty(stack))
        printf("%d", pop(stack));
    printf("\n");

    freeStack(stack);
}

int main() {
    int number;
    printf("Enter decimal number: ");
    scanf("%d", &number);

    decimalToBinary(number);
    return 0;
}
