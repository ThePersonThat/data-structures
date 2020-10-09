

#define CAPACITY 1000

typedef struct {
    char key[32];
    char value[64];
} HashItem;

typedef struct {
    HashItem** items;
    unsigned int size;
    unsigned int count;
} HashTable;

HashItem* create_item(char* key, char* value);
HashTable* create_table(unsigned int size);
void hashTable_insert(HashTable* table, char* key, char* value); 
void handle_collision(HashTable* table, HashItem* item);
char* HashTable_search(HashTable* table, char* key);

unsigned long hash(char* str);

void HashTable_print(HashTable* table);

void free_item(HashItem* item);
void free_table(HashTable* table);