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

// Check palindrome
int isPalindrome() {
    if (!head) return 1; // empty list is palindrome

    struct Node* front = head;
    struct Node* rear = head;

    // Move rear to last node
    while (rear->next != NULL) rear = rear->next;

    // Compare front and rear
    while (front != rear && front->prev != rear) {
        if (front->data != rear->data)
            return 0; // Not a palindrome
        front = front->next;
        rear = rear->prev;
    }

    return 1; // Palindrome
}

// Main
int main() {
    int n, val;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertAtEnd(val);
    }

    traverse();

    if (isPalindrome())
        printf("The list is a palindrome.\n");
    else
        printf("The list is NOT a palindrome.\n");

    return 0;
}
