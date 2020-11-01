#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_OUT_OF_BOUNDS(index, size)                  \
    if(index < 0 || index > size)                         \
    {                                                     \
        fprintf(stderr, "Error! Index out of bounds\n");  \
        return;                                           \
    }   

_Bool linkedList_contains(const LinkedList * list, const void* item)
{
    if(list->equals)
    {
        for(int i = 0; i < list->size; i++)
            if(list->equals(linkedList_get(list, i), item))
                return true;
    }
    else 
    {
        for (int i = 0; i < list->size; i++)
            if (linkedList_get(list, i) == item)
                return true;
    }
  
    return false;
}

LinkedList* create_linkedList(unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals)
{
    if(object_size <= 0)
    {
        fprintf(stderr, "Error! object_size <= 0\n");
        return NULL;
    }

    LinkedList* list = malloc(sizeof(LinkedList));

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->object_size = object_size;
    list->destroy = destroy;
    list->to_string = to_string;
    list->equals = equals;

    return list;
}

void linkedList_insert_list(LinkedList* dest_list, const LinkedList* source_list, unsigned int index)
{
    CHECK_OUT_OF_BOUNDS(index, dest_list->size);

    LinkedNode* temp;

    for (int i = 0; i < source_list->size; i++)
    {
        linkedList_add_by_index(dest_list, index, linkedList_get(source_list, i));
        index++;
    }
}

void linkedList_remove_if(LinkedList* list, void* item_condition, _Bool (condition)(void*, void*))
{
    LinkedNode* temp = list->head;

    for (int i = 0; i < list->size; i++)
    {
        if (condition(linkedList_get(list, i), item_condition))
            linkedList_remove_by_index(list, i);
    }
}

char* linkedList_to_string(const LinkedList* list, const char* format, char* buffer)
{
    sprintf(buffer, "LinkedList: [ ");
    int offset = strlen("LinkedList: [ ");

    for (int i = 0; i < list->size; i++)
    {
        sprintf(buffer + offset, format, linkedList_get(list, i));
        offset += strlen(buffer) - offset;
    }

    sprintf(buffer + offset, " ]\0");

    return buffer;
}

inline void linkedList_set_first(LinkedList* list, const void* item)
{
    if(list->destroy)
        list->destroy(list->tail->data);
    
    memcpy(list->head->data, item, list->object_size);
}

inline void LinkedList_set_last(LinkedList* list, const void* item)
{
    if(list->destroy)
        list->destroy(list->tail->data);
    
    memcpy(list->tail->data, item, list->object_size);
}

void linkedList_set(LinkedList* list, unsigned int index, const void* item)
{
    if (list->size == 0)
        return;

    CHECK_OUT_OF_BOUNDS(index, list->size);

    LinkedNode* temp = list->head;

    for (int i = 0; i < index; i++)
        temp = temp->next;

    if(list->destroy)
        list->destroy(temp->data);

    memcpy(temp->data, item, list->object_size);
}

void linkedList_sort(LinkedList* list, _Bool (compare)(void*, void*))
{
    mergeSort(list, 0, list->size - 1, compare);
}

void merge(LinkedList* list, int start, int mid, int end, _Bool (compare)(void*, void*))
{
    int start2 = mid + 1;

    if (compare(linkedList_get(list, mid), linkedList_get(list, start2))) {
        return;
    }

    while (start <= mid && start2 <= end) {

        if (compare(linkedList_get(list, start), linkedList_get(list, start2))) {
            start++;
        }
        else {
            void* value = linkedList_get(list, start2);
            int index = start2;

            while (index != start) {
                linkedList_set(list, index, linkedList_get(list, index - 1));
                index--;
            }
         
            linkedList_set(list, start, value);

            start++;
            mid++;
            start2++;
        }
    }
}

void mergeSort(LinkedList* list, int l, int r, _Bool (compare)(void*, void*))
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(list, l, m, compare);
        mergeSort(list, m + 1, r, compare);

        merge(list, l, m, r, compare);
    }
}


static void remove_node(LinkedNode* node, destroyFunction destroy)
{
    if(destroy)
        destroy(node->data);

    free(node->data);
    free(node);
}

