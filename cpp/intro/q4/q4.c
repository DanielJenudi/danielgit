#include <stdio.h> /* printf */

typedef struct List
{
    int arr[10];
} List_t;

typedef struct Person
{
    int age;
} Person_t;

void foo(List_t *ll, int key, int age, void *pp);

int main()
{
    List_t ll = {0};
    Person_t pp = {0};

    foo(&ll, 0, 1, &pp);
    return 0;
}

void foo(List_t *ll, int key, int age, void *pp)
{
    int i = 0;
    /*void *vv =ll_find(ll, key);*/
    (void)key;

    Person_t *p = reinterpret_cast<Person_t *>(ll);
    p->age = age;

    for (i = 0; i < 10; ++i)
    {
        printf("%d\n", ll->arr[i]);
    }
}