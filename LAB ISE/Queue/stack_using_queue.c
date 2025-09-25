#include <stdio.h>
#include <stdlib.h>

struct LQueue {
    int front, rear, size;
    int *arr;
};

// Create queue
struct LQueue *createQueue(int capacity) {
    struct LQueue *queue = (struct LQueue *)malloc(sizeof(struct LQueue));
    queue->size = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->arr = (int *)malloc(capacity * sizeof(int));
    return queue;
}

// Check empty
int isEmpty(struct LQueue *queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Check full
int isFull(struct LQueue *queue) {
    return (queue->rear == queue->size - 1);
}

// Enqueue
void enqueue(struct LQueue *queue, int value) {
    if (isFull(queue)) return;
    if (queue->front == -1) queue->front = 0;
    queue->arr[++queue->rear] = value;
}

// Dequeue
int dequeue(struct LQueue *queue) {
    if (isEmpty(queue)) return -1;
    return queue->arr[queue->front++];
}

// Peek front
int peek(struct LQueue *queue) {
    if (isEmpty(queue)) return -1;
    return queue->arr[queue->front];
}

// ---------------- Stack using Queue ----------------
struct Stack {
    struct LQueue *q;
    int capacity;
};

// Create stack
struct Stack *createStack(int capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->q = createQueue(capacity);
    stack->capacity = capacity;
    return stack;
}

// Push element onto stack
void push(struct Stack *stack, int value) {
    if (isFull(stack->q)) {
        printf("Stack overflow!\n");
        return;
    }

    enqueue(stack->q, value);

    // Rotate queue to bring new element to front
    int size = stack->q->rear - stack->q->front + 1;
    for (int i = 0; i < size - 1; i++) {
        int temp = dequeue(stack->q);
        enqueue(stack->q, temp);
    }
    printf("Pushed: %d\n", value);
}

// Pop element from stack
int pop(struct Stack *stack) {
    if (isEmpty(stack->q)) {
        printf("Stack underflow!\n");
        return -1;
    }
    int val = dequeue(stack->q);
    printf("Popped: %d\n", val);
    return val;
}

// Top element
int top(struct Stack *stack) {
    if (isEmpty(stack->q)) return -1;
    return peek(stack->q);
}

// Check empty
int empty(struct Stack *stack) {
    return isEmpty(stack->q);
}

// ---------------- Main ----------------
int main() {
    int capacity, choice, value;
    printf("Enter stack size: ");
    scanf("%d", &capacity);

    struct Stack *stack = createStack(capacity);

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                pop(stack);
                break;
            case 3:
                value = top(stack);
                if (value != -1)
                    printf("Top element: %d\n", value);
                else
                    printf("Stack is empty!\n");
                break;
            case 4:
                free(stack->q->arr);
                free(stack->q);
                free(stack);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

