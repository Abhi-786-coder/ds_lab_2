#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    int top;
    unsigned capacity;
    char *array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    if (!stack) {
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    if (!stack->array) {
        free(stack);
        return NULL;
    }
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == (int)(stack->capacity) - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack Overflow!\n");
        return;
    }
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow!\n");
        return '\0';
    }
    return stack->array[stack->top--];
}

void reverseString(char str[]) {
    unsigned n = strlen(str);
    struct Stack* stack = createStack(n);
    if (!stack) {
        printf("Memory allocation failed!\n");
        return;
    }
    for (unsigned i = 0; i < n; i++) {
        push(stack, str[i]);
    }
    for (unsigned i = 0; i < n; i++) {
        str[i] = pop(stack);
    }
    free(stack->array);
    free(stack);
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    reverseString(str);
    printf("Reversed string: %s\n", str);
    return 0;
}
