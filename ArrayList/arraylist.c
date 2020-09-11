#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_DEFAULT_SIZE 16

#define CHECK_OUT_OF_BOUNDS(index, size)                \
    if(index < 0 || index > size)                       \
    {                                                   \
        fprintf(stderr, "Error! Index out of bounds");  \
        return;                                         \
    }                                                   \


ArrayList* create_arrayList()
{
    ArrayList* list = malloc(sizeof(ArrayList));

    if(list == NULL)
    {
        fprintf(stderr, "Error of allocate memory");
        return NULL;
    }

    list->size = 0;
    list->data = malloc(sizeof(void *) * INITIAL_DEFAULT_SIZE);
    list->capacity = INITIAL_DEFAULT_SIZE;

    return list;
}

ArrayList* create_arrayListN(int size) 
{
    if(size == 0 || size < 0)
    {
        fprintf(stderr, "Wrong item count");
        return NULL;
    }

    ArrayList* list = malloc(sizeof(ArrayList));

    if(list == NULL)
    {
        fprintf(stderr, "Error allocate memory");
        return NULL;
    }

    list->size = 0;
    list->data = malloc(sizeof(void *) * size);
    list->capacity = size;

    return list;
}

void delete_arrayList(ArrayList* list)
{
    free(list->data);
    free(list);
}

static void allocate_item(ArrayList* list) 
{
    if(list->size + 1 > list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, sizeof(void *) * list->capacity);
        assert(list->data);
    }
}

void arrayList_add(ArrayList* list, void* item)
{
    allocate_item(list);
    list->data[list->size++] = item;
}

void arrayList_add_by_index(ArrayList* list, int index, void* item)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);
    
    allocate_item(list);
    memmove(list->data + index + 1, list->data + index, sizeof(list->data) * (list->size - index));
    list->data[index] = item;
    list->size++;
}

void arrayList_set(ArrayList* list, int index, void* item)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);
    list->data[index] = item;
}

bool arrayList_contains(ArrayList* list, void* item)
{
    for(int i = 0; i < list->size; i++)
    {
        if(list->data[i] == item)
            return true; 
    }

    return false;
}

void arrayList_change_capacity(ArrayList* list, int capacity)
{
    if(capacity < 0 )
    {
        fprintf(stderr, "Error! Index out of bounds");
        return;
    }

    if(capacity < list->size)
    {
        fprintf(stderr, "Error! Capacity can't be less then size");
        return;
    }

    list->capacity = capacity;
    list->data = realloc(list->data, sizeof(void *) * list->capacity);
    assert(list->data);
}

void arrayList_insert_list(ArrayList* dest_list, ArrayList* source_list, int index)
{
    CHECK_OUT_OF_BOUNDS(index, dest_list->size);
        
    if(source_list->size + dest_list->size > dest_list->capacity)
        arrayList_change_capacity(dest_list, (source_list->size + dest_list->size) * 2);

    memmove(dest_list->data + index + source_list->size, dest_list->data + index, sizeof(dest_list->data) * (dest_list->size - index));
    
    for(int i = index, j = 0; i < index + source_list->size; i++, j++)
    {
        dest_list->data[i] = source_list->data[j];
        dest_list->size++;
    }
}

ArrayList* arrayList_clone(ArrayList* list)
{
    ArrayList* new_list = create_arrayListN(list->capacity);
    
    for(int i = 0; i < list->size; i++)
        arrayList_add(new_list, list->data[i]);
    
    return new_list;
}

void arrayList_remove_by_index(ArrayList* list, int index)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);

    memmove(list->data + index, list->data + index + 1, sizeof(list->data) * (list->size - index));
    list->size--;
}

void arrayList_remove_if(ArrayList* list, void* item_condition, _Bool (condition) (void *, void *))
{
    for(int i = 0; i < list->size; i++)
    {
        if(condition(list->data[i], item_condition))
            arrayList_remove_by_index(list, i);
    }
}

void* arrayList_get_element(ArrayList* list, int index)
{
    if(index < 0 || index > list->size)                       
    {                                                   
        fprintf(stderr, "Error! Index out of bounds");  
        return NULL;                                         
    }      
    
    return list->data[index];
}

_Bool arrayList_compare_list(ArrayList* first_list, ArrayList* second_list)
{
    if(first_list->size != second_list->size)
        return false;

    for(int i = 0; i < first_list->size; i++)
    {
        if(first_list->data[i] == second_list->data[i]) 
            continue;
        else 
            return false;  
    }

    return true;
}

char* arrayList_to_string(ArrayList* list, const char* format, char* buffer)
{
    sprintf(buffer, "ArrayList: [ ");
    int offset = strlen("ArrayList: [ ");

    for(int i = 0; i < list->size; i++)
    {
        sprintf(buffer + offset, format, arrayList_get_element(list, i));
        offset += strlen(buffer) - offset;
    }

    sprintf(buffer + offset, " ]\0");

    return buffer;
}


void arrayList_sort(ArrayList* list, _Bool (compare) (void *, void *))
{
    mergeSort(list->data, 0, list->size - 1, compare);
}

void merge(void* arr[], int start, int mid, int end, _Bool (compare)(void*, void*))
{
    int start2 = mid + 1;

    if (compare(arr[mid], arr[start2])) {
        return;
    }

    while (start <= mid && start2 <= end) {

        if (compare(arr[start], arr[start2])) {
            start++;
        }
        else {
            void* value = arr[start2];
            int index = start2;

            while (index != start) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;

            start++;
            mid++;
            start2++;
        }
    }
}

void mergeSort(void* arr[], int l, int r, _Bool (compare) (void *, void *))
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, compare);
        mergeSort(arr, m + 1, r, compare);

        merge(arr, l, m, r, compare);
    }
}

extern inline void arrayList_removeAll(ArrayList* list)
{
    list->size = 0;
}

extern inline unsigned int arrayList_get_size(ArrayList* list)
{
    return list->size;
}

extern inline unsigned int arrayList_get_capacity(ArrayList* list)
{
    return list->capacity;
}

extern inline _Bool arrayList_is_empty(ArrayList* list)
{
    return list->size == 0 ? true : false;
}