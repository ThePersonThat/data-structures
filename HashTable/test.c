#include <stdio.h>
#include "hashtable.h"


int main()
{
    HashTable* ht = create_table(CAPACITY);

    hashTable_insert(ht, "1", "First address");

    hashTable_insert(ht, "2", "Second address");

    printf("%s\n", HashTable_search(ht, "1"));

    printf("%s\n", HashTable_search(ht, "2"));

    printf("%s\n", HashTable_search(ht, "3"));

    HashTable_print(ht);

    free_table(ht);

    return 0;
}