#include "linkedlist.h"
#include "../test/test_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

define_test_list(LinkedList, linkedList);

int main()
{
    printf("Test is starting...\n\n");
    test_linkedList();
    printf("\nThe test was passed successfully\n");
}