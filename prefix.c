#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};


struct TreeNode* createNode(char value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

struct TreeNode* buildExpressionTree(char postfix[]) {
    struct TreeNode* stack[100];
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        struct TreeNode* newNode = createNode(postfix[i]);
        if (isalnum(postfix[i])) {
            stack[++top] = newNode;
        } else if (isOperator(postfix[i])) {
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }
    return stack[top];
}

void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        if (isOperator(root->data)) printf("(");
        inOrderTraversal(root->left);
        printf("%c", root->data);
        inOrderTraversal(root->right);
        if (isOperator(root->data)) printf(")");
    }
}

void freeExpressionTree(struct TreeNode* root) {
    if (root != NULL) {
        freeExpressionTree(root->left);
        freeExpressionTree(root->right);
        free(root);
    }
}

int main() {
    char postfixExpression[100];
    printf("Enter a postfix expression: ");
    scanf("%s", postfixExpression);

    struct TreeNode* root = buildExpressionTree(postfixExpression);

    printf("In-order Traversal of the Expression Tree: ");
    inOrderTraversal(root);
    printf("\n");

    freeExpressionTree(root);
    return 0;
}
