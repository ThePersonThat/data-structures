#ifndef STACK_H
#define STACK_H

#include "../LinkedLIst/linkedlist.h"
#include <stdbool.h>

typedef void (*destroyFunction) (void *); 
typedef _Bool (*equalsFunction) (void*, void*);
typedef void (*to_stringFunction) (void *);
typedef void (*cloneFunction) (void*, void*);

typedef struct {
    LinkedList* list;
    unsigned int size;
    unsigned int capacity;
    _Bool auto_growing;
} Stack;

Stack* create_stack( _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone); // create stack with default size
Stack* create_stackN(unsigned int size,  _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone); // create stack with N size

void stack_push(Stack* stack, const void* item); // add item to stack 
void* stack_pop(Stack* stack); // get item from stack

Stack* stack_clone(const Stack* stack); // create copy stack
extern void stack_to_string(const Stack* stack);

extern _Bool stack_compare(const Stack* first, const Stack* second);
extern void stack_change_capacity(Stack* stack, unsigned int capacity); // realloc stack capacity 

static Stack* setup_stack(Stack* stack, unsigned int capacity, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);

extern void* stack_peek(const Stack* stack); // get the top item without removing
extern _Bool stack_is_auto_growing(const Stack* stack);
extern _Bool stack_is_full(const Stack* stack);
extern unsigned int stack_get_size(const Stack* stack); // get stack size
extern unsigned int stack_get_capacity(const Stack* stack); // get stack capacity
extern _Bool stack_is_empty(const Stack* stack); // return true if stack size = 0

void delete_stack(Stack* stack);

#endif