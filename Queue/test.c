#include "queue.h"

#include <stdio.h>

int main()
{
    Queue* q = create_queue(false);

    queue_push(q, 10);
    queue_push(q, 20);
    queue_push(q, 40);

    char buffer[128];

    printf("%s\n", queue_to_string(q, " %d ", buffer));

    delete_queue(q);
}