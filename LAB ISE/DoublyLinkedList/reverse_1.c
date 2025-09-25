
// By value swapping

#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
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
    newNode->prev = NULL;
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
    newNode->prev = temp;
}

// Reverse by swapping data
void reverseData() {
    if (head == NULL || head->next == NULL) return; // empty or single node
    
    struct Node* start = head;
    struct Node* end = head;
    
    // Find the last node
    while (end->next != NULL) {
        end = end->next;
    }
    
    // Swap data from both ends moving towards center
    while (start != end && start->prev != end) {
        // Swap data
        int temp = start->data;
        start->data = end->data;
        end->data = temp;
        
        // Move pointers
        start = start->next;
        end = end->prev;
    }
}

// Traverse list forward
void traverse() {
    struct Node* temp = head;
    printf("Doubly Linked List: ");
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

    printf("Reversing list by swapping data...\n");
    reverseData();

    printf("Reversed list: ");
    traverse();

    return 0;
}
