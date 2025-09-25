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
    if (isFull(queue)) {
        printf("Queue overflow!\n");
        return;
    }
    if (queue->front == -1) queue->front = 0;
    queue->arr[++queue->rear] = value;
}

// Dequeue
int dequeue(struct LQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow!\n");
        return -1;
    }
    return queue->arr[queue->front++];
}

// Find min and max
void findMinMax(struct LQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    int min = queue->arr[queue->front];
    int max = queue->arr[queue->front];

    for (int i = queue->front; i <= queue->rear; i++) {
        if (queue->arr[i] < min) min = queue->arr[i];
        if (queue->arr[i] > max) max = queue->arr[i];
    }

    printf("Minimum element = %d\n", min);
    printf("Maximum element = %d\n", max);
}

// ---------------- Main ----------------
int main() {
    int capacity, n, value;
    printf("Enter queue size: ");
    scanf("%d", &capacity);

    struct LQueue *queue = createQueue(capacity);

    printf("Enter number of elements to insert: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(queue, value);
    }

    findMinMax(queue);

    free(queue->arr);
    free(queue);

    return 0;
}
