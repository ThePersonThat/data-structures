#include <stdbool.h>


typedef struct _linkedNode {
    void* data;
    struct _linkedNode* next;
    struct _linkedNode* prev;
} LinkedNode;

typedef struct {
    LinkedNode* head; 
    LinkedNode* tail;
    unsigned int size;
} LinkedList;

void* linkedList_get(LinkedList* list, unsigned int index);

void linkedList_add_by_index(LinkedList* list, unsigned int index, void* item);
extern void linkedList_add_first(LinkedList* list, void* item);
extern void linkedList_add_last(LinkedList* list, void* item);

void linkedList_insert_list(LinkedList* dest_list, LinkedList* source_list, unsigned int index);

void linkedList_set(LinkedList* list, unsigned int index, void* item);
extern void linkedList_set_first(LinkedList* list, void* item);
extern void LinkedList_set_last(LinkedList* list, void* item);

void linkedList_remove_by_index(LinkedList* list, unsigned int index);
void linkedList_remove_All(LinkedList* list);
extern void linkedList_remove_first(LinkedList* list);
extern void linkedList_remove_last(LinkedList* list);

_Bool linkedList_contain(LinkedList* list, void* item);
LinkedList* create_linkedList();

extern _Bool linkedList_is_empty(LinkedList* list);

extern void* linkedList_get_first(LinkedList* list);
extern void* linkedList_get_last(LinkedList* list);
extern unsigned int linkedList_get_size(LinkedList* list);
void delete_linkedList(LinkedList* list);