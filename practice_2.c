 #include <stdio.h>
#include <stdlib.h>

struct LQueue {
    int front, rear, size;
    char *arr;
};

struct LQueue *createQueue(int capacity) {
    struct LQueue *queue = (struct LQueue *)malloc(sizeof(struct LQueue));
    queue->size = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->arr = (char *)malloc(capacity * sizeof(char));
    return queue;
}

int isFull(struct LQueue *queue) {
    return queue->rear == queue->size - 1;
}

int isEmpty(struct LQueue *queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

void enqueue(struct LQueue *queue, char value) {
    if (isFull(queue)) {
        printf("Queue is full! Cannot insert %c\n", value);
        return;
    }
    if (queue->front == -1) // First element
        queue->front = 0;
    queue->rear++;
    queue->arr[queue->rear] = value;
    printf("Inserted: %c\n", value);
}

void dequeue(struct LQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! Cannot delete.\n");
        return;
    }
    printf("Deleted: %c\n", queue->arr[queue->front]);
    queue->front++;
    if (queue->front > queue->rear) { // reset when empty
        queue->front = -1;
        queue->rear = -1;
    }
}

void display(struct LQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%c ", queue->arr[i]);
    }
    printf("\n");
}

// Function to find first non-repeating character
int first_non_repeating_char(struct LQueue *queue)
{
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }

    int freq[256] = {0}; // Frequency array for ASCII chars

    // Count frequencies
    for (int i = queue->front; i <= queue->rear; i++) {
        freq[queue->arr[i]]++;
    }

    // Find first char with freq == 1
    for (int i = queue->front; i <= queue->rear; i++) {
        if (freq[queue->arr[i]] == 1) {
            return queue->arr[i];
        }
    }

    return -1; // No non-repeating element found
}

int main() {
    int capacity, choice;
    char value;

    printf("Enter the size of the queue: ");
    scanf("%d", &capacity);
    struct LQueue *queue = createQueue(capacity);

    while (1) {
        printf("\n--- Queue Menu ---\n");
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("5. First Non-Repeating Character\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf(" %s", &value);  // take single character
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
        case 5: {
            int ans = first_non_repeating_char(queue);
            if (ans == -1)
                printf("No non-repeating character found!\n");
            else
                printf("First non-repeating character: %c\n", ans);
            break;
        }
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
