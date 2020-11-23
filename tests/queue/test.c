#include <stdio.h>
#include <assert.h>

#include "../../PriorityQueue/priorityqueue.h"
#include "../../Queue/queue.h"
#include "../../Stack/stack.h"

#include "test_queue.h"


#define pr_q /**/
define_test_queue_primitive(Queue, queue);
define_test_queue_object(Queue, queue);

#define pr_q /**/
define_test_queue_primitive(Stack, stack);
define_test_queue_object(Stack, stack);

#define pr_q pr_q_func,
define_test_queue_primitive(PriorityQueue, prQueue);

#define pr_q compare_person,
define_test_queue_object(PriorityQueue, prQueue);


int main()
{
    printf("Test is starting...\n\n");
    test_primitive_stack();
    test_object_stack();

    printf("\n\n");

    test_primitive_queue();
    test_object_queue();

    printf("\n\n");

    test_primitive_prQueue();
    test_object_prQueue();
    printf("\nThe test was passed successfully\n");

    return 0;
}