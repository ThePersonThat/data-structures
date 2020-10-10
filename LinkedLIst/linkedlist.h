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

LinkedList* linkedList_clone(LinkedList* list);

char* linkedList_to_string(LinkedList* list, const char* format, char* buffer);

void linkedList_insert_list(LinkedList* dest_list, LinkedList* source_list, unsigned int index);

void linkedList_set(LinkedList* list, unsigned int index, void* item);
extern void linkedList_set_first(LinkedList* list, void* item);
extern void LinkedList_set_last(LinkedList* list, void* item);

void linkedList_remove_by_index(LinkedList* list, unsigned int index);
void linkedList_remove_All(LinkedList* list);

_Bool linkedList_compare_list(LinkedList* one, LinkedList* two);

void linkedList_remove_if(LinkedList* list, void* item_condtion, _Bool (condition) (void*, void*));

void linkedList_sort(LinkedList* list, _Bool (compare)(void*, void*));
static void merge(LinkedList* list, int start, int mid, int end, _Bool (compare)(void*, void*));
static void mergeSort(LinkedList* list, int l, int r, _Bool (compare)(void*, void*));

extern void linkedList_remove_first(LinkedList* list);
extern void linkedList_remove_last(LinkedList* list);

_Bool linkedList_contains(LinkedList* list, void* item);
LinkedList* create_linkedList();

extern _Bool linkedList_is_empty(LinkedList* list);

extern void* linkedList_get_first(LinkedList* list);
extern void* linkedList_get_last(LinkedList* list);
extern unsigned int linkedList_get_size(LinkedList* list);
void delete_linkedList(LinkedList* list);