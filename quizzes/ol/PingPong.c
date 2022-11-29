#include <semaphore.h> /* seminit, sem_t */
#include <pthread.h>   /* pthread_create */
#include <stdio.h>     /* printf */

enum Status
{
    SUCCESS = 0,
    FAIL = -1
};

sem_t g_sem = {0};

void *DoPing(void *arg);
void *DoPong(void *arg);

int main()
{
    pthread_t tid[2] = {0};
    void *retval = NULL;

    sem_init(&g_sem, 0, 0);

    if (SUCCESS !=
        pthread_create(&tid[0], NULL, &DoPong, NULL))
    {
        return FAIL;
    }

    if (SUCCESS !=
        pthread_create(&tid[1], NULL, &DoPing, NULL))
    {
        return FAIL;
    }

    if (SUCCESS != pthread_join(tid[0], &retval))
    {
        return FAIL;
    }

    if (SUCCESS != pthread_join(tid[1], &retval))
    {
        return FAIL;
    }

    return SUCCESS;
}

void *DoPing(void *arg)
{
    int sem_val = 0;

    (void)arg;

    while (1)
    {
        sem_getvalue(&g_sem, &sem_val);

        if (0 == sem_val)
        {
            printf("PING\n");
            sem_post(&g_sem);
        }
    }
}

void *DoPong(void *arg)
{
    int sem_val = 0;

    (void)arg;

    while (1)
    {
        sem_getvalue(&g_sem, &sem_val);

        if (1 == sem_val)
        {
            printf("PONG\n");
            sem_wait(&g_sem);
        }
    }
}
