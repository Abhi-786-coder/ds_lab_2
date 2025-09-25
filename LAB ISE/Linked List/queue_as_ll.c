#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

struct Node* front = NULL; // points to first element
struct Node* rear = NULL;  // points to last element

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Enqueue (insert at end)
void enqueue(int data) {
    struct Node* newNode = createNode(data);
    if (rear == NULL) { // empty queue
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("Enqueued: %d\n", data);
}

// Dequeue (delete from beginning)
void dequeue() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    struct Node* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL; // queue became empty
    printf("Dequeued: %d\n", temp->data);
    free(temp);
}

// Peek front
void peek() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Front element: %d\n", front->data);
}

// Traverse queue
void traverse() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    struct Node* temp = front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    int n, value, op;
    printf("Enter number of operations: ");
    scanf("%d", &n);

    printf("\nOperations:\n");
    printf("1 x -> Enqueue x\n");
    printf("2   -> Dequeue\n");
    printf("3   -> Front element\n");
    printf("4   -> Traverse queue\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &value);
            enqueue(value);
        } else if (op == 2) {
            dequeue();
        } else if (op == 3) {
            peek();
        } else if (op == 4) {
            traverse();
        } else {
            printf("Invalid operation!\n");
        }
    }

    return 0;
}
