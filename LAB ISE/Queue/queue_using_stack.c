#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    unsigned capacity;
    int *array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == (int)(stack->capacity - 1);
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (isFull(stack)) return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

// Queue using two stacks
struct Queue {
    struct Stack* s1;
    struct Stack* s2;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->s1 = createStack(capacity);
    q->s2 = createStack(capacity);
    return q;
}

void enqueue(struct Queue* q, int x) {
    push(q->s1, x);
}

int dequeue(struct Queue* q) {
    if (isEmpty(q->s1) && isEmpty(q->s2)) {
        return -1;
    }
    if (isEmpty(q->s2)) {
        while (!isEmpty(q->s1)) {
            push(q->s2, pop(q->s1));
        }
    }
    return pop(q->s2);
}

int main() {
    int n, val;
    printf("Enter number of elements to enqueue: ");
    scanf("%d", &n);

    struct Queue* q = createQueue(n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        enqueue(q, val);
    }

    printf("Dequeuing all elements:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", dequeue(q));
    }

    return 0;
}
