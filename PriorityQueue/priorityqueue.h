
#include "../LinkedLIst/linkedlist.h"
#include <stdbool.h>


typedef _Bool (*CompareFunction) (void *, void *);

typedef struct 
{
    LinkedList* list;
    CompareFunction func;
    unsigned int size;
    unsigned int capacity;
    _Bool auto_growing;
} PriorityQueue; 


static PriorityQueue* setup_prQueue(CompareFunction func, unsigned int capacity, _Bool auto_growing);
PriorityQueue* create_prQueue(CompareFunction func, _Bool auto_growing);
PriorityQueue* create_prQueueN(CompareFunction func, unsigned int size, _Bool auto_growing);

void prQueue_push(PriorityQueue* q, void* item);
void* prQueue_pop(PriorityQueue* q);

void delete_prQueue(PriorityQueue* queue);
