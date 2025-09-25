#include <stdio.h>
#include <stdlib.h>

// Node structure for DLL
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data; 
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Insert node at end
struct Node* insertEnd(struct Node* head, int data) {
    struct Node* node = newNode(data);
    if (!head) return node;

    struct Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
    node->prev = temp;
    return head;
}

// Sort DLL using bubble sort algo
struct Node* sortList(struct Node* head) {
    if (!head) return NULL;

    int swapped;
    struct Node *ptr, *last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->data > ptr->next->data) {
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);

    return head;
}

// Merge two sorted DLLs 
struct Node* mergeSorted(struct Node* first, struct Node* second) {
    if (!first) return second;
    if (!second) return first;

    struct Node* mergedHead = NULL;
    struct Node* tail = NULL;

    while (first && second) {
        struct Node* temp;
        if (first->data <= second->data) {
            temp = first;
            first = first->next;
        } else {
            temp = second;
            second = second->next;
        }

        temp->prev = tail;
        temp->next = NULL;
        if (!mergedHead) {
            mergedHead = temp;
        } else {
            tail->next = temp;
        }
        tail = temp;
    }

    struct Node* remaining = (first) ? first : second;
    if (remaining) {
        remaining->prev = tail;
        if (tail) tail->next = remaining;
        else mergedHead = remaining; // in case mergedHead was NULL
    }

    return mergedHead;
}

// Print list forward
void printList(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node *a = NULL, *b = NULL;
    int n1, n2, val;

    // Input first list
    printf("Enter number of elements in first list: ");
    scanf("%d", &n1);
    if (n1 > 0) {
        printf("Enter %d elements:\n", n1);
        for (int i = 0; i < n1; i++) {
            scanf("%d", &val);
            a = insertEnd(a, val);
        }
    }

    // Input second list
    printf("Enter number of elements in second list: ");
    scanf("%d", &n2);
    if (n2 > 0) {
        printf("Enter %d elements:\n", n2);
        for (int i = 0; i < n2; i++) {
            scanf("%d", &val);
            b = insertEnd(b, val);
        }
    }

    // Check if both lists are empty
    if (n1 == 0 && n2 == 0) {
        printf("Both lists are empty.\n");
        return 0;
    }

    printf("Unsorted List A: ");
    printList(a);
    printf("Unsorted List B: ");
    printList(b);

    // Sort both lists
    a = sortList(a);
    b = sortList(b);

    printf("Sorted List A: ");
    printList(a);
    printf("Sorted List B: ");
    printList(b);

    // Merge them using iterative loop
    struct Node* merged = mergeSorted(a, b);

    printf("Merged Sorted List: ");
    printList(merged);

 return 0;
}