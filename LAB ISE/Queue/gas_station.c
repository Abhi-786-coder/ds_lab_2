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

// Peek front
int peek(struct LQueue *queue) {
    if (isEmpty(queue)) return -1;
    return queue->arr[queue->front];
}

// Gas Station Problem using Queue
int canCompleteCircuit(int gas[], int cost[], int n) {
    struct LQueue *queue = createQueue(n);
    for (int i = 0; i < n; i++) enqueue(queue, i); // enqueue all stations

    for (int start = 0; start < n; start++) {
        int tank = 0, completed = 1;
        int idx = start;
        for (int count = 0; count < n; count++) {
            tank += gas[idx] - cost[idx];
            if (tank < 0) {
                completed = 0;
                break;
            }
            idx = (idx + 1) % n; // move to next station
        }
        if (completed) {
            free(queue->arr);
            free(queue);
            return start;
        }
    }

    free(queue->arr);
    free(queue);
    return -1;
}

int main() {
    int n;
    printf("Enter number of stations: ");
    scanf("%d", &n);

    int gas[n], cost[n];
    printf("Enter gas array:\n");
    for (int i = 0; i < n; i++) scanf("%d", &gas[i]);

    printf("Enter cost array:\n");
    for (int i = 0; i < n; i++) scanf("%d", &cost[i]);

    int ans = canCompleteCircuit(gas, cost, n);
    if (ans != -1)
        printf("Starting station index: %d\n", ans);
    else
        printf("No possible starting station (-1)\n");

    return 0;
}
