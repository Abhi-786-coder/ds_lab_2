#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Stack for tree nodes
struct TreeNode* stack[100];
int top = -1;
void push(struct TreeNode* node) { stack[++top] = node; }
struct TreeNode* pop() { return stack[top--]; }

// Create new node
struct TreeNode* createNode(char value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

// Build expression tree from postfix
struct TreeNode* buildExpressionTree(char postfix[]) {
    int n = strlen(postfix);
    for (int i = 0; i < n; i++) {
        char ch = postfix[i];
        if (islower(ch)) {
            push(createNode(ch));
        } else {
            struct TreeNode* node = createNode(ch);
            node->right = pop();
            node->left = pop();
            push(node);
        }
    }
    return pop();
}

// Evaluate expression tree
int evaluateExpressionTree(struct TreeNode* root, int operandValues[]) {
    if (!root) return 0;
    if (!root->left && !root->right)
        return operandValues[root->data - 'a'];
    int left_val = evaluateExpressionTree(root->left, operandValues);
    int right_val = evaluateExpressionTree(root->right, operandValues);
    switch (root->data) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return right_val != 0 ? left_val / right_val : 0;
        case '%': return right_val != 0 ? left_val % right_val : 0;
        default: return 0;
    }
}

// Tree print (rotated, optional)
void printTree(struct TreeNode* root, int space) {
    if (!root) return;
    space += 4;
    printTree(root->right, space);
    printf("\n");
    for (int i = 4; i < space; i++) printf(" ");
    printf("%c\n", root->data);
    printTree(root->left, space);
}

// Free tree memory
void freeTree(struct TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char postfix[100];
    printf("Enter Postfix Expression: ");
    scanf("%s", postfix);

    int operandValues[26] = {0};
    int used[26] = {0};
    // Find all operands in postfix
    for (int i = 0; postfix[i]; i++)
        if (islower(postfix[i]))
            used[postfix[i] - 'a'] = 1;
    // Take their values from user
    for (int i = 0; i < 26; i++) {
        if (used[i]) {
            printf("Enter value for %c: ", (char)('a'+i));
            scanf("%d", &operandValues[i]);
        }
    }

    struct TreeNode* root = buildExpressionTree(postfix);
    printf("\nConstructed Expression Tree (rotated):\n");
    printTree(root, 0);

    int result = evaluateExpressionTree(root, operandValues);
    printf("\n\nEvaluated Result: %d\n", result);

    freeTree(root);
    return 0;
}
