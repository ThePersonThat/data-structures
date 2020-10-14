#include "priorityqueue.h"
#include <stdio.h>
#include <stdbool.h>

#define DATA(d) d
#define PRIORITY(p) p

typedef struct 
{
    int data;
    int priority;
} item_t;

_Bool compare(void* one, void* two)
{
    return ((item_t *)one)->priority > ((item_t *)two)->priority;
}

int main()
{
    PriorityQueue* q = create_prQueue(compare, false);

    item_t item[] = 
    {
        
        {
            DATA(40),
            PRIORITY(0)
        },
        {
            DATA(50),
            PRIORITY(2)
        },
        {
            DATA(10),
            PRIORITY(4)
        },
        {
            DATA(60),
            PRIORITY(0)
        }

    };

    prQueue_push(q, &item[0]);
    prQueue_push(q, &item[1]);
    prQueue_push(q, &item[2]);
    prQueue_push(q, &item[3]);

    for(int i = 0; q->size; i++)
        printf("%d\n", ((item_t *)prQueue_pop(q))->data);

    delete_prQueue(q);
    return 0;
}