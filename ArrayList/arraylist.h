
#define fori_arrayList(item, index, list)  \
    for(item = list->data[index]; index < list->size; item = list->data[++index])


typedef struct {
    unsigned int size;
    unsigned int capacity;
    void** data; 
} ArrayList;


ArrayList* create_arrayList(); // to create list with constant size (16)
ArrayList* create_arrayListN(int size); // to create list with own size 
void delete_arrayList(ArrayList* list); // to delete and free memory of arrayList

void arrayList_add(ArrayList* list, void* item); // to add element to arrayList
void arrayList_add_by_index(ArrayList* list, int index, void* item); // to add element to arrayList by index

void arrayList_set(ArrayList* list, int index, void* item); // change element by index

void arrayList_change_capacity(ArrayList* list, int capacity); // realocate capacity

ArrayList* arrayList_clone(ArrayList* list); // clone arrayList

char* arrayList_to_string(ArrayList* list, const char* format, char* buffer); // return returns printed items

void arrayList_sort(ArrayList* list, _Bool (compare) (void *, void *)); // sort arrayList with comparator 

void arrayList_insert_list(ArrayList* dest_list, ArrayList* source_list, int index); // insert one arrayList to another arrayList 

_Bool arrayList_contains(ArrayList* list, void* item); // check if contains item

_Bool arrayList_compare_list(ArrayList* first_list, ArrayList* second_list); // return true if all the elements from two arrayLists are the same 
void* arrayList_get_element(ArrayList* list, int index); // to get element by index

void arrayList_remove_by_index(ArrayList* list, int index); // remove item by index 
void arrayList_remove_if(ArrayList* list, _Bool (condition) (void *)); // remove item if it fits the condition

static void allocate_item(ArrayList* list); // allocate memory for new item
static void mergeSort(void* arr[], int l, int r, _Bool (compare) (void *, void *)); // merge sort
static void merge(void* arr[], int start, int mid, int end, _Bool (compare) (void*, void*)); // merge sort

inline void arrayList_removeAll(ArrayList* list); // remove all the item from list
inline unsigned int arrayList_get_size(ArrayList* list); // get list size 
inline unsigned int arrayList_get_capacity(ArrayList* list); // get list capacity 
inline _Bool arrayList_is_empty(ArrayList* list); // returns true if this arrayList contains no elements