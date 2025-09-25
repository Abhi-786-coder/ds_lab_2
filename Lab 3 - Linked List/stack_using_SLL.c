#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

// pointer to keep track of top of the stack
struct Node *top = NULL;

// check if stack is empty
int isEmpty()
{
    return (top == NULL);
}

// push operation (insert at top)
void push(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = top; // link new node with previous top
    top = newNode;       // update top to new node
    printf("%d pushed to stack\n", value);
}

// pop operation (remove top element)
int pop()
{
    if (isEmpty())
    {
        printf("Stack is Empty(Underflow condition)! Cannot pop.\n");
        return -1;
    }
    int popped = top->data;
    struct Node *temp = top;
    top = top->next; // move top to next node
    free(temp);      // free memory of old top
    return popped;
}

// peek operation (view top element without removing it)
int peek()
{
    if (isEmpty())
    {
        printf("Stack is empty.\n");
        return -1;
    }
    return top->data;
}

// display all elements of stack
void display()
{
    if (isEmpty())
    {
        printf("Stack is empty.\n");
        return;
    }
    struct Node *temp = top;
    printf("Stack elements: top-> ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Stack Operations ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Check isEmpty\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(value);
            break;

        case 2:
            value = pop();
            if (value != -1)
                printf("Popped: %d\n", value);
            break;

        case 3:
            value = peek();
            if (value != -1)
                printf("Top element: %d\n", value);
            break;

        case 4:
            display();
            break;

        case 5:
            if (isEmpty())
                printf("Stack is empty.\n");
            else
                printf("Stack is not empty.\n");
            break;

        case 6:
            printf("Exiting program.\n");
            exit(0);
        }
    }
    return 0;
}
