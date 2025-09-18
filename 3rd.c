#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(char value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int evaluateExpressionTree(struct TreeNode* root, int operandValues[]) {
    if (!root) return 0;


    if (!root->left && !root->right) {
        return operandValues[root->data - 'a'];
    }

    int left_val = evaluateExpressionTree(root->left, operandValues);
    int right_val = evaluateExpressionTree(root->right, operandValues);

    switch (root->data) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return right_val != 0 ? left_val / right_val : 0;
        default: return 0;
    }
}

int main() {
 
    struct TreeNode* root = createNode('*');
    root->left = createNode('+');
    root->right = createNode('c');
    root->left->left = createNode('a');
    root->left->right = createNode('b');

    int operandValues[26] = {0};  
    operandValues['a' - 'a'] = 1; 
    operandValues['b' - 'a'] = 2; 
    operandValues['c' - 'a'] = 3; 

    int result = evaluateExpressionTree(root, operandValues);
    printf("Result: %d\n", result); 

    return 0;
}
