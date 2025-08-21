#include <stdio.h>
#include <stdlib.h>

struct LQueue {
    int front, rear, size;
    int *arr;
};

struct LQueue* createQueue(int capacity) {
    struct LQueue* queue = (struct LQueue*)malloc(sizeof(struct LQueue));
    queue->size = capacity + 1;  // extra space for circular queue full/empty distinction
    queue->front = 0;
    queue->rear = 0;
    queue->arr = (int*)malloc(queue->size * sizeof(int));
    return queue;
}

int isEmpty(struct LQueue* queue) {
    return queue->front == queue->rear;
}

int isFull(struct LQueue* queue) {
    return (queue->rear + 1) % queue->size == queue->front;
}

void enqueue(struct LQueue* queue, int value) {
    if (isFull(queue)) {
        return;  // queue is full, ignore (should not happen here)
    }
    queue->arr[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->size;
}

int dequeue(struct LQueue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    int val = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    return val;
}

int queueSize(struct LQueue* queue) {
    if (queue->rear >= queue->front)
        return queue->rear - queue->front;
    else
        return queue->size - queue->front + queue->rear;
}

int josephus(int n, int k) {
    struct LQueue* queue = createQueue(n);
    // Enqueue people numbered 1 to n
    for (int i = 1; i <= n; i++) {
        enqueue(queue, i);
    }

    while (queueSize(queue) > 1) {
        // Skip k-1 people by dequeuing and enqueuing back
        for (int i = 0; i < k - 1; i++) {
            int temp = dequeue(queue);
            enqueue(queue, temp);
        }
        // Remove the k-th person
        int eliminated = dequeue(queue);
        printf("Person %d eliminated\n", eliminated);
    }
    int survivor = dequeue(queue);
    free(queue->arr);
    free(queue);
    return survivor;
}

int main() {
    int n, k;
    printf("Enter number of people (n): ");
    scanf("%d", &n);
    printf("Enter step count (k): ");
    scanf("%d", &k);

    int survivor = josephus(n, k);
    printf("Survivor is person %d\n", survivor);
    return 0;
}
