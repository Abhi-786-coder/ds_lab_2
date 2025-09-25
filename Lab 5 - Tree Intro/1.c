#include <stdio.h>
#include <stdlib.h>

// Define the binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Utility function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Stack structure
struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

// Create a stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return stack;
}

// Check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push a node onto the stack
void push(struct Stack* stack, struct Node* node) {
    if (stack->top == stack->capacity - 1) return; // stack overflow check
    stack->array[++stack->top] = node;
}

// Pop a node from the stack
struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack)) return NULL;
    return stack->array[stack->top--];
}

// Zigzag traversal using two stacks
void zigzagTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Stack* currentLevel = createStack(100);
    struct Stack* nextLevel = createStack(100);

    int leftToRight = 1; // flag for direction

    push(currentLevel, root);

    while (!isEmpty(currentLevel)) {
        struct Node* node = pop(currentLevel);
        if (node) {
            printf("%d ", node->data);

            if (leftToRight) {
                if (node->left) push(nextLevel, node->left);
                if (node->right) push(nextLevel, node->right);
            } else {
                if (node->right) push(nextLevel, node->right);
                if (node->left) push(nextLevel, node->left);
            }
        }

        if (isEmpty(currentLevel)) {
            // switch stacks
            struct Stack* temp = currentLevel;
            currentLevel = nextLevel;
            nextLevel = temp;

            // change direction
            leftToRight = !leftToRight;
            printf("\n"); // new line for each level
        }
    }
}

// Driver code
int main() {
    struct Node* root = newNode(3);
    root->left = newNode(9);
    root->right = newNode(20);
    root->right->left = newNode(15);
    root->right->right = newNode(7);

    printf("Zigzag Level Order Traversal:\n");
    zigzagTraversal(root);

    return 0;
}
