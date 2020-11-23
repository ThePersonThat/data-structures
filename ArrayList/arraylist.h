#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef void (*destroyFunction) (void *); 
typedef _Bool (*equalsFunction) (void*, void*);
typedef void (*to_stringFunction) (void *);
typedef void (*cloneFunction) (void*, void*);

typedef struct {
    void* data; 
    destroyFunction destroy;
    equalsFunction equals;
    to_stringFunction to_string;
    cloneFunction clone;
    unsigned int object_size;
    unsigned int size;
    unsigned int capacity;
} ArrayList;

static ArrayList* setup_arrayList(unsigned int size, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone);
ArrayList* create_arrayList(unsigned int object_size, destroyFunction destroy,to_stringFunction to_string, equalsFunction equals, cloneFunction clone); // to create list with constant size (16)
ArrayList* create_arrayListN(unsigned int size, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone); // to create list with own size 
void delete_arrayList(ArrayList* list); // to delete and free memory of arrayList

void arrayList_add_first(ArrayList* list, const void* item); // to add element to the begin arrayList
void arrayList_add_last(ArrayList* list, const void* item); // to add element to the end arrayList
void arrayList_add_by_index(ArrayList* list, int index, const void* item); // to add element to arrayList by index

void arrayList_set_first(ArrayList* list, const void* item); // change the first element
void arrayList_set_last(ArrayList* list, const void* item); // change the last element
void arrayList_set(ArrayList* list, int index, const void* item); // change element by index

void arrayList_change_capacity(ArrayList* list, unsigned int capacity); // realocate capacity

ArrayList* arrayList_clone(const ArrayList* list); // clone arrayList

void arrayList_to_string(const ArrayList* list);

void arrayList_sort(ArrayList* list, _Bool (compare) (void *, void *)); // sort arrayList with comparator 

void arrayList_insert_list(ArrayList* dest_list, const ArrayList* source_list, int index); // insert one arrayList to another arrayList 

_Bool arrayList_contains(ArrayList* list, const void* item); // check if contains item

_Bool arrayList_compare_list(const ArrayList* first_list, const ArrayList* second_list); // return true if all the elements from two arrayLists are the same 
void* arrayList_get(const ArrayList* list, unsigned int index); // to get element by index

void arrayList_remove_last(ArrayList* list);
void arrayList_remove_by_index(ArrayList* list, unsigned int index); // remove item by index 
void arrayList_remove_first(ArrayList* list);
void arrayList_remove_if(ArrayList* list, void* item_condition, _Bool (condition) (void *, void *)); // remove item if it fits the condition

void allocate_item(ArrayList* list); // allocate memory for new item
static void arrayList_mergeSort(ArrayList* list, int l, int r, _Bool (compare) (void *, void *)); // merge sort
static void arrayList_merge(ArrayList* list, int start, int mid, int end, _Bool (compare) (void*, void*)); // merge sort

void arrayList_remove_All(ArrayList* list); // remove all the item from list
extern unsigned int arrayList_get_size(ArrayList* list); // get list size 
extern unsigned int arrayList_get_capacity(ArrayList* list); // get list capacity 
extern _Bool arrayList_is_empty(ArrayList* list); // returns true if this arrayList contains no elements

#endif