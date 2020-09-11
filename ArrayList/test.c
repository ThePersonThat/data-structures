#include "arraylist.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


_Bool condition(void* item, void* list)
{
    return arrayList_contains(list, item);
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

    

    printf("\n\t\t\t\t================= Test insertion ================ \n\n");

    delete_arrayList(list);
    
}

int main()
{
    printf("Test is starting...\n\n");
    test_arrayList();
    printf("\nThe test was passed successfully\n");
}