void linkedList_remove_by_index(LinkedList* list, unsigned int index)
{
    if (list->size == 0)
        return;

    CHECK_OUT_OF_BOUNDS(index, list->size);
  
    LinkedNode* temp;

    if (index == 0)
    {
        temp = list->head;

        list->size--;

        if (list->head->next == NULL)
        {
            remove_node(temp, list->destroy);

            list->tail = list->head = NULL;
            return;
        }

        list->head = list->head->next;
        list->head->prev = NULL;
        remove_node(temp, list->destroy);

        return;
    }

    if (index == list->size - 1)
    {
        temp = list->tail;

        list->size--;

        if (list->tail->prev == NULL)
        {
            remove_node(temp, list->destroy);

            list->tail = list->head = NULL;
            return;
        }
       
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        remove_node(temp, list->destroy);

        return;
    }

    LinkedNode* delete_node;

    temp = list->head;

    for (int i = 0; i < index - 1; i++)
        temp = temp->next;

    delete_node = temp->next;
    temp->next = delete_node->next;

    temp = delete_node->next;

    temp->prev = delete_node->prev;

    remove_node(temp, list->destroy);
    list->size--;
}

_Bool linkedList_compare_list(const LinkedList* one, const LinkedList* two)
{
    if (one->size != two->size || one->object_size != two->object_size)
        return false;


    if(one->equals)
    {
        for(int i = 0; i < one->size; i++)
            if(one->equals(linkedList_get(one, i), linkedList_get(two, i)) == false)
                return false;
    }
    else 
    {
        for (int i = 0; i < one->size; i++)
        {
            if (linkedList_get(one, i) != linkedList_get(two, i))
                return false;
        }
    }

    return true;
}

void linkedList_remove_All(LinkedList* list)
{
    while (list->size)
        linkedList_remove_first(list);
}

void linkedList_remove_first(LinkedList* list)
{
    linkedList_remove_by_index(list, 0);
}

void linkedList_remove_last(LinkedList* list)
{
    linkedList_remove_by_index(list, list->size - 1);
}

void linkedList_add_by_index(LinkedList* list, unsigned int index, const void* item)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);

    LinkedNode* node = malloc(sizeof(LinkedNode));
    node->data = malloc(sizeof(list->object_size));

    memcpy(node->data, item, list->object_size);

    if (index == 0)
    {

        if (list->size == 0)
        {
            node->next = NULL;
            node->prev = NULL;
            list->size++;

            list->head = list->tail = node;

            return;
        }

        node->next = list->head;
        node->prev = NULL;

        list->head->prev = node;
        list->head = node;

        list->size++;

        return;
    }

    if (index == list->size)
    {
        list->size++;

        node->next = NULL;
        node->prev = list->tail;

        list->tail->next = node;
        list->tail = list->tail->next;

        return;
    }

    LinkedNode* temp = list->head;

    for (int i = 0; i < index - 1; i++)
        temp = temp->next;

    node->prev = temp;
    node->next = temp->next;

    temp->next = node;
    list->size++;
}


LinkedList* linkedList_clone(const LinkedList* list)
{
    LinkedList* clone_list = create_linkedList(list->object_size, list->destroy, list->to_string, list->equals);

    for (int i = 0; i < list->size; i++)
        linkedList_add_last(clone_list, linkedList_get(list, i));

    return clone_list;
}

_Bool linkedList_is_empty(const LinkedList* list)
{
    return list->size == 0;
}

inline void linkedList_add_first(LinkedList* list, const void* item)
{
    linkedList_add_by_index(list, 0, item);
}

inline void linkedList_add_last(LinkedList* list, const void* item)
{
    linkedList_add_by_index(list, list->size, item);
}

inline void* linkedList_get_first(const LinkedList* list)
{
    return list->head->data;
}

inline void* linkedList_get_last(const LinkedList* list)
{
    return list->tail->data;
}

void* linkedList_get(const LinkedList* list, unsigned int index)
{
    if(index < 0 || index > list->size)                       
    {                                                   
        fprintf(stderr, "Error! Index out of bounds"); 
        return NULL;                                         
    }   

    if(index == 0)
        return list->head->data;

    if (index == list->size - 1)
        return list->tail->data;

    LinkedNode* temp = list->head;

    for (int i = 0; i < index; i++)
        temp = temp->next;

    return temp->data;
}

inline unsigned int linkedList_get_size(const LinkedList* list)
{
    return list->size;
}

void delete_linkedList(LinkedList* list)
{
    linkedList_remove_All(list);
    free(list);
}