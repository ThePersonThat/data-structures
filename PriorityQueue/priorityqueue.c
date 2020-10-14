#include "priorityqueue.h"
#include <stdio.h>

#define INITIAL_DEFAULT_SIZE 16


PriorityQueue* setup_prQueue(CompareFunction func, unsigned int capacity, _Bool auto_growing)
{
    PriorityQueue* q = malloc(sizeof(PriorityQueue));

    if(q == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    q->auto_growing = auto_growing;
    q->capacity = capacity;
    q->size = 0;
    q->func = func;
    q->list = create_linkedList();

    return q;
}

void prQueue_push(PriorityQueue* q, void* item)
{
    if(q->size == 0)
    {
        q->size++;
        linkedList_add_last(q->list, item);
        return;
    }

    LinkedNode* node = q->list->head;

    int i = 0;
    while(!q->func(item, node->data))
    {
        node = node->next;
        i++;

        if (node == NULL)
            break;
    }

    q->size++;
    linkedList_add_by_index(q->list, i, item);
}

void* prQueue_pop(PriorityQueue* q)
{
    void* item = linkedList_get(q->list, 0);
    linkedList_remove_first(q->list);

    q->size--;
    return item;

}

PriorityQueue* create_prQueue(CompareFunction func, _Bool auto_growing)
{
    return setup_prQueue(func, INITIAL_DEFAULT_SIZE, auto_growing);
}

PriorityQueue* create_prQueueN(CompareFunction func, unsigned int size, _Bool auto_growing)
{
    return setup_prQueue(func, size, auto_growing);
}


void delete_prQueue(PriorityQueue* queue)
{
    delete_linkedList(queue->list);
    free(queue);
}