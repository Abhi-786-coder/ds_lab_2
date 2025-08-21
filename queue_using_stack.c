#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Stack structure
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Create a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack operations
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}
void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }
    return stack->array[stack->top--];
}

// Free stack
void freeStack(struct Stack* stack) {
    free(stack->array);
    free(stack);
}

// Queue using 2 stacks
struct Queue {
    struct Stack *s1, *s2;
};

// Create a queue
struct Queue* createQueue(unsigned capacity) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->s1 = createStack(capacity);
    q->s2 = createStack(capacity);
    return q;
}

// Enqueue: always push into s1
void enqueue(struct Queue* q, int item) {
    push(q->s1, item);
    printf("%d enqueued\n", item);
}

// Dequeue: transfer from s1 to s2 when s2 is empty
int dequeue(struct Queue* q) {
    if (isEmpty(q->s1) && isEmpty(q->s2)) {
        printf("Queue is empty\n");
        return INT_MIN;
    }

    if (isEmpty(q->s2)) {
        while (!isEmpty(q->s1)) {
            push(q->s2, pop(q->s1));
        }
    }
    return pop(q->s2);
}

// Peek front element
int peekQueue(struct Queue* q) {
    if (isEmpty(q->s1) && isEmpty(q->s2)) {
        printf("Queue is empty\n");
        return INT_MIN;
    }

    if (isEmpty(q->s2)) {
        while (!isEmpty(q->s1)) {
            push(q->s2, pop(q->s1));
        }
    }
    return q->s2->array[q->s2->top];
}

// Free queue
void freeQueue(struct Queue* q) {
    freeStack(q->s1);
    freeStack(q->s2);
    free(q);
}

// Main
int main() {
    int capacity, choice, value;
    printf("Enter the capacity of the queue: ");
    scanf("%d", &capacity);

    struct Queue* q = createQueue(capacity);

    do {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek Front\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(q, value);
            break;
        case 2:
            value = dequeue(q);
            if (value != INT_MIN)
                printf("%d dequeued\n", value);
            break;
        case 3:
            value = peekQueue(q);
            if (value != INT_MIN)
                printf("Front element is %d\n", value);
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    freeQueue(q);
    return 0;
}
