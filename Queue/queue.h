#ifndef QUEUE_H
#define QUEUE_H

#include "../LinkedLIst/linkedlist.h"
#include <stdbool.h>

typedef void (*destroyFunction) (void *); 
typedef _Bool (*equalsFunction) (void*, void*);
typedef void (*to_stringFunction) (void *);
typedef void (*cloneFunction) (void*, void*);


typedef struct 
{
    LinkedList* list;
    unsigned int size;
    unsigned int capacity;
    _Bool auto_growing;
} Queue;


static Queue* setup_queue(Queue* queue, unsigned int capacity, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);
Queue* create_queue(_Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);
Queue* create_queueN(unsigned int size, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);

Queue* queue_clone(const Queue* queue);

extern void queue_to_string(const Queue* queue);

extern void* queue_peek_font(const Queue* queue);
extern void* queue_peek_rear(const Queue* queue);

extern void queue_change_capacity(Queue* queue, unsigned int capacity);
extern _Bool queue_compare(const Queue* first, const Queue* second);

void queue_push(Queue* queue, const void* item);
void* queue_pop(Queue* queue);

extern unsigned int queue_get_size(const Queue* queue);
extern unsigned int queue_get_capacity(const Queue* queue);
extern _Bool queue_is_full(const Queue* queue);
extern _Bool queue_is_empty(const Queue* queue);
extern _Bool queue_is_auto_growing(const Queue* queue);
void delete_queue(Queue* queue);

#endif