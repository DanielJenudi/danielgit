/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 15/06/2022
File: 100K Threads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <pthread.h> /* pthread_create */
#include <stdio.h>   /* printf */

#define MAX_THREADS (10)

enum Status
{
    SUCCESS = 0,
    FAIL = -1
};

void *NumOfDivisors(void *arg);
long CreatThreds();
long SimpleLoop();
long JoinTheard(pthread_t *tid_arr);
int HaveRest();

static size_t g_check_number = 1234567890;

int main()
{
    time_t start = 0, end = 0;

    start = time(NULL);
    printf("sum_retval threads = %ld\n", CreatThreds());
    end = time(NULL);

    printf("overall time threads is %ld\n", end - start);

    start = time(NULL);
    printf("\nsum_retval simple loop = %ld\n", SimpleLoop());
    end = time(NULL);

    printf("overall time simple loop is %ld\n", end - start);

    return 0;
}

long CreatThreds()
{
    pthread_t tid_arr[MAX_THREADS] = {0};
    size_t i = 0;
    long sum_retval = 0;

    for (i = 0; i < MAX_THREADS; ++i)
    {
        if (SUCCESS != pthread_create(&tid_arr[i], NULL, &NumOfDivisors, (void *)i))
        {
            return FAIL;
        }
    }

    sum_retval = JoinTheard(tid_arr);

    if (HaveRest())
    {
        ++sum_retval;
    }

    return sum_retval;
}

long JoinTheard(pthread_t *tid_arr)
{
    size_t i = 0;
    void *retval = NULL;
    long sum_retval = 0;

    for (i = 0; i < MAX_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(tid_arr[i], &retval))
        {
            return FAIL;
        }

        sum_retval += (long)retval;
    }

    return sum_retval;
}

int HaveRest()
{
    return 0 != (g_check_number % MAX_THREADS);
}

void *NumOfDivisors(void *arg)
{
    long index = (long)arg;
    long num_of_reviews = g_check_number / MAX_THREADS;
    size_t start = index * num_of_reviews + 1;
    size_t end = start + num_of_reviews - 1;
    long counter = 0;

    for (; start <= end; ++start)
    {
        if (0 == (g_check_number % start))
        {
            ++counter;
        }
    }

    return (void *)counter;
}

long SimpleLoop()
{
    long counter = 0;
    size_t i = 0;

    for (i = 1; i <= g_check_number; ++i)
    {
        if (0 == (g_check_number % i))
        {
            ++counter;
        }
    }

    return counter;
}