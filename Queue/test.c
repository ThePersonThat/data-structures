#include "queue.h"

#include <stdio.h>

int main()
{
    Queue* q = create_queue(false);

    queue_push(q, 10);
    queue_push(q, 20);

    printf("%d\n", queue_pop(q));
    delete_queue(q);
}