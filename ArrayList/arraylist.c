#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_DEFAULT_SIZE 16
#define OFFSET(ptr, object_size, offset) (void *)((unsigned char *)ptr + (offset) * object_size)


#define CHECK_OUT_OF_BOUNDS(index, size)                \
    if(index < 0 || index > size)                       \
    {                                                   \
        fprintf(stderr, "Error! Index out of bounds");  \
        return;                                         \
    }                                                   \


ArrayList* setup_arrayList(unsigned int size, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    if(object_size == 0)
    {
        fprintf(stderr, "Error! object_size == 0\n");
        return NULL;
    }

    ArrayList* list = malloc(sizeof(ArrayList));

    if(list == NULL)
    {
        fprintf(stderr, "Error of allocate memory");
        return NULL;
    }

    list->object_size = object_size;
    list->size = 0;
    list->data = malloc(object_size * size);
    list->capacity = size;
    list->to_string = to_string;
    list->destroy = destroy;
    list->equals = equals;
    list->clone = clone;

    return list;
}

ArrayList* create_arrayList(unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    return setup_arrayList(INITIAL_DEFAULT_SIZE, object_size, destroy, to_string, equals, clone);
}

ArrayList* create_arrayListN(unsigned int size, unsigned int object_size, destroyFunction destroy, to_stringFunction to_string, equalsFunction equals, cloneFunction clone)
{
    return setup_arrayList(size, object_size, destroy, to_string, equals, clone);
}

void delete_arrayList(ArrayList* list)
{
    if(list->destroy)
        arrayList_remove_All(list);

    free(list->data);
    free(list);
}

static void allocate_item(ArrayList* list) 
{
    if(list->size + 1 > list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->object_size * list->capacity);
        assert(list->data);
    }
}

void arrayList_add_first(ArrayList* list, const void* item)
{
    arrayList_add_by_index(list, 0, item);
}

void arrayList_add_last(ArrayList* list, const void* item)
{
    arrayList_add_by_index(list, list->size, item);
}

void arrayList_add_by_index(ArrayList* list, int index, const void* item)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);
    
    allocate_item(list);

    if(list->size == index)
    {
        allocate_item(list);

        memcpy(OFFSET(list->data, list->object_size, list->size), item, list->object_size);
        list->size++;

        return;
    }

    memmove(OFFSET(list->data, list->object_size, index + 1), OFFSET(list->data, list->object_size, index), list->object_size * (list->size - index));
    memcpy(OFFSET(list->data, list->object_size, index), item, list->object_size);
    list->size++;
}


void arrayList_set_first(ArrayList* list, const void* item)
{
    arrayList_set(list, 0, item);
}

void arrayList_set_last(ArrayList* list, const void* item)
{
    arrayList_set(list, list->size - 1, item);
}

void arrayList_set(ArrayList* list, int index, const void* item)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);

    if(list->destroy)
        list->destroy(OFFSET(list->data, list->object_size, index));

    memcpy(OFFSET(list->data, list->object_size, index), item, list->object_size);
}

_Bool arrayList_contains(ArrayList* list, const void* item)
{
    if(list->equals)
    {
        for(int i = 0; i < list->size; i++)
            if(list->equals(OFFSET(list->data, list->object_size, i), item) == true)
                return true;
    }
    else 
    {
        for(int i = 0; i < list->size; i++)
            if(memcmp(OFFSET(list->data, list->object_size, i), item, list->object_size) == 0)
                return true;
    }

    return false;
}

void arrayList_change_capacity(ArrayList* list, unsigned int capacity)
{
    if(capacity < list->size)
    {
        fprintf(stderr, "Error! Capacity can't be less then size");
        return;
    }

    list->capacity = capacity;
    list->data = realloc(list->data, list->object_size * list->capacity);
    assert(list->data);
}

void arrayList_insert_list(ArrayList* dest_list, const ArrayList* source_list, int index)
{
    if(dest_list->object_size != source_list->object_size)
    {
        fprintf(stderr, "Error! Data types are different!\n");
        return;
    }

    if(source_list->size == 0)
    {
        fprintf(stderr, "Error! Size of list is 0\n");
        return;
    }
        
    CHECK_OUT_OF_BOUNDS(index, dest_list->size);
        
    if(source_list->size + dest_list->size > dest_list->capacity)
        arrayList_change_capacity(dest_list, (source_list->size + dest_list->size) * 2);

    memmove(OFFSET(dest_list->data, dest_list->object_size, index + source_list->size), OFFSET(dest_list->data, dest_list->object_size, index), dest_list->object_size * (dest_list->size - index));
    
    for(int i = index, j = 0; i < index + source_list->size; i++, j++)
    {
        memcpy(OFFSET(dest_list->data, dest_list->object_size, i), OFFSET(source_list->data, dest_list->object_size, j), source_list->object_size);
        dest_list->size++;
    }
}

