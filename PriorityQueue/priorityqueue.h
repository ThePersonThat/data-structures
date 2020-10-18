
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

extern void prQueue_change_capacity(PriorityQueue* queue, unsigned int capacity);
void prQueue_push(PriorityQueue* q, void* item);
void* prQueue_pop(PriorityQueue* q);

PriorityQueue* prQueue_clone(PriorityQueue* q);
char* prQueue_to_string(PriorityQueue* queue, const char* format, char* buffer);

void delete_prQueue(PriorityQueue* q);

extern _Bool prQueue_compare(PriorityQueue* first, PriorityQueue* second);

extern void* prQueue_peek_font(PriorityQueue* q);
extern void* prQueue_peek_rear(PriorityQueue* q);

extern unsigned int prQueue_get_size(PriorityQueue* q);
extern unsigned int prQueue_get_capacity(PriorityQueue* q);
extern _Bool prQueue_is_full(PriorityQueue* q);
extern _Bool prQueue_is_empty(PriorityQueue* q);
extern _Bool prQueue_is_auto_growing(PriorityQueue* q);
extern void prQueue_remove_All(PriorityQueue* queue);
