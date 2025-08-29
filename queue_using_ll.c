#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

// Global pointers for the queue
struct Node *front = NULL;
struct Node *rear = NULL;

// Function to create a new node
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Enqueue operation (insert at end/rear)
void enqueue(int data) {
    struct Node *newNode = createNode(data);
    if (rear == NULL) {
        // Queue is empty
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("%d enqueued to queue\n", data);
}

// Dequeue operation (delete from front)
void dequeue() {
    if (front == NULL) {
        printf("Queue Underflow! (Queue is empty)\n");
        return;
    }
    struct Node *temp = front;
    printf("Dequeued: %d\n", temp->data);
    front = front->next;
    if (front == NULL) {
        rear = NULL; // Queue became empty
    }
    free(temp);
}

// Peek/front operation
void peek() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Front element: %d\n", front->data);
}

// Traverse/Display queue
void display() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    struct Node *temp = front;
    printf("Queue (Front -> Rear): ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Menu-driven main function
int main() {
    int choice, data;
    while (1) {
        printf("\n--- Queue Using Linked List Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek (Front)\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter data to enqueue: ");
            scanf("%d", &data);
            enqueue(data);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            peek();
            break;
        case 4:
            display();
            break;
        case 5:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
