#include <stdio.h>
#include <stdlib.h>

// Queue structure
struct Queue {
    int front, rear, size, capacity;
    int* arr;
};

// Function to create a queue
struct Queue* createQueue(int capacity) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->arr = (int*)malloc(capacity * sizeof(int));
    return q;
}

int isFull(struct Queue* q) {
    return (q->size == q->capacity);
}

int isEmpty(struct Queue* q) {
    return (q->size == 0);
}

void enqueue(struct Queue* q, int item) {
    if (isFull(q)) return;
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = item;
    q->size++;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

// Stack using queue
struct Stack {
    struct Queue* q;
    int capacity;
};

// Create stack
struct Stack* createStack(int capacity) {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->q = createQueue(capacity);
    s->capacity = capacity;
    return s;
}

// Push operation (costly)
void push(struct Stack* s, int x) {
    if (isFull(s->q)) {
        printf("Stack Overflow\n");
        return;
    }

    // Enqueue new element
    enqueue(s->q, x);

    // Rotate queue to put new element at front
    for (int i = 0; i < s->q->size - 1; i++) {
        enqueue(s->q, dequeue(s->q));
    }
}

// Pop operation
int pop(struct Stack* s) {
    if (isEmpty(s->q)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return dequeue(s->q);
}

// Peek (top element)
int top(struct Stack* s) {
    if (isEmpty(s->q)) return -1;
    return s->q->arr[s->q->front];
}

// Check if stack is empty
int isEmptyStack(struct Stack* s) {
    return isEmpty(s->q);
}

// Driver code
int main() {
    struct Stack* s = createStack(5);

    push(s, 10);
    push(s, 20);
    push(s, 30);

    printf("Top element: %d\n", top(s)); // 30
    printf("Pop: %d\n", pop(s));         // 30
    printf("Pop: %d\n", pop(s));         // 20
    printf("Top element: %d\n", top(s)); // 10

    return 0;
}
