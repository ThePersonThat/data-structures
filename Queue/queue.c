#include "queue.h"
#include <stdio.h>

#define INITIAL_DEFAULT_SIZE 16

Queue* setup_queue(Queue* queue, unsigned int capacity, _Bool auto_growing)
{
    if(queue == NULL)
    {
        fprintf(stderr, "Error alocation memory!\n");
        return NULL;
    }

    queue->list = create_linkedList();
    queue->size = 0;
    queue->auto_growing = auto_growing;
    queue->capacity = capacity;

    return queue;
}

Queue* create_queue(_Bool auto_growing)
{
    Queue* queue = malloc(sizeof(Queue));

    return setup_queue(queue, INITIAL_DEFAULT_SIZE, auto_growing);
}


Queue* create_queueN(unsigned int capacity, _Bool auto_growing)
{
    Queue* queue = malloc(sizeof(Queue));

    return setup_queue(queue, capacity, auto_growing);
}

inline void queue_change_capacity(Queue* queue, unsigned int capacity)
{
    queue->capacity = capacity;
}

void queue_push(Queue* queue, void* item)
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

char* queue_to_string(Queue* queue, const char* format, char* buffer)
{
    sprintf(buffer, "Queue: [ ");
    int offset = strlen(buffer);

    for(int i = 0; i < queue->size; i++)
    {
        sprintf(buffer + offset, format, linkedList_get(queue->list, i));
        offset += strlen(buffer) - offset;
    }

    sprintf(buffer + offset, " ]\0");

    return buffer;
}

Queue* queue_clone(Queue* queue)
{
    Queue* q = create_queueN(queue->capacity, queue->auto_growing);

    q->size = queue->size;

    q->list = linkedList_clone(queue->list);

    return q;
}

inline _Bool queue_compare(Queue* first, Queue* second)
{
    return linkedList_compare_list(first->list, second->list);
}

inline void queue_remove_All(Queue* queue)
{
    linkedList_remove_All(queue->list);
    queue->size = 0;
}

inline _Bool queue_is_full(Queue* queue)
{
    return queue->size == queue->capacity;
}

inline _Bool queue_is_empty(Queue* queue)
{
    return queue->size == 0;
}

inline _Bool queue_is_auto_growing(Queue* queue)
{
    return queue->auto_growing;
}

inline unsigned int queue_get_size(Queue* queue)
{
    return queue->size;
}

inline unsigned int queue_get_capacity(Queue* queue)
{
    return queue->capacity;
}

inline void* queue_peek_font(Queue* queue)
{
    return linkedList_get_first(queue->list);
}

inline void* queue_peek_rear(Queue* queue)
{
    return linkedList_get_last(queue->list);
}

void* queue_pop(Queue* queue)
{
    void* item = linkedList_get(queue->list, 0);
    linkedList_remove_first(queue->list);

    queue->size--;
    return item;
}

void delete_queue(Queue* queue)
{
    delete_linkedList(queue->list);
    free(queue);
}