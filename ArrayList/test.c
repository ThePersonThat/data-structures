#include "arraylist.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "../test/test_list.h"

define_test_list(ArrayList, arrayList);

int main()
{
    printf("Test is starting...\n\n");
    test_arrayList();
    printf("\nThe test was passed successfully\n");
    
    return 0;
}