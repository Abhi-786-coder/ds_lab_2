#include <stdio.h>
#include <stdlib.h>

// Structure for a doubly linked list node
struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Helper function to append a node to the end of a list
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = createNode(new_data);
    struct Node* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;
}

// Function to traverse and print the list
void traverse(struct Node* node) {
    if (node == NULL) {
        printf("List is empty!\n");
        return;
    }
    printf("NULL <-> ");
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Function to swap data of two nodes for sorting
void swap(struct Node *a, struct Node *b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Function to sort the doubly linked list using bubble sort
void sortList(struct Node *start) {
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    // Return if the list is empty
    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to merge two sorted DLLs by creating a new list
struct Node* mergeSortedLists(struct Node* h1, struct Node* h2) {
    struct Node* mergedHead = NULL;

    // Pointers to traverse the two input lists
    struct Node* p1 = h1;
    struct Node* p2 = h2;

    // While both lists have nodes, compare and append the smaller one
    while (p1 != NULL && p2 != NULL) {
        if (p1->data <= p2->data) {
            append(&mergedHead, p1->data);
            p1 = p1->next;
        } else {
            append(&mergedHead, p2->data);
            p2 = p2->next;
        }
    }

    // Append the remaining nodes from the first list, if any
    while (p1 != NULL) {
        append(&mergedHead, p1->data);
        p1 = p1->next;
    }

    // Append the remaining nodes from the second list, if any
    while (p2 != NULL) {
        append(&mergedHead, p2->data);
        p2 = p2->next;
    }

    return mergedHead;
}

// Function to free all nodes in a list to prevent memory leaks
void freeList(struct Node* node) {
    struct Node* temp;
    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
}

// Main function to drive the program
int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    int data;

    // --- Get User Input for Lists ---
    printf("--- First List ---\n");
    printf("Enter numbers (enter -1 to finish):\n");
    while (scanf("%d", &data) == 1 && data != -1) {
        append(&head1, data);
    }

    printf("\n--- Second List ---\n");
    printf("Enter numbers (enter -1 to finish):\n");
    while (scanf("%d", &data) == 1 && data != -1) {
        append(&head2, data);
    }

    printf("\n--- Initial Lists ---\n");
    printf("First list (unsorted):  ");
    traverse(head1);
    printf("Second list (unsorted): ");
    traverse(head2);

    // --- Sort the Lists ---
    sortList(head1);
    sortList(head2);

    printf("\n--- Sorted Lists ---\n");
    printf("First list (sorted):    ");
    traverse(head1);
    printf("Second list (sorted):   ");
    traverse(head2);

    // --- Merge the Lists ---
    struct Node* mergedHead = mergeSortedLists(head1, head2);
    printf("\n--- Final Merged List ---\n");
    traverse(mergedHead);

    // --- Clean up memory ---
    freeList(head1);
    freeList(head2);
    freeList(mergedHead);

    return 0;
}

