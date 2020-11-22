#define SIZE 5

#define cast(type, value) (*(type *)value)
#define get_field(type, value, field) ((type *)value)->field

typedef struct
{
    char* name;
    int age;
} Person;

void destroy(void* object)
{
    Person* person = object;
    free(person->name);
}

void to_string_person(void* object)
{
    Person* p = object;
    printf("Name: %s, Age: %d\n", p->name, p->age);
}

_Bool equals(void* one, void* two)
{
    if (one == two)
        return true;

    if (get_field(Person, one, age) == get_field(Person, two, age))
    {
        if (strcmp(get_field(Person, one, name), get_field(Person, two, name)) == 0)
            return true;
    }

    return false;
}


void clone(void* _from, void* _to)
{
    Person* to = (Person*)_to;
    Person* from = (Person*)_from;
    int size = strlen(from->name);

    to->age = from->age;
    to->name = malloc(size + 1);

    memcpy(to->name, from->name, size + 1);
}

_Bool compare_person(void* one, void* two)
{
    return (strlen(get_field(Person, one, name)) < strlen(get_field(Person, two, name)));
}

void init_person(Person* pers)
{
    const char* names[SIZE] =
    {
        "Alex",
        "Bastard",
        "Edward",
        "Dante",
        "Squall"
    };

    for (int i = 0; i < SIZE; i++)
    {
        pers[i].name = malloc(strlen(names[i]) + 1);
        memcpy(pers[i].name, names[i], strlen(names[i]) + 1);
        pers[i].age = i + 18;
    }
}

void destroy_persons(Person* pers)
{
    for (int i = 0; i < SIZE; i++)
        free(pers[i].name);
}

void to_string(void* item)
{
    printf("[ %d ]", *(int *)item);
}

_Bool compare(void* one, void* two)
{
    return *(int *)one > *(int *)two;
}