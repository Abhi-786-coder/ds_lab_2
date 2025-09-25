#include <stdio.h>
#include <stdlib.h>

// Define a node
struct node {
    int data;
    struct node *left, *right;
};

// Function to create a new node interactively
struct node* create() {
    struct node* temp;
    int data, choice;

    printf("\nPress 0 to exit (no node)");
    printf("\nPress 1 for new node");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 0) {
        return NULL;
    } else {
        temp = (struct node*)malloc(sizeof(struct node));
        printf("Enter the data: ");
        scanf("%d", &data);
        temp->data = data;

        printf("\nEnter the left child of %d", data);
        temp->left = create();

        printf("\nEnter the right child of %d", data);
        temp->right = create();

        return temp;
    }
}

// Stack structure for Zigzag Traversal
struct Stack {
    int top;
    int capacity;
    struct node* array; // Store nodes directly
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct node*)malloc(capacity * sizeof(struct node));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct node node) {
    if (stack->top == stack->capacity - 1) return;
    stack->array[++stack->top] = node; // Copy the node directly
}

struct node pop(struct Stack* stack) {
    if (isEmpty(stack)) return (struct node){0, NULL, NULL}; // Return an empty node
    return stack->array[stack->top--];
}

// Function to free a stack
void freeStack(struct Stack* stack) {
    if (stack) {
        free(stack->array);
        free(stack);
    }
}

// Zigzag Traversal using two stacks
void zigzagTraversal(struct node* root) {
    if (root == NULL) return;

    struct Stack* currentLevel = createStack(100);
    struct Stack* nextLevel = createStack(100);
    int leftToRight = 1;

    push(currentLevel, root);

    while (!isEmpty(currentLevel)) {
        struct node* temp = pop(currentLevel);
        if (temp) {
            printf("%d ", temp->data);

            if (leftToRight) {
                if (temp->left) push(nextLevel, temp->left);
                if (temp->right) push(nextLevel, temp->right);
            } else {
                if (temp->right) push(nextLevel, temp->right);
                if (temp->left) push(nextLevel, temp->left);
            }
        }

        if (isEmpty(currentLevel)) {
            printf("\n"); // Print a newline after finishing the current level
            leftToRight = !leftToRight;
            // Swap stacks
            struct Stack* tempStack = currentLevel;
            currentLevel = nextLevel;
            nextLevel = tempStack;
        }
    }

    freeStack(currentLevel);
    freeStack(nextLevel);
}

// Function to free the tree
void freeTree(struct node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Driver code
int main() {
    struct node* root;
    printf("Creating tree...\n");
    root = create();

    printf("\n\nZigzag Level Order Traversal:\n");
    zigzagTraversal(root);

    freeTree(root);

    return 0;
}
