#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Node creation
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Sorted insert for DLL construction
struct Node* sortedInsert(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL)
        return newNode;
    if (data <= head->data) {
        newNode->next = head;
        head->prev = newNode;
        return newNode;
    }
    struct Node* curr = head;
    while (curr->next != NULL && curr->next->data < data)
        curr = curr->next;
    newNode->next = curr->next;
    if (curr->next)
        curr->next->prev = newNode;
    curr->next = newNode;
    newNode->prev = curr;
    return head;
}

// Create sorted DLL from user input
struct Node* inputSortedDLL() {
    int n, val;
    struct Node* head = NULL;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter %d elements in any order (will be inserted sorted):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        head = sortedInsert(head, val);
    }
    return head;
}

// Merge two sorted DLLs
struct Node* mergeSortedDLL(struct Node* h1, struct Node* h2) {
    struct Node* merged = NULL;
    struct Node* last = NULL;
    while (h1 && h2) {
        struct Node* newNode;
        if (h1->data <= h2->data) {
            newNode = createNode(h1->data);
            h1 = h1->next;
        } else {
            newNode = createNode(h2->data);
            h2 = h2->next;
        }
        if (!merged) {
            merged = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
    }
    while (h1) {
        struct Node* newNode = createNode(h1->data);
        if (!merged) { merged = newNode; last = newNode; }
        else { last->next = newNode; newNode->prev = last; last = newNode; }
        h1 = h1->next;
    }
    while (h2) {
        struct Node* newNode = createNode(h2->data);
        if (!merged) { merged = newNode; last = newNode; }
        else { last->next = newNode; newNode->prev = last; last = newNode; }
        h2 = h2->next;
    }
    return merged;
}

// Display DLL
void displayDLL(struct Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node* temp = head;
    printf("DLL: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    printf("Create First Sorted DLL:\n");
    struct Node* h1 = inputSortedDLL();
    printf("Create Second Sorted DLL:\n");
    struct Node* h2 = inputSortedDLL();
    printf("First Sorted DLL: ");
    displayDLL(h1);
    printf("Second Sorted DLL: ");
    displayDLL(h2);
    struct Node* merged = mergeSortedDLL(h1, h2);
    printf("Merged Sorted DLL: ");
    displayDLL(merged);
    return 0;
}
