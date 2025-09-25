#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* stack[100];
int top = -1;
void push(struct TreeNode* node) { stack[++top] = node; }
struct TreeNode* pop() { return stack[top--]; }

struct TreeNode* createNode(char value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

struct TreeNode* build(char postfix[]) {
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

int evaluate(struct TreeNode* root, int letters[]) {
    if (!root) return 0;
    if (!root->left && !root->right)
        return letters[root->data - 'a'];
    int left = evaluate(root->left, letters);
    int right = evaluate(root->right, letters);
    switch (root->data) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : 0;
        case '%': return right != 0 ? left % right : 0;
        default: return 0;
    }
}

int main() {
    char postfix[100];
    printf("Enter Postfix Expression: ");
    scanf("%s", postfix);

    int letters[26] = {0};
    int used[26] = {0};
    for (int i = 0; postfix[i]; i++)
        if (isalpha(postfix[i]))
            used[postfix[i] - 'a'] = 1;

    for (int i = 0; i < 26; i++) {
        if (used[i]) {
            printf("Enter value for %c: ", (char)('a'+i));
            scanf("%d", &letters[i]);
        }
    }

    struct TreeNode* root = build(postfix);
    int result = evaluate(root, letters);
    printf("\n\nEvaluated Result: %d\n", result);

    return 0;
}