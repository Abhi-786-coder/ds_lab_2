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
struct Node* sortedInsert(struct Node* head, int data) {
    struct Node* node = newNode(data);
    if (head == NULL) {
        return node;
    }

    struct Node* temp = head;
    while (temp != NULL && temp->data < data)
        temp = temp->next;

    if (temp == head) { // insert at beginning
        node->next = head;
        head->prev = node;
        head = node;
    } else if (temp == NULL) { // insert at end
        struct Node* tail = head;
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
    return head;
}

// Insert node at end of DLL (used in iterative merge)
struct Node* insertEnd(struct Node* head, int data) {
    struct Node* node = newNode(data);
    if (head == NULL)
        return node;

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = node;
    node->prev = temp;
    return head;
}

// Iterative merge of two sorted DLLs
struct Node* mergeSortedDLL(struct Node* head1, struct Node* head2) {
    struct Node* head3 = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            head3 = insertEnd(head3, head1->data);
            head1 = head1->next;
        } else {
            head3 = insertEnd(head3, head2->data);
            head2 = head2->next;
        }
    }

    while (head1 != NULL) {
        head3 = insertEnd(head3, head1->data);
        head1 = head1->next;
    }

    while (head2 != NULL) {
        head3 = insertEnd(head3, head2->data);
        head2 = head2->next;
    }

    return head3;
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
        head = sortedInsert(head, val);
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

    struct Node* mergedHead = mergeSortedDLL(head1, head2);
    printf("Merged sorted DLL: ");
    printDLL(mergedHead);

    return 0;
}