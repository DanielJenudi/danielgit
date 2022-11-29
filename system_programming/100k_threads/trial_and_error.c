/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 15/06/2022
File: 100K Threads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <pthread.h>/* pthread_create */
#include <stdio.h>  /* printf */

#define SIZE_OF_ARR (32750)

enum Status
{
    SUCCESS = 0,
    FAIL
};

void *Thread(void *arg);
void StartThread();
void TestCheckArr();

int g_arr[SIZE_OF_ARR] = {0};

int main()
{
    StartThread();
    TestCheckArr();

    return 0;
}

void TestCheckArr()
{
    int i = 0;

    for (i = 0; i < SIZE_OF_ARR; ++i)
    {
        if (i != g_arr[i])
        {
            printf("fail in index %d\n", i);
            break;
        }
    }

    if (i == SIZE_OF_ARR)
    {
        printf("SUCCESS\n");
    }
}

void StartThread()
{
    pthread_t tid_arr[SIZE_OF_ARR] = {0};
    pthread_attr_t attr = {0};
    size_t i = 0;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for (i = 0; i < SIZE_OF_ARR; ++i)
    {
        while (SUCCESS !=
               pthread_create(&tid_arr[i], &attr, &Thread, (void *)i))
            ;
    }
}

void *Thread(void *arg)
{
    long index = (long)arg;
    *(g_arr + index) = index;

    return NULL;
}