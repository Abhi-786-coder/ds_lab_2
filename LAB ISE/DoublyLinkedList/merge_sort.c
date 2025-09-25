#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Create node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert at end
void insertAtEnd(struct Node** head_ref, int data) {
    struct Node* newNode = createNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct Node* temp = *head_ref;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// Traverse
void traverse(struct Node* head) {
    struct Node* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Merge two sorted doubly linked lists
struct Node* mergeSorted(struct Node* head1, struct Node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    struct Node* mergedHead = NULL;
    struct Node* mergedTail = NULL;

    // Initialize head
    if (head1->data < head2->data) {
        mergedHead = head1;
        head1 = head1->next;
    } else {
        mergedHead = head2;
        head2 = head2->next;
    }
    mergedHead->prev = NULL;
    mergedTail = mergedHead;

    // Merge remaining nodes
    while (head1 && head2) {
        if (head1->data < head2->data) {
            mergedTail->next = head1;
            head1->prev = mergedTail;
            mergedTail = head1;
            head1 = head1->next;
        } else {
            mergedTail->next = head2;
            head2->prev = mergedTail;
            mergedTail = head2;
            head2 = head2->next;
        }
    }

    // Attach remaining nodes
    if (head1) {
        mergedTail->next = head1;
        head1->prev = mergedTail;
    } else if (head2) {
        mergedTail->next = head2;
        head2->prev = mergedTail;
    }

    return mergedHead;
}

// Main
int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    struct Node* mergedHead = NULL;

    int n1, n2, val;

    printf("Enter number of elements in first sorted list: ");
    scanf("%d", &n1);
    printf("Enter elements in sorted order:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &val);
        insertAtEnd(&head1, val);
    }

    printf("Enter number of elements in second sorted list: ");
    scanf("%d", &n2);
    printf("Enter elements in sorted order:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &val);
        insertAtEnd(&head2, val);
    }

    printf("First list: ");
    traverse(head1);
    printf("Second list: ");
    traverse(head2);

    mergedHead = mergeSorted(head1, head2);

    printf("Merged sorted list: ");
    traverse(mergedHead);

    return 0;
}
