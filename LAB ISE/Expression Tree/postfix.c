#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for isalpha()

struct node {
    char data;
    struct node *left, *right;
};

// Create a new tree node
struct node* newNode(char data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Stack structure for tree nodes
struct Stack {
    int top;
    unsigned capacity;
    struct node** array;
};

// Create a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (struct node**)malloc(stack->capacity * sizeof(struct node*));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct node* item) {
    stack->array[++stack->top] = item;
}

struct node* pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return NULL;
}

// Build expression tree from postfix string
struct node* constructTree(char postfix[]) {
    struct Stack* stack = createStack(100);  // assume max length 100
    struct node *t, *t1, *t2;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        // Skip spaces
        if (ch == ' ')
            continue;

        // If operand, create node and push
        if (isalpha(ch)) {
            t = newNode(ch);
            push(stack, t);
        }
        // Operator
        else {
            t = newNode(ch);

            // Pop two top nodes
            t1 = pop(stack);  // right child
            t2 = pop(stack);  // left child

            t->right = t1;
            t->left = t2;

            // Push this subtree back
            push(stack, t);
        }
    }

    // Root of expression tree
    return pop(stack);
}

// Inorder traversal (will print the infix expression)
void inorder(struct node* root) {
    if (root) {
        if (root->left) printf("(");  // add brackets
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
        if (root->right) printf(")");
    }
}

int main() {
    char postfix1[] = "ab+c*";
    char postfix2[] = "ab*cd/+";

    struct node* root1 = constructTree(postfix1);
    printf("Inorder expression for %s is: ", postfix1);
    inorder(root1);
    printf("\n");

    struct node* root2 = constructTree(postfix2);
    printf("Inorder expression for %s is: ", postfix2);
    inorder(root2);
    printf("\n");

    return 0;
}
