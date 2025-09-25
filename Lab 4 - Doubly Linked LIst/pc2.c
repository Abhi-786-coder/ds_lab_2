#include <stdio.h>
#include <stdlib.h>

// Node structure for DLL
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

// Insert node in sorted order into DLL
void sortedInsert(struct Node** head, int data) {
    struct Node* node = newNode(data);
    if (*head == NULL) { // empty list
        *head = node;
        return;
    }

    struct Node* temp = *head;
    while (temp != NULL && temp->data < data)
        temp = temp->next;

    if (temp == *head) { // insert at beginning
        node->next = *head;
        (*head)->prev = node;
        *head = node;
    } else if (temp == NULL) { // insert at end
        struct Node* tail = *head;
        while (tail->next != NULL)
            tail = tail->next;
        tail->next = node;
        node->prev = tail;
    } else { // insert in middle
        node->next = temp;
        node->prev = temp->prev;
        temp->prev->next = node;
        temp->prev = node;
    }
}

// Function to merge two sorted DLLs
struct Node* mergeDLL(struct Node* head1, struct Node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    struct Node* merged = NULL;
    if (head1->data < head2->data) {
        merged = head1;
        merged->next = mergeDLL(head1->next, head2);
        if (merged->next) merged->next->prev = merged;
        merged->prev = NULL;
    } else {
        merged = head2;
        merged->next = mergeDLL(head1, head2->next);
        if (merged->next) merged->next->prev = merged;
        merged->prev = NULL;
    }
    return merged;
}

// Print DLL
void printDLL(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Input DLL elements
struct Node* inputDLL() {
    struct Node* head = NULL;
    int val;
    printf("Enter elements (-1 to end): ");
    while (1) {
        scanf("%d", &val);
        if (val == -1) break;
        sortedInsert(&head, val);
    }
    return head;
}

int main() {
    printf("Input first list:\n");
    struct Node* head1 = inputDLL();

    printf("Input second list:\n");
    struct Node* head2 = inputDLL();

    if (head1 == NULL && head2 == NULL) {
    printf("Both lists are empty. Exiting program.\n");
    return 0;
   }
 
    printf("First sorted DLL: ");
    printDLL(head1);

    printf("Second sorted DLL: ");
    printDLL(head2);

    struct Node* mergedHead = mergeDLL(head1, head2);
    printf("Merged sorted DLL: ");
    printDLL(mergedHead);

  return 0;
}