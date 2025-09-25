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

        struct Node
        {
            int data;
            struct Node *next;
        };

        struct Node *top = NULL;

        // Check if stack is empty
        int isEmpty()
        {
            return (top == NULL);
        }

        // Check if stack is full (heap overflow test)
        int isFull()
        {
            struct Node *testNode = (struct Node *)malloc(sizeof(struct Node));
            if (testNode == NULL)
                return 1; // no memory
            free(testNode);
            return 0; // memory available
        }

        void push(int value)
        {
            if (isFull())
            {
                printf("Stack Overflow! No memory available.\n");
                return;
            }
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = value;
            newNode->next = top;
            top = newNode;
            printf("%d pushed to stack\n", value);
        }

        int pop()
        {
            if (isEmpty())
            {
                printf("Stack Underflow! Cannot pop.\n");
                return -1;
            }
            int popped = top->data;
            struct Node *temp = top;
            top = top->next;
            free(temp);
            return popped;
        }

        int peek()
        {
            if (isEmpty())
            {
                printf("Stack is empty.\n");
                return -1;
            }
            return top->data;
        }

        void display()
        {
            if (isEmpty())
            {
                printf("Stack is empty.\n");
                return;
            }
            struct Node *temp = top;
            printf("Stack elements: ");
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
                printf("\n--- Stack Menu ---\n");

                printf("1. Push\n");
                printf("2. Pop\n");
                printf("3. Peek\n");
                printf("4. Display\n");
                printf("5. Check isEmpty\n");
                printf("6. Check isFull\n");
                printf("7. Exit\n");
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
                    if (isFull())
                        printf("Stack is full (no memory available).\n");
                    else
                        printf("Stack is not full.\n");
                    break;

                case 7:
                    printf("Exiting program.\n");
                    exit(0);

                default:
                    printf("Invalid choice! Try again.\n");
                }
            }
            return 0;
        }
