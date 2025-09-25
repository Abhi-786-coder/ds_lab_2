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

// Length of list
int length() {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Rotate right by K nodes
void rotateRight(int K) {
    if (!head || !head->next) return; // empty or single node

    int len = length();
    K = K % len;
    if (K == 0) return; // no rotation needed

    // Traverse to new tail: (len-K)th node
    struct Node* newTail = head;
    for (int i = 1; i < len - K; i++) newTail = newTail->next;

    struct Node* newHead = newTail->next;

    // Break the list
    newTail->next = NULL;
    newHead->prev = NULL;

    // Find old tail
    struct Node* oldTail = newHead;
    while (oldTail->next != NULL) oldTail = oldTail->next;

    // Connect old tail to old head
    oldTail->next = head;
    head->prev = oldTail;

    // Update head
    head = newHead;
}

// Main
int main() {
    int n, val, K;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertAtEnd(val);
    }

    printf("Original list: ");
    traverse();

    printf("Enter K to rotate right: ");
    scanf("%d", &K);

    rotateRight(K);

    printf("List after rotation: ");
    traverse();

    return 0;
}
