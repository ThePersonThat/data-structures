#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../object.h"

void pr_q_func(void* one, void* two)
{
    return *(int*)one > * (int*)two;
}

#define define_test_queue_primitive(type, function_name)                                            \
void test_primitive_##function_name()                                                               \
{                                                                                                   \
    type* queue = create_##function_name##N(pr_q 5, true, sizeof(int), NULL, to_string, NULL, NULL);   \
                                                                                                    \
    for(int i = 0; i < 10; i++)                                                                     \
    {                                                                                               \
        int number = rand() % 50;                                                                   \
        function_name##_push(queue, &number);                                                       \
    }                                                                                               \
                                                                                                    \
    printf("Created auto growing %s from 0 to 9: \n", #type);                                       \
                                                                                                    \
    function_name##_to_string(queue);                                                               \
                                                                                                    \
    printf("Pop 5 items: ");                                                                        \
                                                                                                    \
    for(int i = 0; i < 5; i++)                                                                      \
        to_string(function_name##_pop(queue));                                                      \
                                                                                                    \
    printf("\n");                                                                                   \
                                                                                                    \
    type* clone = function_name##_clone(queue);                                                     \
                                                                                                    \
    function_name##_to_string(queue);                                                               \
                                                                                                    \
    assert(function_name##_compare(queue, clone) && "Error of comparing!\n");                       \
                                                                                                    \
    delete_##function_name(clone);                                                                  \
    delete_##function_name(queue);                                                                  \
}   

#define define_test_queue_object(type, function_name)                                               \
void test_object_##function_name()                                                                  \
{                                                                                                   \
    Person person[SIZE];                                                                            \
    init_person(person);                                                                            \
                                                                                                    \
    type* queue = create_##function_name##N(pr_q SIZE, true, sizeof(Person), destroy, to_string_person, equals, clone); \
                                                                                                    \
    for (int i = 0; i < SIZE; i++)                                                                  \
        function_name##_push(queue, &person[i]);                                                    \
                                                                                                    \
    printf("Pop 2 items: ");                                                                        \
                                                                                                    \
    for (int i = 0; i < 2; i++)                                                                     \
    {                                                                                               \
        void* ptr = function_name##_pop(queue);                                                     \
        to_string_person(ptr);                                                                      \
        destroy(ptr);                                                                               \
    }                                                                                               \
                                                                                                    \
    printf("\n");                                                                                   \
                                                                                                    \
    type* clone = function_name##_clone(queue);                                                     \
                                                                                                    \
    printf("Created clone %s: \n", #type);                                                          \
                                                                                                    \
    function_name##_to_string(clone);                                                               \
                                                                                                    \
    assert(function_name##_compare(queue, clone) && "Error of comparing!\n");                       \
                                                                                                    \
    delete_##function_name(clone);                                                                  \
    delete_##function_name(queue);                                                                  \
                                                                                                    \
    destroy_persons(person);                                                                        \
}