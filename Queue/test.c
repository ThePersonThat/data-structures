#include "queue.h"
#include <stdio.h>
#include <assert.h>


void test_queue()
{
    Queue* queue = create_queueN(5, true);
    char buffer[128];

    for(int i = 0; i < 10; i++)
        queue_push(queue, i);

    printf("Created auto growing queue from 0 to 9: %s\n", queue_to_string(queue, " %d ", buffer));

    printf("Pop 5 items: ");

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", queue_pop(queue));
    }

    printf("\n");

    Queue* clone = queue_clone(queue);

    printf("Created clone queue: %s\n", queue_to_string(queue, " %d ", buffer));

    assert(queue_compare(queue, clone) && "Error of comparing!\n");

    delete_queue(clone);
    delete_queue(queue);
}

int main()
{
    printf("Test is starting...\n\n");
    test_queue();
    printf("\nThe test was passed successfully\n");

    return 0;
}