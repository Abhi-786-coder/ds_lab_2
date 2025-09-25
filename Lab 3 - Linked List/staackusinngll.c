#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* top = NULL;

// Check if stack is empty
int isEmpty() {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return 1;
    }
    printf("Stack is not empty.\n");
    return 0;
}

// Check if stack is full (heap overflow test)
int isFull() {
    struct Node* testNode = (struct Node*)malloc(sizeof(struct Node));
    if (testNode == NULL) {
        printf("Stack is full! No space left in memory.\n");
        return 1;
    }
    free(testNode);
    printf("Stack has free space.\n");
    return 0;
}

void push(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Push failed! Memory not available.\n");
        return;
    }
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    printf("Pushed %d into stack.\n", value);
}

void pop() {
    if (top == NULL) {
        printf("Nothing to pop, stack is empty!\n");
        return;
    }
    int popped = top->data;
    struct Node* temp = top;
    top = top->next;
    free(temp);
    printf("Popped %d from stack.\n", popped);
}

void peek() {
    if (top == NULL) {
        printf("Stack is empty, nothing at top.\n");
        return;
    }
    printf("Top element is: %d\n", top->data);
}

void display() {
    if (top == NULL) {
        printf("Stack is empty, no elements to show.\n");
        return;
    }
    struct Node* temp = top;
    printf("Stack (top to bottom): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n==== Stack Menu ====\n");
        printf("1. Push element\n");
        printf("2. Pop element\n");
        printf("3. Peek top element\n");
        printf("4. Display stack\n");
        printf("5. Check if empty\n");
        printf("6. Check if full\n");
        printf("7. Exit program\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                isEmpty();
                break;

            case 6:
                isFull();
                break;

            case 7:
                printf("Goodbye! Program terminated.\n");
                exit(0);

            default:
                printf("Invalid option, please try again.\n");
        }
    }
    return 0;
}