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

// Insert node into sorted DLL
struct Node* sortedInsert(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    if (data <= head->data) {
        newNode->next = head;
        head->prev = newNode;
        return newNode;
    }
    struct Node* curr = head;
    while (curr->next != NULL && curr->next->data < data) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    if (curr->next != NULL) {
        curr->next->prev = newNode;
    }
    curr->next = newNode;
    newNode->prev = curr;
    return head;
}
// to build sorted DLL from user input until -1
struct Node* buildSortedDLL() {
    struct Node* head = NULL;
    int val;
    printf("Enter elements (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &val);
        if (val == -1) break;
        head = sortedInsert(head, val);
    }
    return head;
}

// Merge two sorted DLLs 
struct Node* mergeSortedDLL(struct Node* h1, struct Node* h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    struct Node* mergedHead = NULL;

    
    if (h1->data <= h2->data) {
        mergedHead = h1;
        h1 = h1->next;
    } else {
        mergedHead = h2;
        h2 = h2->next;
    }
    mergedHead->prev = NULL;

    struct Node* current = mergedHead;

    while (h1 != NULL && h2 != NULL) {
        if (h1->data <= h2->data) {
            current->next = h1;
            h1->prev = current;
            h1 = h1->next;
        } else {
            current->next = h2;
            h2->prev = current;
            h2 = h2->next;
        }
        current = current->next;
    }

    if (h1 != NULL) {
        current->next = h1;
        h1->prev = current;
    }
    if (h2 != NULL) {
        current->next = h2;
        h2->prev = current;
    }
    return mergedHead;
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
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" <-> ");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    printf("Build First Sorted DLL:\n");
    struct Node* head1 = buildSortedDLL();

    printf("Build Second Sorted DLL:\n");
    struct Node* head2 = buildSortedDLL();

    printf("First Sorted DLL: ");
    displayDLL(head1);

    printf("Second Sorted DLL: ");
    displayDLL(head2);

    struct Node* mergedHead = mergeSortedDLL(head1, head2);

    printf("Merged Sorted DLL: ");
    displayDLL(mergedHead);

    return 0;
}
