#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_DEFAULT_SIZE 16

Stack* create_stack()
{
    Stack* stack = malloc(sizeof(Stack));

    if(stack == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    stack->size = 0;
    stack->capacity = INITIAL_DEFAULT_SIZE;

    stack->array_stack = malloc(sizeof(void *) * INITIAL_DEFAULT_SIZE);

    if(stack->array_stack == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    return stack;
}

Stack* create_stackN(unsigned int size)
{
    Stack* stack = malloc(sizeof(Stack));

    if(stack == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    stack->size = 0;
    stack->capacity = size;

    stack->array_stack = malloc(sizeof(void *) * size);

    if(stack->array_stack == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    return stack;
}

void stack_push(Stack* stack, void* item)
{
    if(stack->size + 1 > stack->capacity)
    {
        /* */
    }

    stack->array_stack[stack->size++] = item;
}

void* stack_pop(Stack* stack)
{
    if(stack->size == 0)
        return NULL;

    return stack->array_stack[--stack->size];
}

void delete_stack(Stack* stack)
{
    free(stack->array_stack);
    free(stack);
}

extern inline void remove_All(Stack* stack)
{   
    stack->size = 0;
}

extern inline unsigned int stack_get_size(Stack* stack)
{
    return stack->size;
}

extern inline unsigned int stack_get_capacity(Stack* stack)
{
    return stack->capacity;
}

extern inline _Bool stack_is_empty(Stack* stack)
{
    return stack->size == 0 ? true : false;
}