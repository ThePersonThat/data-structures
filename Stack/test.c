#include "stack.h"
#include <stdio.h>
#include <assert.h>

void test_stack()
{
    Stack* stack = create_stackN(5, true);
    char buffer[128];

    for(int i = 0; i < 10; i++)
        stack_push(stack, (void *)i);

    printf("Created auto growing stack from 0 to 9: %s\n", stack_to_string(stack, " %d ", buffer));

    printf("Pop 4 items: ");

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", stack_pop(stack));
    }

    printf("\n");

    Stack* clone = stack_clone(stack);
    printf("Created clone stack: %s\n", stack_to_string(clone, " %d ", buffer));

    assert(stack_compare(stack, clone) && "Error of comparing!");

    delete_stack(clone);
    delete_stack(stack);
}

int main()
{
    printf("Test is starting...\n\n");
    test_stack();
    printf("\nThe test was passed successfully\n");

    return 0;
}