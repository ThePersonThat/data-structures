#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

#define CHECK_OUT_OF_BOUNDS(index, size)                  \
    if(index < 0 || index > size)                         \
    {                                                     \
        fprintf(stderr, "Error! Index out of bounds\n");  \
        return;                                           \
    }   

_Bool linkedList_contain(LinkedList * list, void* item)
{
    for (int i = 0; i < list->size; i++)
    {
        if (linkedList_get(list, i) == item)
            return true;
        else
            continue;
    }

    return false;
}

LinkedList* create_linkedList()
{
    LinkedList* list = malloc(sizeof(LinkedList));

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void linkedList_insert_list(LinkedList* dest_list, LinkedList* source_list, unsigned int index)
{
    CHECK_OUT_OF_BOUNDS(index, dest_list->size);

    LinkedNode* temp;

    for (int i = 0; i < source_list->size; i++)
    {
        linkedList_add_by_index(dest_list, index, linkedList_get(source_list, i));
        index++;
    }
}

char* linkedList_to_string(LinkedList* list, const char* format, char* buffer)
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

inline void linkedList_set_first(LinkedList* list, void* item)
{
    list->head->data = item;
}

inline void LinkedList_set_last(LinkedList* list, void* item)
{
    list->tail->data = item;
}

void linkedList_set(LinkedList* list, unsigned int index, void* item)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);

    if (list->size == 0)
        return;

    LinkedNode* temp;

    if (list->size / 2 > index)
    {
        temp = list->head;

        for (int i = 0; i < index; i++)
            temp = temp->next;
    }
    else
    {
        temp = list->tail;

        for (int i = list->size; i > index + 1; i--)
            temp = temp->prev;
    }

    temp->data = item;
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
            free(temp);

            list->tail = list->head = NULL;
            return;
        }

        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);

        return;
    }

    if (index == list->size - 1)
    {
        temp = list->tail;

        list->size--;

        if (list->tail->prev == NULL)
        {
            free(temp);

            list->tail = list->head = NULL;
            return;
        }
       
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);

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

    free(delete_node);
    list->size--;
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

void linkedList_add_by_index(LinkedList* list, unsigned int index, void* item)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);

    LinkedNode* node = malloc(sizeof(LinkedNode));

    node->data = item;

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


LinkedList* linkedList_clone(LinkedList* list)
{
    LinkedList* clone_list = create_linkedList();

    for (int i = 0; i < list->size; i++)
        linkedList_add_last(clone_list, linkedList_get(list, i));

    return clone_list;
}

_Bool linkedList_is_empty(LinkedList* list)
{
    return list->size == 0 ? true : false;
}

inline void linkedList_add_first(LinkedList* list, void* item)
{
    linkedList_add_by_index(list, 0, item);
}

inline void linkedList_add_last(LinkedList* list, void* item)
{
    linkedList_add_by_index(list, list->size, item);
}

inline void* linkedList_get_first(LinkedList* list)
{
    return list->head->data;
}

inline void* linkedList_get_last(LinkedList* list)
{
    return list->tail->data;
}

void* linkedList_get(LinkedList* list, unsigned int index)
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

inline unsigned int linkedList_get_size(LinkedList* list)
{
    return list->size;
}

void delete_linkedList(LinkedList* list)
{
    linkedList_remove_All(list);
    free(list);
}