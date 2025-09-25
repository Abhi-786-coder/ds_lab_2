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

// Enqueue
void enqueue(struct LQueue *queue, int value) {
    if (queue->rear == queue->size - 1) return;
    if (queue->front == -1) queue->front = 0;
    queue->arr[++queue->rear] = value;
}

// Dequeue
int dequeue(struct LQueue *queue) {
    if (isEmpty(queue)) return -1;
    return queue->arr[queue->front++];
}

// Josephus Problem using Queue
int josephus(int n, int k) {
    struct LQueue *queue = createQueue(n);

    // Fill queue with people [0, 1, 2, ..., n-1]
    for (int i = 0; i < n; i++) {
        enqueue(queue, i);
    }

    // Process elimination
    while (queue->rear - queue->front + 1 > 1) {
        // Skip k-1 people (move front to rear)
        for (int i = 1; i < k; i++) {
            int temp = dequeue(queue);
            enqueue(queue, temp);
        }
        // Eliminate the k-th person
        int eliminated = dequeue(queue);
        printf("Eliminated: %d\n", eliminated);
    }

    int survivor = dequeue(queue);
    free(queue->arr);
    free(queue);
    return survivor;
}

// ---------------- Main ----------------
int main() {
    int n, k;
    printf("Enter number of people (n): ");
    scanf("%d", &n);
    printf("Enter step count (k): ");
    scanf("%d", &k);

    int survivor = josephus(n, k);
    printf("The survivor is at position: %d\n", survivor);

    return 0;
}
