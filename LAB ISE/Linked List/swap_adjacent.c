#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

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

// Insert at end
void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

// Swap adjacent elements
void swapPairs() {
    struct Node* temp = head;
    while (temp != NULL && temp->next != NULL) {
        int t = temp->data;
        temp->data = temp->next->data;
        temp->next->data = t;
        temp = temp->next->next;
    }
}

// Traverse list
void traverse() {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
        int n, value;
        printf("Enter number of elements: ");
        scanf("%d", &n);

        printf("Enter elements:\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &value);
            insertAtEnd(value);
        }

        printf("Original list: ");
        traverse();

        swapPairs();

        printf("After swapping adjacent elements: ");
        traverse();

        return 0;
}
