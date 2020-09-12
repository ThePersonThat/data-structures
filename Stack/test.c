#include "stack.h"
#include <stdio.h>

int main()
{
    Stack* stack = create_stack();

    char* strings[5] = {
        "hello", "bye", "world", "end", "begin"
    };

    for(int i = 0; i < 5; i++)
    {
        stack_push(stack, (void *)strings[i]);
    }

    for(int i = 0; i < 5; i++)
    {
        printf("%s\n", stack_pop(stack));
    }

    delete_stack(stack);
    return 0;
}