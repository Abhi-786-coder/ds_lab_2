#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Enqueue index
void enqueue(struct LQueue *queue, int value) {
    if (queue->rear == queue->size - 1) return; // full
    if (queue->front == -1) queue->front = 0;
    queue->arr[++queue->rear] = value;
}

// Dequeue index
int dequeue(struct LQueue *queue) {
    if (isEmpty(queue)) return -1;
    return queue->arr[queue->front++];
}

// Peek front
int peek(struct LQueue *queue) {
    if (isEmpty(queue)) return -1;
    return queue->arr[queue->front];
}

// Function to find first unique character index
int firstUniqChar(char *s) {
    int freq[26] = {0};
    int len = strlen(s);

    struct LQueue *queue = createQueue(len);

    for (int i = 0; i < len; i++) {
        freq[s[i] - 'a']++;
        enqueue(queue, i); // store index in queue

        // remove all non-unique chars from front
        while (!isEmpty(queue) && freq[s[peek(queue)] - 'a'] > 1) {
            dequeue(queue);
        }
    }

    int result = isEmpty(queue) ? -1 : peek(queue);
    free(queue->arr);
    free(queue);
    return result;
}

int main() {
    char s[100];
    printf("Enter a string: ");
    scanf("%s", s);

    int index = firstUniqChar(s);
    if (index != -1)
        printf("First non-repeating character is '%c' at index %d\n", s[index], index);
    else
        printf("No non-repeating character found (-1)\n");

    return 0;
}
