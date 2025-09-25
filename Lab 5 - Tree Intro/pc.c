#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node {
    int data;
    struct node *left, *right;
};

// Function to create a new node interactively
struct node* create() {
    int choice, data;
    printf("\nPress 0 to exit (no node)");
    printf("\nPress 1 for new node");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 0) {
        return NULL;
    }

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    printf("Enter the data: ");
    scanf("%d", &data);
    temp->data = data;

    printf("\nEnter the left child of %d", data);
    temp->left = create();

    printf("\nEnter the right child of %d", data);
    temp->right = create();

    return temp;
}

// Stack for zigzag
struct Stack {
    int top, cap;
    struct node** arr;
};

struct Stack* createStack(int cap) {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->cap = cap;
    s->top = -1;
    s->arr = (struct node*)malloc(cap * sizeof(struct node));
    return s;
}

int isEmpty(struct Stack* s) { return s->top == -1; }

void push(struct Stack* s, struct node* n) {
    if (s->top == s->cap - 1) return;
    s->arr[++s->top] = n;
}

struct node* pop(struct Stack* s) {
    if (isEmpty(s)) return NULL;
    return s->arr[s->top--];
}

// Zigzag Traversal
void zigzagTraversal(struct node* root) {
    if (!root) return;

    struct Stack* curr = createStack(100);
    struct Stack* next = createStack(100);
    int ltr = 1;

    push(curr, root);

    while (!isEmpty(curr)) {
        struct node* temp = pop(curr);
        if (temp) {
            printf("%d ", temp->data);

            if (ltr) {
                if (temp->left) push(next, temp->left);
                if (temp->right) push(next, temp->right);
            } else {
                if (temp->right) push(next, temp->right);
                if (temp->left) push(next, temp->left);
            }
        }

        if (isEmpty(curr)) {
            ltr = !ltr;  // flip direction
            struct Stack* swap = curr;
            curr = next;
            next = swap;
            printf("\n");
        }
    }
}

// Driver code
int main() {
    struct node* root;
    printf("Creating tree...\n");
    root = create();

    printf("\nZigzag Level Order Traversal:\n");
    zigzagTraversal(root);

 return 0;
}