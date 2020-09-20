#include "linkedlist.h"

#include <stdio.h>

int main()
{
    LinkedList* list = create_linkedList();

    linkedList_add_last(list, 10);
    linkedList_add_last(list, 20);
    linkedList_add_last(list, 30);
    linkedList_add_last(list, 40);
    linkedList_add_last(list, 50);

    linkedList_set_first(list, 111);

    for (int i = 0; i < linkedList_get_size(list); i++)
    {
        printf("%d -> ", linkedList_get(list, i));
    }

    delete_linkedList(list);
    return 0;
}