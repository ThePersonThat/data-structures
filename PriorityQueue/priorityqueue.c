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

    if(q->size == q->capacity)
    {
        if(q->auto_growing)
            prQueue_change_capacity(q, q->capacity * 2);
        else 
        {
            fprintf(stderr, "Error! Queue is full\n");
            return;
        }
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

inline void prQueue_remove_All(PriorityQueue* queue)
{
    queue->size = 0;
    linkedList_remove_All(queue->list);
}

void* prQueue_pop(PriorityQueue* q)
{
    void* item = linkedList_get(q->list, 0);
    linkedList_remove_first(q->list);

    q->size--;
    return item;

}

PriorityQueue* prQueue_clone(PriorityQueue* q)
{
    PriorityQueue* queue = create_prQueueN(q->func, q->capacity, q->auto_growing);

    queue->size = q->size;

    queue->list = linkedList_clone(q->list);

    return queue;
}

char* prQueue_to_string(PriorityQueue* queue, const char* format, char* buffer)
{
    sprintf(buffer, "PriorityQueue: [ ");
    int offset = strlen(buffer);

    for(int i = 0; i < queue->size; i++)
    {
        sprintf(buffer + offset, format, linkedList_get(queue->list, i));
        offset += strlen(buffer) - offset;
    }

    sprintf(buffer + offset, " ]\0");

    return buffer;
}

inline _Bool prQueue_compare(PriorityQueue* first, PriorityQueue* second)
{
    return linkedList_compare_list(first->list, second->list);
}

inline void prQueue_change_capacity(PriorityQueue* q, unsigned int capacity)
{
    q->capacity = capacity;
}

PriorityQueue* create_prQueue(CompareFunction func, _Bool auto_growing)
{
    return setup_prQueue(func, INITIAL_DEFAULT_SIZE, auto_growing);
}

PriorityQueue* create_prQueueN(CompareFunction func, unsigned int size, _Bool auto_growing)
{
    return setup_prQueue(func, size, auto_growing);
}

inline void* prQueue_peek_font(PriorityQueue* q)
{
    return linkedList_get_first(q->list);
}

inline void* prQueue_peek_rear(PriorityQueue* q)
{
    return linkedList_get_last(q->list);
}

inline unsigned int prQueue_get_size(PriorityQueue* q)
{
    return q->size;
}

inline unsigned int prQueue_get_capacity(PriorityQueue* q)
{
    return q->capacity;
}

inline _Bool prQueue_is_full(PriorityQueue* q)
{
    return q->size == q->capacity;
}

inline _Bool prQueue_is_empty(PriorityQueue* q)
{
    return q->size == 0;
}

inline _Bool prQueue_is_auto_growing(PriorityQueue* q)
{
    return q->auto_growing;
}


void delete_prQueue(PriorityQueue* queue)
{
    delete_linkedList(queue->list);
    free(queue);
}