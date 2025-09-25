#include <stdio.h>
#include <stdlib.h>

// Tree node structure
struct Node {
    int data;
    struct Node *left, *right;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* createTree() {
    int val;
    printf("Enter data (-1 for NULL): ");
    scanf("%d", &val);

    if (val == -1) return NULL;

    struct Node* root = newNode(val);

    printf("Enter left child of %d:\n", val);
    root->left = createTree();

    printf("Enter right child of %d:\n", val);
    root->right = createTree();

    return root;
}

struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct Node** array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (struct Node**)malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

int isEmpty(struct Queue* queue) { return (queue->size == 0); }
int isFull(struct Queue* queue) { return (queue->size == queue->capacity); }

void enqueue(struct Queue* queue, struct Node* item) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

struct Node* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) return NULL;
    struct Node* item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// Function to print right side view
void leftsideview(struct Node* root) {
    if (root == NULL) return;

    struct Queue* queue = createQueue(100);
    enqueue(queue, root);

    printf("Left Side View: ");

    while (!isEmpty(queue)) {
        int n = queue->size; // number of nodes at current level

        for (int i = 1; i <= n; i++) {
            struct Node* temp = dequeue(queue);

            // If it's the last node of this level → print
            if (i == 1) {
                printf("%d ", temp->data);
            }

            if (temp->left != NULL) enqueue(queue, temp->left);
            if (temp->right != NULL) enqueue(queue, temp->right);
        }
    }
}

int main() {
    printf("Create the binary tree:\n");
    struct Node* root = createTree();

    printf("\n");
    leftsideview(root);

    return 0;
}
