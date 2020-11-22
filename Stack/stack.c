#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_DEFAULT_SIZE 16

Stack* setup_stack(Stack* stack, unsigned int capacity, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    if(stack == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }
    
    stack->size = 0; 
    stack->capacity = capacity;
    stack->auto_growing = auto_growing;
    stack->list = create_linkedList(object_size, destroy, to_string, equals, clone);

    return stack;
}

Stack* create_stack( _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    Stack* stack = malloc(sizeof(Stack));

    return setup_stack(stack, INITIAL_DEFAULT_SIZE, auto_growing, object_size, destroy, to_string, equals, clone);
}

Stack* create_stackN(unsigned int size,  _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    Stack* stack = malloc(sizeof(Stack));

    return setup_stack(stack, size, auto_growing, object_size, destroy, to_string, equals, clone);
}

void stack_push(Stack* stack, const void* item)
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

    linkedList_add_first(stack->list, item);
    stack->size++;
}

void* stack_pop(Stack* stack)
{
    stack->size--;
    return LinkedList_pop_front(stack->list);
}

Stack* stack_clone(const Stack* stack)
{
    Stack* new_stack = create_stackN(stack->capacity, stack->auto_growing, stack->list->object_size, stack->list->destroy, stack->list->to_string, 
            stack->list->equals, stack->list->clone);

    new_stack->size = stack->size;

    new_stack->list = linkedList_clone(stack->list);

    return new_stack;
}

inline void stack_to_string(const Stack* stack)
{
    linkedList_to_string(stack->list);
}

inline _Bool stack_compare(const Stack* first, const Stack* second)
{
    return linkedList_compare_list(first->list, second->list);
}


inline void stack_change_capacity(Stack* stack, unsigned int capacity)
{
    stack->capacity = capacity;
}

void delete_stack(Stack* stack)
{
    delete_linkedList(stack->list);
    free(stack);
}

inline void* stack_peek(const Stack* stack)
{
    return linkedList_get_first(stack->list);
}

inline _Bool stack_is_full(const Stack* stack)
{
    return stack->size == stack->capacity;
}

inline unsigned int stack_get_size(const Stack* stack)
{
    return stack->size;
}

inline unsigned int stack_get_capacity(const Stack* stack)
{
    return stack->capacity;
}

inline _Bool stack_is_empty(const Stack* stack)
{
    return stack->size == 0;
}

inline _Bool stack_is_auto_growing(const Stack* stack)
{
    return stack->auto_growing;
}