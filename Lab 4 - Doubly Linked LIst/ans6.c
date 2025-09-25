#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void append(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void traverse(struct Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    printf("Head <-> ");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void swap(struct Node *node1, struct Node *node2) {
    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

void sortList(struct Node *head) {
    if (head == NULL) {
        return;
    }

    int wasSwapped;
    struct Node *current;
    struct Node *lastNode = NULL;

    do {
        wasSwapped = 0;
        current = head;

        while (current->next != lastNode) {
            if (current->data > current->next->data) {
                swap(current, current->next);
                wasSwapped = 1;
            }
            current = current->next;
        }
        lastNode = current;
    } while (wasSwapped);
}

struct Node* mergeSortedLists(struct Node* head1, struct Node* head2) {
    struct Node* newHead = NULL;
    struct Node* current1 = head1;
    struct Node* current2 = head2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->data < current2->data) {
            append(&newHead, current1->data);
            current1 = current1->next;
        } else {
            append(&newHead, current2->data);
            current2 = current2->next;
        }
    }

    while (current1 != NULL) {
        append(&newHead, current1->data);
        current1 = current1->next;
    }

    while (current2 != NULL) {
        append(&newHead, current2->data);
        current2 = current2->next;
    }

    return newHead;
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    int number;
    int size1, size2;

    printf("Enter details for the first list.\n");
    printf("Enter size: ");
    scanf("%d", &size1);
    printf("Enter %d numbers: ", size1);
    for (int i = 0; i < size1; i++) {
        scanf("%d", &number);
        append(&head1, number);
    }

    printf("\nEnter details for the second list.\n");
    printf("Enter size: ");
    scanf("%d", &size2);
    printf("Enter %d numbers: ", size2);
    for (int i = 0; i < size2; i++) {
        scanf("%d", &number);
        append(&head2, number);
    }

    printf("\nLists before sorting:\n");
    printf("First list:  ");
    traverse(head1);
    printf("Second list: ");
    traverse(head2);

    sortList(head1);
    sortList(head2);

    printf("\nLists after sorting:\n");
    printf("First list:  ");
    traverse(head1);
    printf("Second list: ");
    traverse(head2);

    struct Node* mergedHead = mergeSortedLists(head1, head2);
    printf("\nFinal merged list:\n");
    traverse(mergedHead);

    freeList(head1);
    freeList(head2);
    freeList(mergedHead);

    return 0;
}

