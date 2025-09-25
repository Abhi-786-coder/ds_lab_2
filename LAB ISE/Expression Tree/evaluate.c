#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    char data;
    struct node *left, *right;
};

// Create a new node
struct node* newNode(char data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Stack for tree nodes
struct Stack {
    int top;
    unsigned capacity;
    struct node** array;
};

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

// Construct expression tree from postfix string
struct node* constructTree(char postfix[]) {
    struct Stack* stack = createStack(100);
    struct node *t, *t1, *t2;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        if (ch == ' ') continue;

        if (isdigit(ch)) {  // Operand (number)
            t = newNode(ch);
            push(stack, t);
        } else {  // Operator
            t = newNode(ch);

            t1 = pop(stack);
            t2 = pop(stack);

            t->right = t1;
            t->left = t2;

            push(stack, t);
        }
    }
    return pop(stack);
}

// Evaluate the expression tree
int eval(struct node* root) {
    if (!root) return 0;

    // If leaf node (operand)
    if (!root->left && !root->right)
        return root->data - '0'; // convert char digit to int

    // Evaluate left and right subtrees
    int left_val = eval(root->left);
    int right_val = eval(root->right);

    // Apply operator
    switch (root->data) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return left_val / right_val; // assume no divide by zero
    }
    return 0;
}

int main() {
    char postfix1[] = "23+5*";   // (2+3)*5 = 25
    char postfix2[] = "82/3-";   // (8/2)-3 = 1

    struct node* root1 = constructTree(postfix1);
    printf("Result of expression %s = %d\n", postfix1, eval(root1));

    struct node* root2 = constructTree(postfix2);
    printf("Result of expression %s = %d\n", postfix2, eval(root2));

    return 0;
}
