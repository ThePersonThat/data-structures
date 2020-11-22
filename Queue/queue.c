#include "queue.h"
#include <stdio.h>

#define INITIAL_DEFAULT_SIZE 16

Queue* setup_queue(Queue* queue, unsigned int capacity, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    if(queue == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    queue->list = create_linkedList(object_size, destroy, to_string, equals, clone);
    queue->size = 0;
    queue->auto_growing = auto_growing;
    queue->capacity = capacity;

    return queue;
}

Queue* create_queue(_Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    Queue* queue = malloc(sizeof(Queue));

    return setup_queue(queue, INITIAL_DEFAULT_SIZE, auto_growing, object_size, destroy, to_string, equals, clone);
}


Queue* create_queueN(unsigned int size, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    Queue* queue = malloc(sizeof(Queue));

    return setup_queue(queue, size, auto_growing, object_size, destroy, to_string, equals, clone);
}

inline void queue_change_capacity(Queue* queue, unsigned int capacity)
{
    queue->capacity = capacity;
}

void queue_push(Queue* queue, const void* item)
{
    if(queue->size == queue->capacity)
    {
        if(queue->auto_growing)
            queue_change_capacity(queue, queue->capacity * 2);
        else 
        {
            fprintf(stderr, "Error! Queue is full\n");
            return;
        }
    }

    linkedList_add_last(queue->list, item);
    queue->size++;
}

inline void queue_to_string(const Queue* queue)
{  
    linkedList_to_string(queue->list);
}

Queue* queue_clone(const Queue* queue)
{
    Queue* q = create_queueN(queue->capacity, queue->auto_growing, queue->list->object_size, queue->list->destroy, queue->list->to_string, 
            queue->list->equals, queue->list->clone);

    q->size = queue->size;

    q->list = linkedList_clone(queue->list);

    return q;
}

inline _Bool queue_compare(const Queue* first, const Queue* second)
{
    return linkedList_compare_list(first->list, second->list);
}

inline _Bool queue_is_full(const Queue* queue)
{
    return queue->size == queue->capacity;
}

inline _Bool queue_is_empty(const Queue* queue)
{
    return queue->size == 0;
}

inline _Bool queue_is_auto_growing(const Queue* queue)
{
    return queue->auto_growing;
}

inline unsigned int queue_get_size(const Queue* queue)
{
    return queue->size;
}

inline unsigned int queue_get_capacity(const Queue* queue)
{
    return queue->capacity;
}

inline void* queue_peek_font(const Queue* queue)
{
    return linkedList_get_first(queue->list);
}

inline void* queue_peek_rear(const Queue* queue)
{
    return linkedList_get_last(queue->list);
}

void* queue_pop(Queue* queue)
{
    queue->size--;
    return LinkedList_pop_front(queue->list);
}

void delete_queue(Queue* queue)
{
    delete_linkedList(queue->list);
    free(queue);
}