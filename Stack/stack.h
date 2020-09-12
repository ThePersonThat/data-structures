#include <stdbool.h>


typedef struct {
    void** array_stack;
    unsigned int size;
    unsigned int capacity;
    _Bool auto_growing;
} Stack;

Stack* create_stack(_Bool auto_growing); // create stack with default size
Stack* create_stackN(unsigned int size, _Bool auto_growing); // create stack with N size

void stack_push(Stack* stack, void* item); // add item to stack 
void* stack_pop(Stack* stack); // get item from stack

Stack* stack_clone(Stack* stack); // create copy stack
char* stack_to_string(Stack* stack, const char* format, char* buffer);

void stack_change_capacity(Stack* stack, unsigned int capacity); // realloc stack capacity 

static Stack* setup_stack(Stack* stack, unsigned int capacity, _Bool auto_growing);

extern void* stack_peek(Stack* stack); // get the top item without removing
extern _Bool stack_is_auto_growing(Stack* stack);
extern _Bool stack_is_full(Stack* stack);
extern void stack_remove_all(Stack* stack); // remove all the item from stack 
extern unsigned int stack_get_size(Stack* stack); // get stack size
extern unsigned int stack_get_capacity(Stack* stack); // get stack capacity
extern _Bool stack_is_empty(Stack* stack); // return true if stack size = 0

void delete_stack(Stack* stack);