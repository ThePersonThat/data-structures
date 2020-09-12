#include <stdbool.h>


typedef struct {
    unsigned int size;
    unsigned int capacity;
    _Bool auto_growing;
    void** array_stack;
} Stack;

Stack* create_stack(); // create stack with default size
Stack* create_stackN(unsigned int size); // create stack with N size

void stack_push(Stack* stack, void* item); // add item to stack 
void* stack_pop(Stack* stack); // get item from stack

inline void remove_All(Stack* stack); // remove all the item from stack 
inline unsigned int stack_get_size(Stack* stack); // get stack size
inline unsigned int stack_get_capacity(Stack* stack); // get stack capacity
inline _Bool stack_is_empty(Stack* stack); // return true if stack size = 0

void delete_stack(Stack* stack);