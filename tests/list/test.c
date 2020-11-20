#include "test_list.h"
#include "../../ArrayList/arraylist.h"
#include "../../LinkedLIst/linkedlist.h"

#include <assert.h>
#include <stdio.h>

define_test_list_primitive(ArrayList, arrayList);
define_test_list_object(ArrayList, arrayList); 

define_test_list_primitive(LinkedList, linkedList);
define_test_list_object(LinkedList, linkedList);

int main()
{
    printf("Test is starting... \n\n");
    test_primitive_arrayList();
    test_object_arrayList();
    test_primitive_linkedList();
    test_object_linkedList();
    printf("\nThe test was passed successfully \n");
}