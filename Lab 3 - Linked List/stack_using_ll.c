#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node
{
    int data;
    struct Node *next;
};

// Global top pointer for the stack
struct Node *top = NULL;

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Push operation (Insert at Beginning)
void push(int data)
{
    struct Node *newNode = createNode(data);
    newNode->next = top;
    top = newNode;
    printf("%d pushed to stack\n", data);
}

// Pop operation (Delete from Beginning)
void pop()
{
    if (top == NULL)
    {
        printf("Stack Underflow! (Stack is empty)\n");
        return;
    }
    struct Node *temp = top;
    printf("Popped: %d\n", temp->data);
    top = top->next;
    free(temp);
}

// Peek operation (View the top element)
void peek()
{
    if (top == NULL)
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element: %d\n", top->data);
}

// Traverse stack (print all elements)
void display()
{
    if (top == NULL)
    {
        printf("Stack is empty!\n");
        return;
    }
    struct Node *temp = top;
    printf("Stack (Top -> Bottom): ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Menu-driven main function
int main()
{
    int choice, data;
    while (1)
    {
        printf("\n--- Stack Using Linked List Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to push: ");
            scanf("%d", &data);
            push(data);
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            display();
            break;
        case 5:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
