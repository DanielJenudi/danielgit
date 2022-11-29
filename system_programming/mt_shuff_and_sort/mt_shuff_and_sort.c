/*******************************************************************************
 * Name: Daniel Jenudi
 * Reviewer: Roni
 * Date: 10/07/22
 *******************************************************************************/
#include <stdlib.h>  /* qsort, malloc, calloc, free */
#include <string.h>  /* strcmp */
#include <assert.h>  /* assert */
#include <pthread.h> /* pthread_create */

#include "mt_shuff_and_sort.h"

enum Status
{
    SUCCESS = 0,
    FAIL = 1
};

enum Bubble_Sort_Status
{
    UNSORT = 0,
    SORT = 1
};

typedef void *(*thread_func_t)(void *arg);

static int CmpFunc(const void *str1, const void *str2);
static void *QsortThread(void *arg);

static void *BubbleSortThread(void *arg);
static void SwapStr(unsigned char **str1, unsigned char **str2);

static size_t g_segment_size = 0;
static thread_func_t g_thread_func_lut[2] = {&BubbleSortThread, &QsortThread};

int SortDic(unsigned char **arr, size_t arr_len, size_t threads_amount,
            int sort_type)
{
    pthread_t *tid_arr = NULL;
    size_t i = 0;

    assert(NULL != arr);
    assert(0 != arr_len);
    assert(0 != threads_amount);

    tid_arr = (pthread_t *)malloc(threads_amount * sizeof(pthread_t));
    if (NULL == tid_arr)
    {
        return FAIL;
    }

    g_segment_size = (arr_len / threads_amount);

    for (i = 0; i < (threads_amount - 1); ++i)
    {
        if (SUCCESS !=
            pthread_create(&tid_arr[i], NULL, g_thread_func_lut[sort_type],
                           (arr + (g_segment_size * i))))
        {
            return FAIL;
        }
    }

    for (i = 0; i < (threads_amount - 1); ++i)
    {
        if (SUCCESS != pthread_join(tid_arr[i], NULL))
        {
            return FAIL;
        }
    }

    /* remaine handel */
    g_segment_size = arr_len - (g_segment_size * (threads_amount - 1));

    if (SUCCESS !=
        pthread_create(&tid_arr[i], NULL, g_thread_func_lut[sort_type],
                       (arr + (arr_len - g_segment_size))))
    {
        return FAIL;
    }

    if (SUCCESS != pthread_join(tid_arr[i], NULL))
    {
        return FAIL;
    }

    /* sort all together */
    g_segment_size = arr_len;
    (*g_thread_func_lut[sort_type])(arr);

    free(tid_arr);
    tid_arr = NULL;

    return SUCCESS;
}

static void *QsortThread(void *arg)
{
    qsort((unsigned char **)arg, g_segment_size, sizeof(unsigned char *), &CmpFunc);

    return NULL;
}

static void *BubbleSortThread(void *arg)
{
    size_t i = 0, j = 0;
    int flag = SORT;
    unsigned char **str1 = NULL;
    unsigned char **str2 = NULL;

    for (i = 0; i < g_segment_size; ++i)
    {
        flag = SORT;
        for (j = 0; j < (g_segment_size - 1); ++j)
        {
            str1 = (unsigned char **)(arg) + j;
            str2 = (unsigned char **)(arg) + j + 1;
            if (0 < CmpFunc(str1, str2))
            {
                flag = UNSORT;
                SwapStr(str1, str2);
            }
        }

        if (flag == SORT)
        {
            break;
        }
    }

    return NULL;
}

static void SwapStr(unsigned char **str1, unsigned char **str2)
{
    unsigned char *temp = NULL;

    assert(NULL != str1);
    assert(NULL != str2);

    temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

static int CmpFunc(const void *str1, const void *str2)
{
    return strcmp(*(char **)str1, *(char **)str2);
}
