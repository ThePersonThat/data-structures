#include "../LinkedLIst/linkedlist.h"
#include <stdbool.h>

typedef struct 
{
    LinkedList* list;
    unsigned int size;
    unsigned int capacity;
    _Bool auto_growing;
} Queue;


static Queue* setup_queue(Queue* queue, unsigned int capacity, _Bool auto_growing);
Queue* create_queue(_Bool auto_growing);
Queue* create_queueN(unsigned int size, _Bool auto_growing);

extern void* queue_peek_font(Queue* queue);
extern void* queue_peek_rear(Queue* queue);

extern void queue_change_capacity(Queue* queue, unsigned int capacity);

void queue_push(Queue* queue, void* item);
void* queue_pop(Queue* queue);

extern unsigned int queue_get_size(Queue* queue);
extern unsigned int queue_get_capacity(Queue* queue);
extern _Bool queue_is_full(Queue* queue);
extern _Bool queue_is_empty(Queue* queue);
extern _Bool queue_is_auto_growing(Queue* queue);
extern void queue_remove_All(Queue* queue);
void delete_queue(Queue* queue);