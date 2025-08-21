#include <stdio.h>
#include <stdlib.h>
struct LQueue
{
    int front, rear, size;
    int *arr;
};
// Function to create a queue using malloc
struct LQueue *createQueue(int capacity)
{
    struct LQueue *queue = (struct LQueue *)malloc(sizeof(struct LQueue));
    queue->size = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->arr = (int *)malloc(capacity * sizeof(int));
    return queue;
}
// Check if the queue is full
int isFull(struct LQueue *queue)
{
    return queue->rear == queue->size - 1;
}
// Check if the queue is empty
int isEmpty(struct LQueue *queue)
{
    return queue->front == -1 || queue->front > queue->rear;
}
// Insert element into the queue
void enqueue(struct LQueue *queue, int value)
{
    if (isFull(queue))
    {
        printf("Queue is full! Cannot insert %d\n", value);
        return;
    }
    if (queue->front == -1) // First element
        queue->front = 0;
    queue->rear++;
    queue->arr[queue->rear] = value;
    printf("Inserted: %d\n", value);
}
// Delete element from the queue
void dequeue(struct LQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty! Cannot delete.\n");
        return;
    }
    printf("Deleted: %d\n", queue->arr[queue->front]);
    queue->front++;
}
// Display the queue
void display(struct LQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++)
    {
        printf("%d ", queue->arr[i]);
    }
    printf("\n");
}

struct Stack{
    struct Queue*q;
    int capacity
};

//creating stack

struct Stack* createStack(int capacity)
{
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->q = createQueue(capacity);
    s->capacity = capacity;
    return s;
}

void push(struct Stack* s,int x)
{
    if(isFull(s->q))
    {
        printf("Stack is full\n");
        return;
    }

    enqueue(s->q,x);

    for (int i = 0; i < s->q->size - 1; i++) {
        enqueue(s->q, dequeue(s->q));
    }

}










int main()
{
    int capacity, choice, value;

    printf("Enter the size of the queue: ");
    scanf("%d", &capacity);
    struct LQueue *queue = createQueue(capacity);
    while (1)
    {
        printf("\n--- Queue Menu ---\n");
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            enqueue(queue, value);
            break;
        case 2:
            dequeue(queue);
            break;
        case 3:
            display(queue);
            break;
        case 4:
            free(queue->arr);
            free(queue);
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}