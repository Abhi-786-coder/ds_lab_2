#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Stack {
    int top;
    int capacity;
    char *array;
};


struct Stack* createstack(int capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}


int isfull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}


int isempty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    if (isfull(stack)) {
        printf("Stack Overflow!\n");
        return;
    }
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (isempty(stack)) {
        printf("Stack Underflow!\n");
        return '\0';
    }
    return stack->array[stack->top--];
}


void reversestring(char str[]) {
    int n = strlen(str);

    
    struct Stack* stack = createstack(n);

    
    for (int i = 0; i < n; i++) {
        push(stack, str[i]);
    }

   
    for (int i = 0; i < n; i++) {
        str[i] = pop(stack);
    }

    free(stack->array);
    free(stack);
}

int main() {
    char str[100];

    printf("Enter a string: ");
    scanf("%s", str); 

    reversestring(str);

    printf("Reversed string: %s\n", str);

    return 0;
}
