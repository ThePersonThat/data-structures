#include "priorityqueue.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

_Bool compare(void* one, void* two)
{
    return (int)one > (int)two;
}

void test_prQueue()
{
    char buffer[128];

    PriorityQueue* pq = create_prQueueN(compare, 3, true);

    for(int i = 0; i < 10; i++)
        prQueue_push(pq, rand() % 50);

     printf("Created auto growing priority queue from 0 to 10: %s\n", prQueue_to_string(pq, " %d ", buffer));

     printf("Pop 5 items: ");

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", prQueue_pop(pq));
    }

    PriorityQueue* clone = prQueue_clone(pq);
    printf("Created clone queue: %s\n", prQueue_to_string(pq, " %d ", buffer));

    assert(prQueue_compare(pq, clone) && "Error of comparing!\n");

    delete_prQueue(pq);
    delete_prQueue(clone);
}

int main()
{
    printf("Test is starting...\n\n");
    test_prQueue();
    printf("\nThe test was passed successfully\n");
}