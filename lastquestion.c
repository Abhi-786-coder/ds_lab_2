#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(char value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to evaluate the expression tree
// operandValues is an array that maps 'a'-> operandValues[0], 'b'->operandValues[1], etc.
int evaluateExpressionTree(struct TreeNode* root, int operandValues[]) {
    if (!root) return 0;

    // if leaf node (operand)
    if (!root->left && !root->right) {
        return operandValues[root->data - 'a'];
    }

    // Evaluate left and right subtrees
    int left_val = evaluateExpressionTree(root->left, operandValues);
    int right_val = evaluateExpressionTree(root->right, operandValues);

    // Apply operator at root
    switch (root->data) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return right_val != 0 ? left_val / right_val : 0; // handle div by zero gracefully
        default: return 0;
    }
}

// Sample usage to test the function
int main() {
    // Example: expression ((a + b) * c)
    struct TreeNode* root = createNode('*');
    root->left = createNode('+');
    root->right = createNode('c');
    root->left->left = createNode('a');
    root->left->right = createNode('b');

    int operandValues[26] = {0};  // Initialize all to 0
    operandValues['a' - 'a'] = 1; // a = 1
    operandValues['b' - 'a'] = 2; // b = 2
    operandValues['c' - 'a'] = 3; // c = 3

    int result = evaluateExpressionTree(root, operandValues);
    printf("Result: %d\n", result); // Output: 9

    // Free memory (not shown here for brevity)
    return 0;
}
