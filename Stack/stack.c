#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_DEFAULT_SIZE 16


Stack* setup_stack(Stack* stack, unsigned int capacity, _Bool auto_growing)
{
    if(stack == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }
    
    stack->size = 0;
    stack->capacity = capacity;
    stack->auto_growing = auto_growing;
    stack->array_stack = malloc(sizeof(void *) * capacity);

    if(stack->array_stack == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    return stack;
}

Stack* create_stack(_Bool auto_growing)
{
    Stack* stack = malloc(sizeof(Stack));

    return setup_stack(stack, INITIAL_DEFAULT_SIZE, auto_growing);
}

Stack* create_stackN(unsigned int size, _Bool auto_growing)
{
    Stack* stack = malloc(sizeof(Stack));

    return setup_stack(stack, size, auto_growing);
}

void stack_push(Stack* stack, void* item)
{
    if(stack->size == stack->capacity)
    {
        if(stack->auto_growing == true)
            stack_change_capacity(stack, stack->capacity * 2);
        else 
        {
            fprintf(stderr, "Error! Stack is full\n");
            return;
        }
    }

    stack->array_stack[stack->size++] = item;
}

void* stack_pop(Stack* stack)
{
    if(stack->size == 0)
        return NULL;

    return stack->array_stack[--stack->size];
}

Stack* stack_clone(Stack* stack)
{
    Stack* new_stack = create_stackN(stack->capacity, stack->auto_growing);

    memcpy(new_stack->array_stack, stack->array_stack, sizeof(void *) * stack->size);

    new_stack->size = stack->size;

    return stack;
}

char* stack_to_string(Stack* stack, const char* format, char* buffer)
{
    sprintf(buffer, "Stack: [ ");
    int offset = strlen(buffer);

    for(int i = 0; i < stack->size; i++)
    {
        sprintf(buffer + offset, format, stack->array_stack[i]);
        offset += strlen(buffer) - offset;
    }

    sprintf(buffer + offset, " ]\0");

    return buffer;
}

_Bool stack_compare(Stack* first, Stack* second)
{
    if(first->size != second->size)
        return false;

    for(int i = 0; i < first->size; i++)
    {
        if(first->array_stack[i] == second->array_stack[i])
            continue;
        else 
            return false;
    }

    return true;
}


void stack_change_capacity(Stack* stack, unsigned int capacity)
{
    if(capacity < stack->size)
    {
        fprintf(stderr, "Error! Capacity can't be less then size\n");
        return;
    }

    stack->array_stack = realloc(stack->array_stack, sizeof(void *) * capacity);
    stack->capacity = capacity;
}

void delete_stack(Stack* stack)
{
    free(stack->array_stack);
    free(stack);
}


inline void* stack_peek(Stack* stack)
{
    return stack->size == 0 ? NULL : stack->array_stack[0];
}

inline _Bool stack_is_full(Stack* stack)
{
    return stack->size == stack->capacity ? true : false;
}

inline void stack_remove_all(Stack* stack)
{   
    stack->size = 0;
}

inline unsigned int stack_get_size(Stack* stack)
{
    return stack->size;
}

inline unsigned int stack_get_capacity(Stack* stack)
{
    return stack->capacity;
}

inline _Bool stack_is_empty(Stack* stack)
{
    return stack->size == 0 ? true : false;
}

inline _Bool stack_is_auto_growing(Stack* stack)
{
    return stack->auto_growing;
}