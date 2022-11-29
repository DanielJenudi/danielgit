#include <assert.h>    /* assert */
#include <stdlib.h>    /* calloc, malloc, free */
#include <string.h>    /* memcpy */
#include <stdatomic.h> /* atomic_int */
#include <pthread.h>   /* pthread_create */
#include <stdio.h>

#include "mt_counting_sort.h"

#define HISTOGRAM_LEN (256)

enum status
{
    SUCCESS = 0,
    FAIL = 1
};

static int SetHistogram(const unsigned char *arr, size_t arr_len, size_t threads_amount);

static void SortArr(unsigned char *arr, size_t arr_len,
                    unsigned char *sort_arr);

static void *SetHistogramHandler(void *arg);

static void PrintArr(size_t *arr, size_t len);

static size_t g_histogram[HISTOGRAM_LEN] = {0};
static unsigned char *g_dictionary = NULL;
static size_t g_segment_size = 0;
static pthread_mutex_t g_lock = {0};

int MtCountingSort(unsigned char *arr, size_t len, size_t threads_amount)
{
    unsigned char *sort_arr = NULL;

    assert(NULL != arr);
    assert(0 != len);
    assert(0 != threads_amount);

    pthread_mutex_init(&g_lock, NULL);
    g_dictionary = arr;

    sort_arr = (unsigned char *)malloc(len * sizeof(unsigned char));
    if (NULL == sort_arr)
    {
        return FAIL;
    }

    SetHistogram(arr, len, threads_amount);

    SortArr(arr, len, sort_arr);

    memcpy(arr, sort_arr, len * sizeof(unsigned char));

    free(sort_arr);
    sort_arr = NULL;

    return SUCCESS;
}

static int SetHistogram(const unsigned char *arr, size_t arr_len, size_t threads_amount)
{
    pthread_t *tid_arr = NULL;
    void *retval = NULL;
    size_t i = 0;

    assert(NULL != arr);
    assert(0 != arr_len);
    assert(0 != threads_amount);

    assert(NULL != arr);

    tid_arr = (pthread_t *)malloc(threads_amount * sizeof(pthread_t));
    if (NULL == tid_arr)
    {
        return FAIL;
    }

    pthread_mutex_init(&g_lock, NULL);

    g_segment_size = (arr_len / threads_amount);

    for (i = 0; i < (threads_amount - 1); ++i)
    {
        if (SUCCESS !=
            pthread_create(&tid_arr[i], NULL, &SetHistogramHandler,
                           (g_dictionary + (g_segment_size * i))))
        {
            return FAIL;
        }
    }

    for (i = 0; i < (threads_amount - 1); ++i)
    {
        if (SUCCESS != pthread_join(tid_arr[i], &retval))
        {
            return FAIL;
        }
    }

    /* remaine handel */
    g_segment_size = arr_len - (g_segment_size * (threads_amount - 1));

    if (SUCCESS !=
        pthread_create(&tid_arr[i], NULL, &SetHistogramHandler,
                       (g_dictionary + (arr_len - g_segment_size))))
    {
        return FAIL;
    }

    if (SUCCESS != pthread_join(tid_arr[i], &retval))
    {
        return FAIL;
    }

    free(tid_arr);
    tid_arr = NULL;

    /* set histogram */
    for (i = 0; i < (HISTOGRAM_LEN - 1); ++i)
    {
        g_histogram[i + 1] += g_histogram[i];
    }

    return SUCCESS;
}

static void *SetHistogramHandler(void *arg)
{
    size_t i = 0;
    size_t local_histogram[HISTOGRAM_LEN] = {0};
    unsigned char *local_arr = (unsigned char *)arg;

    assert(NULL != arg);

    for (i = 0; i < g_segment_size; ++i)
    {
        ++(local_histogram[*(local_arr + i)]);
    }

    pthread_mutex_lock(&g_lock); /* lock */

    for (i = 0; i < HISTOGRAM_LEN; ++i)
    {
        g_histogram[i] += local_histogram[i];
    }

    pthread_mutex_unlock(&g_lock); /* unlock */

    return NULL;
}

static void SortArr(unsigned char *arr, size_t arr_len,
                    unsigned char *sort_arr)
{
    long i = 0;

    assert(NULL != arr);
    assert(NULL != sort_arr);
    assert(0 != arr_len);

    for (i = (long)(arr_len - 1); 0 <= i; --i)
    {
        --g_histogram[arr[i]];
        sort_arr[g_histogram[arr[i]]] = arr[i];
    }
}

static void PrintArr(size_t *arr, size_t len)
{
    size_t i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("index %lu: %lu ", i, arr[i]);
        printf("\n");
    }

    printf("\n");
}