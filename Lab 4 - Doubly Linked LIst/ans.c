#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Global head pointer
struct Node* head = NULL;

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

// Insert at Beginning
void insertAtBeginning(int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
    if (head != NULL)
        head->prev = newNode;
    head = newNode;
}

// Insert at End
void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// Insert at Position
void insertAtPosition(int data, int pos) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    if (pos == 1) {
        insertAtBeginning(data);
        return;
    }
    struct Node* newNode = createNode(data);
    struct Node* temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;
    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = newNode;
    temp->next = newNode;
}

// Delete from Beginning
void deleteAtBeginning() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node* temp = head;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;
    printf("Deleted: %d\n", temp->data);
    free(temp);
}

// Delete from End
void deleteAtEnd() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    if (temp->prev != NULL)
        temp->prev->next = NULL;
    else
        head = NULL;
    printf("Deleted: %d\n", temp->data);
    free(temp);
}

// Delete at Position
void deleteAtPosition(int pos) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    struct Node* temp = head;
    for (int i = 1; temp != NULL && i < pos; i++)
        temp = temp->next;
    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    printf("Deleted: %d\n", temp->data);
    free(temp);
}

// Traverse forward
void traverse() {
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

// Traverse from any head pointer
void traverseFrom(struct Node* h) {
    if (h == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node* temp = h;
    printf("DLL: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Sorted insert for user-input sorted DLL creation
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

// Create sorted doubly linked list from user input
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

// Function for Case 8: User inputs two sorted DLLs, merges, and displays result
void mergeUserSortedDLLs() {
    printf("Create First Sorted DLL:\n");
    struct Node* h1 = inputSortedDLL();
    printf("Create Second Sorted DLL:\n");
    struct Node* h2 = inputSortedDLL();
    printf("First Sorted DLL: ");
    traverseFrom(h1);
    printf("Second Sorted DLL: ");
    traverseFrom(h2);
    struct Node* merged = mergeSortedDLL(h1, h2);
    printf("Merged Sorted DLL: ");
    traverseFrom(merged);
    // Free h1, h2, merged if desired
}

// Main menu-driven function
int main() {
    int choice, data, pos;
    while (1) {
        printf("\n--- Doubly Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Specific Position\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Delete at Specific Position\n");
        printf("7. Traverse\n");
        printf("8. Merge two sorted DLLs (user input)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            insertAtBeginning(data);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            insertAtEnd(data);
            break;
        case 3:
            printf("Enter data: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &pos);
            insertAtPosition(data, pos);
            break;
        case 4:
            deleteAtBeginning();
            break;
        case 5:
            deleteAtEnd();
            break;
        case 6:
            printf("Enter position: ");
            scanf("%d", &pos);
            deleteAtPosition(pos);
            break;
        case 7:
            traverse();
            break;
        case 8:
            mergeUserSortedDLLs();
            break;
        case 9:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
