#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL; // top of stack

// Create a new node
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

// Push operation
void push(int data) {
    struct Node* newNode = createNode(data);
    newNode->next = top;
    top = newNode;
    printf("Pushed: %d\n", data);
}

// Pop operation
void pop() {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    struct Node* temp = top;
    top = top->next;
    printf("Popped: %d\n", temp->data);
    free(temp);
}

// Peek/Top
void peek() {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element: %d\n", top->data);
}

// Traverse stack
void traverse() {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    struct Node* temp = top;
    printf("Stack elements: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function using user input
int main() {
    int op, value;

    printf("Operations:\n");
    printf("1 x -> Push x\n");
    printf("2   -> Pop\n");
    printf("3   -> Top\n");
    printf("4   -> Traverse\n");
    printf("0   -> Exit\n");

    while (1) {
        printf("\nEnter operation: ");
        if (scanf("%d", &op) != 1) break; // EOF or bad input => stop

        switch (op) {
            case 1:
                printf("Enter the value: ");
                if (scanf("%d", &value) != 1) return 0;
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                traverse();
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                return 0; 
            default:
                printf("Invalid operation! Please try again.\n");
                break;
        }
    }
    return 0;
}