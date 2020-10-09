#include "hashtable.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HashItem* create_item(char* key, char* value)
{
    HashItem* item = malloc(sizeof(HashItem));

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

HashTable* create_table(unsigned int size)
{
    HashTable* table = malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;

    table->items = malloc(sizeof(HashItem *) * table->size);
    memset(table->items, 0, sizeof(HashItem *) * table->size);

    return table;
}

void handle_collision(HashTable* table, HashItem* item)
{

}

void HashTable_print(HashTable* table)
{
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (table->items[i]) 
            printf("Index: %d, Key: %s, Value: %s\n", i, table->items[i]->key, table->items[i]->value);
    }
    
    printf("-------------------\n\n");
}

char* HashTable_search(HashTable* table, char* key)
{
    int index = hash(key);
    HashItem* item = table->items[index];

    if(item != NULL) 
    {
        if(strcmp(item->key, key) == 0)
            return item->value;
    }

    return NULL;
}

void hashTable_insert(HashTable* table, char* key, char* value)
{
    int index = hash(key);
    HashItem* item = create_item(key, value);
    HashItem* current_item = table->items[index];

    if(current_item == NULL)
    {
        if(table->count == table->size)
        {
            printf("Insert Error: Hash Table is full\n");
            return;
        }

        table->items[index] = item;
        table->count++;
    } 
    else
    {
        if(strcmp(current_item->key, key) == 0) 
        {
            strcpy(table->items[index]->value, value);
            return;
        }
        else
        {
            handle_collision(table, item);
            return;
        }
        
    }
    
}

unsigned long hash(char* str)
{
    unsigned long sum_ascii = 0;

    for(int i = 0; str[i]; i++)
        sum_ascii += (int)str[i];


    return sum_ascii % CAPACITY;
}

void free_table(HashTable* table)
{
    for(int i = 0; i < table->size; i++)
    {
        if(table->items[i] != NULL)
            free(table->items[i]);
    }

    free(table->items);
    free(table);
}

void free_item(HashItem* item)
{
    free(item);
}

