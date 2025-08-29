#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Stack
{
    int top;
    int capacity;
    int *array;
};

struct Stack *createStack(int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    if (!stack)
    {
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}
void push(struct Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}
int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        return INT_MIN;
    }
    return stack->array[stack->top--];
}

void freeStack(struct Stack *stack)
{
    free(stack->array);
    free(stack);
}

struct Queue
{
    struct Stack *stack1;
    struct Stack *stack2;
};

struct Queue *createQueue(int capacity)
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->stack1 = createStack(capacity);
    q->stack2 = createStack(capacity);
    return q;
};

void enqueue(struct Queue *q, int item)
{
    push(q->stack1, item);
    if (!isFull(q->stack1))
    {
        printf("%d enqueued\n", item);
    }
}

int dequeue(struct Queue *q)
{
    if (isEmpty(q->stack1) && isEmpty(q->stack2))
    {
        printf("Queue is empty\n");
        return -1;
    }

    if (isEmpty(q->stack2))
    {
        while (!isEmpty(q->stack1))
        {
            push(q->stack2, pop(q->stack1));
        }
    }
    return pop(q->stack2);
}

int peekQueue(struct Queue *q)
{
    if (isEmpty(q->stack1) && isEmpty(q->stack2))
    {
        printf("Queue is empty\n");
        return -1;
    }

    if (isEmpty(q->stack2))
    {
        while (!isEmpty(q->stack1))
        {
            push(q->stack2, pop(q->stack1));
        }
    }
    return q->stack2->array[q->stack2->top];
}

void freeQueue(struct Queue *q)
{
    freeStack(q->stack1);
    freeStack(q->stack2);
    free(q);
}

void display(struct Queue *q)
{
    if (isEmpty(q->stack1) && isEmpty(q->stack2))
    {
        printf("The queue is empty\n");
        return;
    }

    if (isEmpty(q->stack2))
    {
        while (!isEmpty(q->stack1))
        {
            push(q->stack2, pop(q->stack1));
        }
    }
    printf("Queue elements: ");
    for (int i = q->stack2->top; i >= 0; i--)
    {
        printf("%d ", q->stack2->array[i]);
    }
}

// Main
int main()
{
    int capacity, choice, value;
    printf("Enter the capacity of the queue: ");
    scanf("%d", &capacity);

    struct Queue *q = createQueue(capacity);

    while (choice != 4)
    {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Front\n");
        printf("4. Exit\n");
        printf("5. Display the Queue\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(q, value);
            break;
        case 2:
            value = dequeue(q);

            printf("%d dequeued\n", value);
            break;
        case 3:
            value = peekQueue(q);

            printf("Front element is %d\n", value);
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        case 5:
            display(q);
            break;
        }
    }

    freeQueue(q);
    return 0;
}