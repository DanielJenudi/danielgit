#include <stdio.h> /* printf */
#include <stdlib.h>/* calloc, malloc, free */
#include <time.h>  /* clock */

#include "mt_counting_sort.h"

#define N_DICT (3000)
#define N_OF_THREADS (16)

static void PrintArr(unsigned char *arr, size_t len);

int main()
{
    FILE *fp = NULL;
    unsigned char *buffer = NULL;
    size_t n_chars = 0, i = 0;

    fp = fopen("words.txt", "r");
    if (NULL == fp)
    {
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    n_chars = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = (unsigned char *)calloc((N_DICT * n_chars) + 1, sizeof(char));
    if (NULL == buffer)
    {
        return -1;
    }

    for (i = 0; i < N_DICT; ++i)
    {
        fread(buffer + i * n_chars, sizeof(char), n_chars, fp);
    }

    fclose(fp);
    fp = NULL;

    MtCountingSort(buffer, n_chars * N_DICT, N_OF_THREADS);

    free(buffer);
    buffer = NULL;

    return 0;
}

static void PrintArr(unsigned char *arr, size_t len)
{
    size_t i = 0;

    for (i = 0; i < len; ++i)
    {
        printf("index %lu: %d ", i, (int)arr[i]);
        if (0 == (i % 4))
        {
            printf("\n");
        }
    }

    printf("\n");
}
