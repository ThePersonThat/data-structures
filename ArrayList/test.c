#include "arraylist.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>


_Bool condition(void* item, void* list)
{
    return arrayList_contains(list, item);
}

_Bool compare(void* one, void* two)
{
    return (int)one < (int)two ? true : false;
}

void test_arrayList()
{
    ArrayList* list = create_arrayList();
    ArrayList* test_remove = create_arrayList();
    char buffer[128];

    for(int i = 0; i <= 15; i++)
    {
        arrayList_add(list, (void *)i);
       
        if (i >= 5 && i < 10)
            continue;

        arrayList_add(test_remove, (void *)i);
    }

    ArrayList* clone_list = arrayList_clone(list);

    printf("Created an array from 0 to 15: %s\n", arrayList_to_string(list, " %d ", buffer));

    for(int i = 5, deleted = 0; i < 10; i++)
    {
        arrayList_remove_by_index(list, i - deleted);
        deleted++;
    }

    printf("\n\t\t\t\t================= Test removing ================= \n\n");
    printf("An array after removing items by index (removing index from 5 to 10): %s\n", arrayList_to_string(list, " %d ", buffer));
    assert(arrayList_compare_list(list, test_remove) && "Removing by index was not passed successfully");

    arrayList_removeAll(test_remove);

    for(int i = 0; i < 5; i++)
    {
        arrayList_add(test_remove, (void *)i);
    }


    for(int i = 0; i < 5; i++)
    {
        arrayList_remove_if(list, test_remove, condition);
    }

    printf("An array after removing with condition (condition: if(item >= 0 || item < 5)): %s\n", arrayList_to_string(list, " %d ", buffer));

    for(int i = 0; i < 5; i++)
    {
        assert(!arrayList_contains(list, (void *)i) && "Removing with condition was not passed successfully");
    }

    delete_arrayList(test_remove);

    printf("\n\t\t\t\t================= Test removing ================= \n\n");
    printf("\n\t\t\t\t------------------------------------------------- \n\n");
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");
    ArrayList* test_insert = create_arrayList();

    for(int i = 0; i < 10; i++)
    {
        arrayList_add_by_index(test_insert, i, (void *)i);
    }

    printf("Created a new array from 0 to 10: %s\n", arrayList_to_string(test_insert, " %d ", buffer));

    arrayList_insert_list(list, test_insert, 0);

    printf("Inserted a new array to the main array at 0 index: %s\n", arrayList_to_string(list, " %d ", buffer));

    assert(arrayList_compare_list(clone_list, list) && "Inserting an array was not passed successfully");

    delete_arrayList(test_insert);
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");
    printf("\n\t\t\t\t------------------------------------------------- \n\n");
    printf("\n\t\t\t\t=================   Other test   ================ \n\n");

    for (int i = 0; i < arrayList_get_size(list); i++)
    {
        arrayList_set(list, i, rand() % 50);
    }
    printf("Setted random items in array: %s\n", arrayList_to_string(list, " %d ", buffer));

    arrayList_sort(list, compare);

    printf("Array sorted: %s\n", arrayList_to_string(list, " %d ", buffer));

    printf("\n\t\t\t\t=================   Other test   ================ \n\n");
    delete_arrayList(list);
    delete_arrayList(clone_list);
}

int main()
{
    printf("Test is starting...\n\n");
    test_arrayList();
    printf("\nThe test was passed successfully\n");
}