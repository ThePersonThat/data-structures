#include "arraylist.h"
#include <stdio.h>
#include <stdbool.h>

void print(ArrayList* list)
{
    char buffer[64];
    
    printf("%s\n", arrayList_to_string(list, " %d ", buffer));
}

int main()
{
    ArrayList* list = create_arrayList();
    
    arrayList_add(list, (void *) 50);
    arrayList_add(list, (void *) 100);
    arrayList_add(list, (void *) 340);
    arrayList_add(list, (void *) 121);
    arrayList_add(list, (void *) 127);

    print(list);

    return 0;
}