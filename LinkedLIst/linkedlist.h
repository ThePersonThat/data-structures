#include <stdbool.h>


typedef void (*destroyFunction) (void *);
typedef char* (*to_stringFunction) (const void *, char* buffer);
typedef _Bool (*equalsFunction) (const void*, const void*);

typedef struct _linkedNode {
    void* data;
    struct _linkedNode* next;
    struct _linkedNode* prev;
} LinkedNode;

typedef struct {
    LinkedNode* head; 
    LinkedNode* tail;
    destroyFunction destroy;
    equalsFunction equals;
    to_stringFunction to_string;
    unsigned int size;
    unsigned int object_size;
} LinkedList;

void* linkedList_get(const LinkedList* list, unsigned int index);

void linkedList_add_by_index(LinkedList* list, unsigned int index, const void* item);
extern void linkedList_add_first(LinkedList* list, const void* item);
extern void linkedList_add_last(LinkedList* list, const void* item);

LinkedList* linkedList_clone(const LinkedList* list);

char* linkedList_to_string(const LinkedList* list, const char* format, char* buffer);

void linkedList_insert_list(LinkedList* dest_list, const LinkedList* source_list, unsigned int index);

void linkedList_set(LinkedList* list, unsigned int index, const void* item);
extern void linkedList_set_first(LinkedList* list, const void* item);
extern void LinkedList_set_last(LinkedList* list, const void* item);

void linkedList_remove_by_index(LinkedList* list, unsigned int index);
void linkedList_remove_All(LinkedList* list);
static void remove_node(LinkedNode* node, destroyFunction destroy);
_Bool linkedList_compare_list(const LinkedList* one, const LinkedList* two);

void linkedList_remove_if(LinkedList* list, void* item_condtion, _Bool (condition) (void*, void*));

void linkedList_sort(LinkedList* list, _Bool (compare)(void*, void*));
static void merge(LinkedList* list, int start, int mid, int end, _Bool (compare)(void*, void*));
static void mergeSort(LinkedList* list, int l, int r, _Bool (compare)(void*, void*));

extern void linkedList_remove_first(LinkedList* list);
extern void linkedList_remove_last(LinkedList* list);

_Bool linkedList_contains(const LinkedList* list, const void* item);
LinkedList* create_linkedList(unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals);

extern _Bool linkedList_is_empty(const LinkedList* list);

extern void* linkedList_get_first(const LinkedList* list);
extern void* linkedList_get_last(const LinkedList* list);
extern unsigned int linkedList_get_size(const LinkedList* list);
void delete_linkedList(LinkedList* list);