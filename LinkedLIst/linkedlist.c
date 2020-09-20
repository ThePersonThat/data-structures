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

    if (index == 0)
    {
        

     
    }
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
        if(list->head->next != NULL)
            list->head = list->head->next;

        list->head->prev = NULL;
        list->size--;
       
        free(temp);
        return;
    }

    if (index == list->size - 1)
    {
        temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->size--;

        free(temp);
        return;
    }

    LinkedNode* temp2;

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

    temp2 = temp->next;
    temp2->prev = temp->prev;
    temp->prev->next = temp2;

    free(temp);
   
    list->size--;
}

void linkedList_remove_All(LinkedList* list)
{
    while(list->size)
        linkedList_remove_last(list);
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
        node->next = list->head;
        node->prev = NULL;

        list->size++;
        list->head = node;

        if (list->tail == NULL)
            list->tail = node;

        return;
    }

    if (index == list->size)
    {
        node->next = NULL;
        node->prev = list->tail;

        list->size++;
        list->tail->next = node;
        list->tail = node;

        return;
    }

    LinkedNode* temp;

    if (list->size / 2 > index)
    {
        temp = list->head;

        for (int i = 0; i < index - 1; i++)
            temp = temp->next;
    }
    else
    {
        temp = list->tail;

        for (int i = list->size; i > index; i--)
            temp = temp->prev;
    }

    node->next = temp->next;
    node->prev = temp;
    temp->next = node;

    list->size++;
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