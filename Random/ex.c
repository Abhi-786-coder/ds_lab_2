#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <limits.h> // For INT_MIN
// A structure to represent a stack
struct Stack
{
    int top;
    unsigned capacity;
    int *array;
};
// Function to create a stack of given capacity.
struct Stack *createStack(unsigned capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    if (!stack)
    {
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    if (!stack->array)
    {
        free(stack);
        return NULL;
    }
    return stack;
}
int isFull(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}
void push(struct Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}
int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow\n");
        return INT_MIN;
    }
    return stack->array[stack->top--];
}
int peek(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return INT_MIN;
    }
    return stack->array[stack->top];
}
void freeStack(struct Stack *stack)
{
    if (stack)
    {
        free(stack->array);
        free(stack);
    }
}
int main()
{
    unsigned capacity;
    printf("Enter the capacity of the stack: ");
    scanf("%u", &capacity);
    struct Stack *stack = createStack(capacity);
    if (!stack)
    {
        printf("Failed to create stack.\n");
        return 1;
    }
    int choice, value;
    do
    {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Check if stack is empty\n");
        printf("5. Check if stack is full\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(stack, value);
            break;
        case 2:
            value = pop(stack);
            if (value != INT_MIN)
            {
                printf("%d popped from stack\n", value);
            }
            break;
        case 3:
            value = peek(stack);
            if (value != INT_MIN)
            {
                printf("Top element is %d\n", value);
            }
            break;
        case 4:
            if (isEmpty(stack))
            {
                printf("Stack is empty\n");
            }
            else
            {
                printf("Stack is not empty\n");
            }
            break;
        case 5:
            if (isFull(stack))
            {
                printf("Stack is full\n");
            }
            else
            {
                printf("Stack is not full\n");
            }
            break;
        case 6:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    freeStack(stack);
    return 0;
}