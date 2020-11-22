#include "priorityqueue.h"
#include <stdio.h>

#define INITIAL_DEFAULT_SIZE 16

PriorityQueue* setup_prQueue(CompareFunction func, unsigned int capacity, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
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
    q->list = create_linkedList(object_size, destroy, to_string, equals, clone);

    return q;
}

void prQueue_push(PriorityQueue* q, const void* item)
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
    q->size--;
    return LinkedList_pop_front(q->list);
}

PriorityQueue* prQueue_clone(const PriorityQueue* q)
{
    PriorityQueue* queue = create_prQueueN(q->func, q->capacity, q->auto_growing, q->list->object_size, q->list->destroy, 
            q->list->to_string, q->list->equals, q->list->clone);

    queue->size = q->size;

    queue->list = linkedList_clone(q->list);

    return queue;
}

inline void prQueue_to_string(const PriorityQueue* queue)
{
    linkedList_to_string(queue->list);
}

inline _Bool prQueue_compare(const PriorityQueue* first, const PriorityQueue* second)
{
    return linkedList_compare_list(first->list, second->list);
}

inline void prQueue_change_capacity(PriorityQueue* q, unsigned int capacity)
{
    q->capacity = capacity;
}

PriorityQueue* create_prQueue(CompareFunction func, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    return setup_prQueue(func, INITIAL_DEFAULT_SIZE, auto_growing, object_size, destroy, to_string, equals, clone);
}

PriorityQueue* create_prQueueN(CompareFunction func, unsigned int size, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    return setup_prQueue(func, size, auto_growing, object_size, destroy, to_string, equals, clone);
}

inline void* prQueue_peek_font(const PriorityQueue* q)
{
    return linkedList_get_first(q->list);
}

inline void* prQueue_peek_rear(const PriorityQueue* q)
{
    return linkedList_get_last(q->list);
}

inline unsigned int prQueue_get_size(const PriorityQueue* q)
{
    return q->size;
}

inline unsigned int prQueue_get_capacity(const PriorityQueue* q)
{
    return q->capacity;
}

inline _Bool prQueue_is_full(const PriorityQueue* q)
{
    return q->size == q->capacity;
}

inline _Bool prQueue_is_empty(const PriorityQueue* q)
{
    return q->size == 0;
}

inline _Bool prQueue_is_auto_growing(const PriorityQueue* q)
{
    return q->auto_growing;
}


void delete_prQueue(PriorityQueue* queue)
{
    delete_linkedList(queue->list);
    free(queue);
}