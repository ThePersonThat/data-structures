
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../object.h"

#define define_test_list_primitive(type, function_name)                                 \
void test_primitive_##function_name()                                                   \
{                                                                                       \
    type* list = create_##function_name(sizeof(int), NULL, to_string, NULL, NULL);      \
                                                                                        \
    for(int i = 0; i < 15; i++)                                                         \
    {                                                                                   \
        function_name##_add_by_index(list, i, &i);                                      \
    }                                                                                   \
                                                                                        \
    printf("Created %s from 0 to 15: \n", #type);                                       \
    function_name##_to_string(list);                                                    \
                                                                                        \
    printf("\n\t\t\t\t================= Test removing ================= \n\n");         \
                                                                                        \
    for(int i = 0; i < 5; i++)                                                          \
        function_name##_remove_by_index(list, 0);                                       \
                                                                                        \
    printf("The %s after removing items by index (removing index from 0 to 4): \n", #type);     \
    function_name##_to_string(list);                                                    \
                                                                                        \
    type* remove_list = create_##function_name(sizeof(int), NULL, to_string, NULL, NULL);       \
    for(int i = 5; i < 15; i++)                                                         \
        function_name##_add_last(remove_list, &i);                                      \
                                                                                        \
    assert(function_name##_compare_list(remove_list, list)                              \
        && "Removing by index was not passed successfully\n");                          \
                                                                                        \
    delete_##function_name(remove_list);                                                \
    printf("\n\t\t\t\t================= Test removing ================= \n\n");         \
    printf("\n\t\t\t\t------------------------------------------------- \n\n");         \
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");         \
                                                                                        \
    function_name##_remove_All(list);                                                   \
                                                                                        \
    for(int i = 0; i < 5; i++)                                                          \
        function_name##_add_last(list, &i);                                             \
                                                                                        \
    type* clone_list = function_name##_clone(list);                                     \
                                                                                        \
    assert(function_name##_compare_list(list, clone_list) && "Error of clone list\n");  \
                                                                                        \
    printf("%s before the insertion: \n", #type);                                       \
                                                                                        \
    function_name##_to_string(list);                                                    \
                                                                                        \
    function_name##_insert_list(list, clone_list, 1);                                   \
                                                                                        \
    printf("Inserted a new %s into the main %s at index 1:\n", #type, #type);           \
    function_name##_to_string(list);                                                    \
                                                                                        \
    delete_##function_name(clone_list);                                                 \
                                                                                        \
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");         \
    printf("\n\t\t\t\t------------------------------------------------- \n\n");         \
    printf("\n\t\t\t\t=================   Other test   ================ \n\n");         \
                                                                                        \
    for(int i = 0; i < list->size; i++)                                                 \
    {                                                                                   \
        int number = rand() % 50;                                                       \
        function_name##_set(list, i, &number);                                          \
    }                                                                                   \
                                                                                        \
    printf("Setted random items in %s: \n", #type);                                     \
    function_name##_to_string(list);                                                    \
                                                                                        \
    function_name##_sort(list, compare);                                                \
                                                                                        \
    printf("%s sorted:\n", #type);                                                      \
    function_name##_to_string(list);                                                    \
                                                                                        \
    delete_##function_name(list);                                                       \
}      



#define define_test_list_object(type, function_name)                                                    \
void test_object_##function_name()                                                                      \
{                                                                                                       \
    Person person[SIZE];                                                                                \
    init_person(person);                                                                                \
    type* list = create_##function_name(sizeof(Person), destroy, to_string_person, equals, clone);      \
                                                                                                        \
    for(int i = 0; i < SIZE; i++)                                                                       \
    {                                                                                                   \
        function_name##_add_by_index(list, i, &person[i]);                                              \
    }                                                                                                   \
                                                                                                        \
    printf("Created %s with %d structs\n", #type, SIZE);                                                \
    function_name##_to_string(list);                                                                    \
                                                                                                        \
    printf("\n\t\t\t\t================= Test removing ================= \n\n");                         \
                                                                                                        \
    for(int i = 0; i < 2; i++)                                                                          \
        function_name##_remove_by_index(list, 0);                                                       \
                                                                                                        \
    printf("The %s after removing items by index (removing index from 0 to 2): \n", #type);             \
    function_name##_to_string(list);                                                                    \
                                                                                                        \
    type* remove_list = create_##function_name(sizeof(Person), destroy, to_string_person, equals, clone);   \
                                                                                                        \
    for(int i = 2; i < SIZE; i++)                                                                       \
        function_name##_add_last(remove_list, &person[i]);                                              \
                                                                                                        \
    assert(function_name##_compare_list(remove_list, list)                                              \
        && "Removing by index was not passed successfully\n");                                          \
                                                                                                        \
    delete_##function_name(remove_list);                                                                \
                                                                                                        \
    printf("\n\t\t\t\t================= Test removing ================= \n\n");                         \
    printf("\n\t\t\t\t------------------------------------------------- \n\n");                         \
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");                         \
                                                                                                        \
    function_name##_remove_All(list);                                                                   \
                                                                                                        \
    for(int i = 0; i < 3; i++)                                                                          \
        function_name##_add_last(list, &person[i]);                                                     \
                                                                                                        \
    type* clone_list = function_name##_clone(list);                                                     \
    assert(function_name##_compare_list(list, clone_list) && "Error of clone list\n");                  \
                                                                                                        \
    printf("%s before the insertion: \n", #type);                                                       \
                                                                                                        \
    function_name##_to_string(list);                                                                    \
                                                                                                        \
    function_name##_insert_list(list, clone_list, 1);                                                   \
    printf("Inserted a new the samee %s into the main %s at index 1:\n", #type, #type);                 \
    function_name##_to_string(list);                                                                    \
                                                                                                        \
    delete_##function_name(clone_list);                                                                 \
                                                                                                        \
    printf("\n\t\t\t\t================= Test insertion ================ \n\n");                         \
    printf("\n\t\t\t\t------------------------------------------------- \n\n");                         \
    printf("\n\t\t\t\t=================   Other test   ================ \n\n");                         \
                                                                                                        \
    function_name##_remove_last(list);                                                                  \
                                                                                                        \
    for(int i = 0; i < SIZE; i++)                                                                       \
        function_name##_set(list, i, &person[i]);                                                       \
                                                                                                        \
    printf("Setted items in %s: \n", #type);                                                            \
    function_name##_to_string(list);                                                                    \
                                                                                                        \
    function_name##_sort(list, compare_person);                                                         \
                                                                                                        \
    printf("%s sorted by size name:\n", #type);                                                         \
    function_name##_to_string(list);                                                                    \
                                                                                                        \
    delete_##function_name(list);                                                                       \
                                                                                                        \
    destroy_persons(person);                                                                            \
}                                                                                                        


