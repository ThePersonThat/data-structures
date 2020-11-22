#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../LinkedLIst/linkedlist.h"
#include <stdbool.h>


typedef void (*destroyFunction) (void *); 
typedef _Bool (*equalsFunction) (void*, void*);
typedef void (*to_stringFunction) (void *);
typedef void (*cloneFunction) (void*, void*);
typedef _Bool (*CompareFunction) (void *, void *);

typedef struct 
{
    LinkedList* list;
    CompareFunction func;
    unsigned int size;
    unsigned int capacity;
    _Bool auto_growing;
} PriorityQueue; 


static PriorityQueue* setup_prQueue(CompareFunction func, unsigned int capacity, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);
PriorityQueue* create_prQueue(CompareFunction func, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);
PriorityQueue* create_prQueueN(CompareFunction func, unsigned int size, _Bool auto_growing, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);

extern void prQueue_change_capacity(PriorityQueue* queue, unsigned int capacity);
void prQueue_push(PriorityQueue* q, const void* item);
void* prQueue_pop(PriorityQueue* q);

PriorityQueue* prQueue_clone(const PriorityQueue* q);
extern void prQueue_to_string(const PriorityQueue* queue);

void delete_prQueue(PriorityQueue* q);

extern _Bool prQueue_compare(const PriorityQueue* first, const PriorityQueue* second);

extern void* prQueue_peek_font(const PriorityQueue* q);
extern void* prQueue_peek_rear(const PriorityQueue* q);

extern unsigned int prQueue_get_size(const PriorityQueue* q);
extern unsigned int prQueue_get_capacity(const PriorityQueue* q);
extern _Bool prQueue_is_full(const PriorityQueue* q);
extern _Bool prQueue_is_empty(const PriorityQueue* q);
extern _Bool prQueue_is_auto_growing(const PriorityQueue* q);
extern void prQueue_remove_All(PriorityQueue* queue);

#endif
