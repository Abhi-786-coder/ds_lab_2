#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Stack
{
    int top;
    unsigned capacity;
    int *array;
};

struct Stack *createstack(unsigned size)
{
    //initialising the stack of type struct stack using malloc
    struct Stack *stack = (struct Stack*)(malloc(sizeof(struct Stack)));
    // always put check to see if the stack was formed
    if(!stack)
    {
        return NULL;
    }
    stack->capacity = size;
    stack->top = -1;
    //initialise the array
    stack->array = (int*)malloc(stack->capacity*sizeof(int));  
    //check if the array is formed
    if(!stack->array)
    {
    // as it is useless to keep a stack without it having a array so just boom boom the array
        free(stack);
        free(stack);
        return NULL;
    }
    return stack;
}