ArrayList* arrayList_clone(const ArrayList* list)
{
    ArrayList* new_list = create_arrayListN(list->capacity, list->object_size, list->destroy, list->to_string, list->equals, list->clone);

    void* item = NULL;

    if (list->clone)
    {
        for (int i = 0; i < list->size; i++)
        {
            item = list->clone(arrayList_get(list, i));
            arrayList_add_by_index(new_list, i, item);
        }
    }
    else
    {
        for (int i = 0; i < list->size; i++)
            arrayList_add_by_index(new_list, i, arrayList_get(list, i));
    }
    
    return new_list;
}

void arrayList_remove_by_index(ArrayList* list, unsigned int index)
{
    CHECK_OUT_OF_BOUNDS(index, list->size);

    if(list->destroy)
        list->destroy(OFFSET(list->data, list->object_size, index));
    
    memmove(OFFSET(list->data, list->object_size, index), OFFSET(list->data, list->object_size, index + 1), list->object_size * (list->size - index));
    list->size--;
}

void arrayList_remove_if(ArrayList* list, void* item_condition, _Bool (condition) (void *, void *))
{
    for(int i = 0; i < list->size; i++)
    {
        if(condition(OFFSET(list->data, list->object_size, i), item_condition))
            arrayList_remove_by_index(list, i);
    }
}

void* arrayList_get(const ArrayList* list, unsigned int index)
{
    if(index > list->size)                       
    {                                                   
        fprintf(stderr, "Error! Index out of bounds");  
        return NULL;                                         
    }      
    
    return OFFSET(list->data, list->object_size, index);
}

_Bool arrayList_compare_list(const ArrayList* first_list, const ArrayList* second_list)
{
    if(first_list->size != second_list->size || first_list->object_size != second_list->object_size)
        return false;

    if(first_list->equals)
    {
        for(int i = 0; i < first_list->size; i++)
            if(first_list->equals(OFFSET(first_list->data, first_list->object_size, i), OFFSET(second_list->data, second_list->object_size, i)) == false)
                return false;
    }
    else
    {
        for(int i = 0; i < first_list->size; i++)
            if(memcmp(OFFSET(first_list->data, first_list->object_size, i), OFFSET(second_list->data, second_list->object_size, i), first_list->object_size) != 0)
                return false;
    }
    

    return true;
}

void arrayList_to_string(const ArrayList* list)
{
    printf("ArrayList: \n");
    
    if (list->to_string)
    {
        for (int i = 0; i < list->size; i++)
            list->to_string(arrayList_get(list, i));
    } 
    else
    {
        for (int i = 0; i < list->size; i++)
            printf("%p\n", arrayList_get(list, i));
    }

    printf("\n");
}


void arrayList_sort(ArrayList* list, _Bool (compare) (void *, void *))
{
    mergeSort(list, 0, list->size - 1, compare);
}

void merge(ArrayList* list, int start, int mid, int end, _Bool (compare)(void*, void*))
{
    int start2 = mid + 1;

    if (compare(OFFSET(list->data, list->object_size, mid), OFFSET(list->data, list->object_size, start2)))
        return;
    
    void* value = malloc(list->object_size);

    while (start <= mid && start2 <= end) {

        if (compare(OFFSET(list->data, list->object_size, start), OFFSET(list->data, list->object_size, start2))) 
        {
            start++;
        }
        else 
        {
            memcpy(value, OFFSET(list->data, list->object_size, start2), list->object_size);

            int index = start2;

            while (index != start) 
            {
                memcpy(OFFSET(list->data, list->object_size, index), OFFSET(list->data, list->object_size, index - 1), list->object_size);
                index--;
            }
    
            memcpy(OFFSET(list->data, list->object_size, start), value, list->object_size);


            start++;
            mid++;
            start2++;
        }
    }

    free(value);
}

void mergeSort(ArrayList* list, int l, int r, _Bool (compare) (void *, void *))
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(list, l, m, compare);
        mergeSort(list, m + 1, r, compare);

        merge(list, l, m, r, compare);
    }
}

void arrayList_remove_All(ArrayList* list)
{
    if(list->destroy)
    {
        for(int i = 0; i < list->size; i++)
            list->destroy(OFFSET(list->data, list->object_size, i));
    }

    list->size = 0;
}

inline unsigned int arrayList_get_size(ArrayList* list)
{
    return list->size;
}

inline unsigned int arrayList_get_capacity(ArrayList* list)
{
    return list->capacity;
}

inline _Bool arrayList_is_empty(ArrayList* list)
{
    return list->size == 0 ? true : false;
}