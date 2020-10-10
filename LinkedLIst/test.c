#include "linkedlist.h"

#include <stdio.h>


_Bool compare(void* one, void* two)
{
    return strlen(one) > strlen(two);
}

int main()
{
    LinkedList* list = create_linkedList();

    /*linkedList_add_first(list, 211);
    linkedList_add_first(list, 210);
    linkedList_add_first(list, 230);
    linkedList_add_first(list, 250);
    linkedList_add_first(list, 240);
    linkedList_add_first(list, 216);
    linkedList_add_first(list, 232);*/

    linkedList_add_first(list, "a");
    linkedList_add_first(list, "aqheloo");
    linkedList_add_first(list, "ahell");
    linkedList_add_first(list, "arqrqwewq ");
    linkedList_add_first(list, "hello wo");
    linkedList_add_first(list, "waah");


    linkedList_sort(list, compare);

    char buffer[128];

    printf("%s", linkedList_to_string(list, "%s\n", buffer));

    delete_linkedList(list);
    return 0;
}