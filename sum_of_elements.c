#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct LQueue {
    int front, rear, size;
    int *arr;
};

struct LQueue* createQueue(int capacity) {
    struct LQueue* queue = (struct LQueue*)malloc(sizeof(struct LQueue));
    queue->size = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->arr = (int*)malloc(capacity * sizeof(int));
    return queue;
}

int isFull(struct LQueue* queue) {
    return queue->rear == queue->size - 1;
}

int isEmpty(struct LQueue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

void enqueue(struct LQueue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full! Cannot insert %d\n", value);
        return;
    }
    if (queue->front == -1) // First element
        queue->front = 0;
    queue->rear++;
    queue->arr[queue->rear] = value;
    printf("Inserted: %d\n", value);
}

void dequeue(struct LQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! Cannot delete.\n");
        return;
    }
    printf("Deleted: %d\n", queue->arr[queue->front]);
    queue->front++;
    if (queue->front > queue->rear) { // reset when empty
        queue->front = -1;
        queue->rear = -1;
    }
}

void display(struct LQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->arr[i]);
    }
    printf("\n");
}

int findMin(struct LQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No minimum value.\n");
        return INT_MAX;
    }
    int min = queue->arr[queue->front];
    for (int i = queue->front + 1; i <= queue->rear; i++) {
        if (queue->arr[i] < min)
            min = queue->arr[i];
    }
    return min;
}

int findMax(struct LQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! No maximum value.\n");
        return INT_MIN;
    }
    int max = queue->arr[queue->front];
    for (int i = queue->front + 1; i <= queue->rear; i++) {
        if (queue->arr[i] > max)
            max = queue->arr[i];
    }
    return max;
}

// New function to calculate sum of elements in the queue
int sumQueue(struct LQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! Sum is 0.\n");
        return 0;
    }
    int sum = 0;
    for (int i = queue->front; i <= queue->rear; i++) {
        sum += queue->arr[i];
    }
    return sum;
}

int main() {
    int capacity, choice, value;
    printf("Enter the size of the queue: ");
    scanf("%d", &capacity);
    struct LQueue* queue = createQueue(capacity);

    while (1) {
        printf("\n--- Queue Menu ---\n");
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display\n");
        printf("4. Find Minimum\n");
        printf("5. Find Maximum\n");
        printf("6. Sum of Elements\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
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
            case 4: {
                int min = findMin(queue);
                if (!isEmpty(queue))
                    printf("Minimum value in queue: %d\n", min);
                break;
            }
            case 5: {
                int max = findMax(queue);
                if (!isEmpty(queue))
                    printf("Maximum value in queue: %d\n", max);
                break;
            }
            case 6: {
                int total = sumQueue(queue);
                if (!isEmpty(queue))
                    printf("Sum of elements in queue: %d\n", total);
                break;
            }
            case 7:
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
