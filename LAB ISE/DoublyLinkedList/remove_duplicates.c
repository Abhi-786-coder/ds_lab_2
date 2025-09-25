#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;

// Create node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert at end
void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    if (!head) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// Traverse
void traverse() {
    struct Node* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Remove duplicates
void removeDuplicates() {
    if (!head) return;

    struct Node* current = head;

    while (current && current->next) {
        if (current->data == current->next->data) {
            struct Node* duplicate = current->next;
            current->next = duplicate->next;
            if (duplicate->next)
                duplicate->next->prev = current;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
}

// Main
int main() {
    int n, val;
    printf("Enter number of elements (sorted list): ");
    scanf("%d", &n);

    printf("Enter elements in sorted order:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertAtEnd(val);
    }

    printf("Original list: ");
    traverse();

    removeDuplicates();

    printf("List after removing duplicates: ");
    traverse();

    return 0;
}
