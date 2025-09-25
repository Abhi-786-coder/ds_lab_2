#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// Function to create the binary tree
struct node *create() {
    struct node *temp;
    int data, choice;
    temp = (struct node *)malloc(sizeof(struct node));

    printf("\n Press 0 to exit");
    printf("\nPress 1 for new node");
    printf("\n Enter your choice : ");
    scanf("%d", &choice);

    if (choice == 0) {
        return NULL;
    } else {
        printf("Enter the data: ");
        scanf("%d", &data);
        temp->data = data;

        printf("\n Enter the left child of %d", data);
        temp->left = create();

        printf("\n Enter the right child of %d", data);
        temp->right = create();

        return temp;
    }
}

// Function to print inorder traversal
void printInorder(struct node* node) {
    if (node == NULL)
        return;

    printInorder(node->left);
    printf("%d ", node->data);
    printInorder(node->right);
}

// Function to calculate sum of root-to-leaf numbers
int sumRootToLeaf(struct node* node, int currentNumber) {
    if (node == NULL)
        return 0;

    // Update the number along this path
    currentNumber = currentNumber * 10 + node->data;

    // If it's a leaf node, return the number
    if (node->left == NULL && node->right == NULL)
        return currentNumber;

    // Recursively sum for left and right subtrees
    return sumRootToLeaf(node->left, currentNumber) + sumRootToLeaf(node->right, currentNumber);
}

int main() {
    struct node *root;
    printf("Creating tree\n");
    root = create();

    printf("\nInorder traversal of binary tree is \n");
    printInorder(root);

    int totalSum = sumRootToLeaf(root, 0);
    printf("\n\nSum of all root-to-leaf numbers = %d\n", totalSum);

    return 0;
}
