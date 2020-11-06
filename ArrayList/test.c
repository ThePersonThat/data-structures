#include "arraylist.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

void to_string(const void* item)
{
    printf("[ %d ] ", *(int *)item);
}

_Bool condition(void* item, void* list)
{
    return arrayList_contains(list, item);
}

_Bool compare(const void* one, const void* two)
{
    return *(int*)one > * (int*)two;
}

void test_arrayList()
{
    ArrayList* list = create_arrayList(sizeof(int), NULL, to_string, NULL, NULL);
    ArrayList* test_remove = create_arrayList(sizeof(int), NULL, to_string, NULL, NULL);

    for(int i = 0; i <= 15; i++)
    {
        arrayList_add_first(list, &i);
       
        if (i >= 5 && i < 10)
            continue;

        arrayList_add_first(test_remove, &i);
    }

    

    ArrayList* clone_list = arrayList_clone(list);

    printf("Created an array from 0 to 15:\n");
    arrayList_to_string(list);
    printf("Created an array from 0 to 10:\n");
    arrayList_to_string(test_remove);

    for(int i = 5, deleted = 0; i < 10; i++)
    {
        arrayList_remove_by_index(list, i - deleted);
        deleted++;
    }

    printf("\n\t\t\t\t================= Test removing ================= \n\n");
    printf("An array after removing items by index (removing index from 5 to 9): \n");
    arrayList_to_string(list);
    assert(arrayList_compare_list(list, test_remove) && "Removing by index was not passed successfully");

    arrayList_removeAll(test_remove);

    for(int i = 0; i < 5; i++)
    {
        arrayList_add_last(test_remove, &i);
    }


    for(int i = 0; i < 5; i++)
    {
        arrayList_remove_if(list, test_remove, condition);
    }

    printf("An array after removing with condition (condition: if(item >= 0 || item < 5)): \n");
    arrayList_to_string(list);

    for(int i = 0; i < 5; i++)
    {
        assert(!arrayList_contains(list, &i) && "Removing with condition was not passed successfully");
    }

    delete_arrayList(test_remove);

    printf("\n\t\t\t\t================= Test removing ================= \n\n");
    printf("\n\t\t\t\t------------------------------------------------- \n\n");
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");

    ArrayList* test_insert = create_arrayList(sizeof(int), NULL, to_string, NULL, NULL);

    for(int i = 0; i < 10; i++)
    {
        arrayList_add_by_index(test_insert, i, &i);
    }

    printf("Created a new array from 0 to 9: \n");
    arrayList_to_string(test_insert);

    arrayList_insert_list(list, test_insert, 0);

    printf("Inserted a new array into the main array at index 0: \n");
    arrayList_to_string(list);

    assert(arrayList_compare_list(clone_list, list) && "Inserting an array was not passed successfully");

    delete_arrayList(test_insert);
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");
    printf("\n\t\t\t\t------------------------------------------------- \n\n");
    printf("\n\t\t\t\t=================   Other test   ================ \n\n");

    for (int i = 0; i < arrayList_get_size(list); i++)
    {
        int number = rand() % 50;
        arrayList_set(list, i, &number);
    }

    printf("Setted random items in array: \n");
    arrayList_to_string(list);

    arrayList_sort(list, compare);

    printf("Array sorted: \n");
    arrayList_to_string(list);

    printf("\n\t\t\t\t=================   Other test   ================ \n\n");
    delete_arrayList(list);
    delete_arrayList(clone_list);
}

int main()
{
    printf("Test is starting...\n\n");
    test_arrayList();
    printf("\nThe test was passed successfully\n");
    
    return 0;
}