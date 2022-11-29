#include <pthread.h>   /* pthread_create */
#include <stdatomic.h> /* atomic_int */
#include <stdlib.h>    /* malloc, free */
#include <stdio.h>     /* printd */

enum Status
{
    SUCCESS = 0,
    FAIL = -1
};

void *ThreadLocal(void *arg);
void *ThreadHeap(void *arg);

atomic_int g_atomic = 1;

int main()
{
    pthread_t tid[2] = {0};
    void *retval = NULL;

    if (SUCCESS !=
        pthread_create(&tid[0], NULL, &ThreadLocal, NULL))
    {
        return FAIL;
    }

    if (SUCCESS !=
        pthread_create(&tid[1], NULL, &ThreadHeap, NULL))
    {
        return FAIL;
    }

    printf("osher is a shoe\n");

    if (SUCCESS != pthread_join(tid[0], &retval))
    {
        return FAIL;
    }

    if (SUCCESS != pthread_join(tid[0], &retval))
    {
        return FAIL;
    }

    return SUCCESS;
}

void *ThreadLocal(void *arg)
{
    long local_var = 0;

    (void)arg;

    ++local_var;

    local_var += g_atomic;

    while (1)
        ;

    return (void *)local_var;
}

void *ThreadHeap(void *arg)
{
    char *heap_var = (char *)malloc(sizeof(char) * 20000);

    (void)arg;

    heap_var[0] = 'a';
    heap_var[1] = 'b';
    heap_var[2] = 'c';

    while (1)
        ;

    free(heap_var);
    heap_var = NULL;

    return NULL;
}