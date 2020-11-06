#include "linkedlist.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void to_string(const void* item)
{
    printf("[ %d ]", cast(int, item));
}

_Bool condition(void* item, void* list)
{
    return linkedList_contains(list, item);
}

_Bool compare(void* one, void* two)
{
    return cast(int, one) > cast(int, two);
}

void test_linkedList()
{
    LinkedList* basic_list = create_linkedList(sizeof(int), NULL, to_string, NULL, NULL);
    LinkedList* compare_list = create_linkedList(sizeof(int), NULL, to_string, NULL, NULL);

    for (int i = 0; i < 10; i++)
    {
        if (i <= 5)
            linkedList_add_by_index(compare_list, i, &i);

        linkedList_add_by_index(basic_list, i, &i);
    }

    printf("Created the LinkedList from 0 to 10:\n");
    linkedList_to_string(basic_list);

    for (int i = 0; i <= 3; i++)
    {
        linkedList_remove_by_index(basic_list, 6);
    }

    printf("\n\t\t\t\t================= Test removing ================= \n\n");

    printf("The linkedList after removing items by index (removing index from 5 to 9):\n");
    linkedList_to_string(basic_list);
    assert(linkedList_compare_list(basic_list, compare_list) && "Removing by index was not passed successfully\n");

    linkedList_remove_All(compare_list);

    for (int i = 0; i < 5; i++)
    {
        linkedList_add_by_index(compare_list, i, &i);
    }


    for (int i = 0; i < 5; i++)
    {
        linkedList_remove_if(basic_list, compare_list, condition);
    }

    
    printf("The linkedList after removing with condition (condition: if(item >= 0 || item < 5)):\n");
    linkedList_to_string(basic_list);

    {
        int number = 5;
        assert(linkedList_contains(basic_list, &number) && "Removing with condition was not passed successfully\n");
    }
    printf("\n\t\t\t\t================= Test removing ================= \n\n");
    printf("\n\t\t\t\t------------------------------------------------- \n\n");
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");


    linkedList_remove_All(basic_list);
    linkedList_remove_All(compare_list);

    for (int i = 0; i < 5; i++)
    {
        linkedList_add_last(basic_list, &i);
    }
    
    LinkedList* clone_list = linkedList_clone(basic_list);

    assert(linkedList_compare_list(basic_list, clone_list) && "Error of clone list\n");

    printf("LinkedList before the insertion:\n");
    linkedList_to_string(basic_list);

    linkedList_insert_list(basic_list, clone_list, 1);
    
    printf("Inserted a new linkedList into the main array at index 1:\n");
    linkedList_to_string(basic_list);

    printf("\n\t\t\t\t================= Test insertion ================ \n\n");
    printf("\n\t\t\t\t------------------------------------------------- \n\n");
    printf("\n\t\t\t\t=================   Other test   ================ \n\n");


    for (int i = 0; i < basic_list->size; i++)
    {
        int number = rand() % 50;
        linkedList_set(basic_list, i, &number);
    }

    printf("Setted random items in linkedList:\n");
    linkedList_to_string(basic_list);

    linkedList_sort(basic_list, compare);

    printf("LinkedList sorted:\n");
    linkedList_to_string(basic_list);

    printf("\n\t\t\t\t=================   Other test   ================ \n\n");

    delete_linkedList(clone_list);
    delete_linkedList(basic_list);
    delete_linkedList(compare_list);
}

int main()
{
    printf("Test is starting...\n\n");
    test_linkedList();
    printf("\nThe test was passed successfully\n");
}