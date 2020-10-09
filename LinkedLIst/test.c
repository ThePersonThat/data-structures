#include "linkedlist.h"

#include <stdio.h>

int main()
{
    LinkedList* list = create_linkedList();

    linkedList_add_first(list, 211);
    linkedList_add_first(list, 210);
    linkedList_add_first(list, 230);
    linkedList_add_by_index(list, 3, 10);
    linkedList_remove_by_index(list, 2);

    LinkedList* insertion_list = create_linkedList();

    linkedList_add_last(insertion_list, 100);
    linkedList_add_last(insertion_list, 200);
    linkedList_insert_list(list, insertion_list, 1);

    char buffer[128];

    printf("%s", linkedList_to_string(list, "%d -> ", buffer));

    delete_linkedList(insertion_list);
    delete_linkedList(list);
    return 0;
}