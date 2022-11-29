/*******************************************************************************
 * Name: Daniel Jenudi
 * Reviewer: Roni
 * Date: 10/07/22
 *******************************************************************************/
#include <stdio.h>  /* printf() */
#include <stdlib.h> /* malloc(), free()*/
#include <string.h>
#include <assert.h>
#include <time.h>

#include "mt_shuff_and_sort.h"

#define NEWLINE_CHAR (10)
#define NULL_TERMINATOR ('\0')
#define N_DIC (1)
#define N_THREADS (16)

enum EXIT_STATUS
{
    FAIL = -1,
    SUCCESS = 0
};

static int ImportDictionary(unsigned char **buffer, size_t n_times);
static size_t ReplaceWithNullChr(unsigned char *buffer);
static void PrepareBuffer(unsigned char *buffer, unsigned char *words_array[], size_t n_words);

void ShuffleWords(unsigned char **words_array, size_t n_words);
int Shuffle(const void *element1, const void *element2);

int main(void)
{
    size_t words_count = 0;
    unsigned char *buffer = NULL;
    unsigned char **words_array;

    srand(time(NULL));

    if (SUCCESS != ImportDictionary(&buffer, N_DIC))
    {
        printf("fails\n");
        return FAIL;
    }

    words_count = ReplaceWithNullChr(buffer);
    words_array = (unsigned char **)malloc(words_count * sizeof(unsigned char *));
    PrepareBuffer(buffer, words_array, words_count);
    ShuffleWords(words_array, words_count);
    printf("words count = %ld\n", words_count);

    SortDic(words_array, words_count, N_THREADS, QSORT);
    /*SortDic(words_array, words_count, N_THREADS, BUBBLE_SORT);*/

    free(words_array);
    free(buffer);

    return SUCCESS;
}

void ShuffleWords(unsigned char **words_array, size_t n_words)
{
    qsort(words_array, n_words, sizeof(unsigned char *), &Shuffle);
}

int Shuffle(const void *element1, const void *element2)
{
    (void)element1;
    (void)element2;
    return ((rand() % 100) - 50);
}

static void PrepareBuffer(unsigned char *buffer, unsigned char *words_array[], size_t n_words)
{
    unsigned char *runner = NULL;
    size_t i = 1;

    assert(NULL != buffer);

    runner = buffer;

    for (i = 0; i < n_words; ++i)
    {
        words_array[i] = runner;
        runner = (unsigned char *)strchr((const char *)runner, NULL_TERMINATOR);
        ++runner;
    }
}

static size_t ReplaceWithNullChr(unsigned char *buffer)
{
    unsigned char *runner = NULL;
    size_t counter = 0;

    runner = (unsigned char *)strchr((const char *)buffer, NEWLINE_CHAR);

    while (NULL != runner)
    {
        *runner = '\0';
        ++runner;
        ++counter;
        runner = (unsigned char *)strchr((const char *)runner, NEWLINE_CHAR);
    }

    return counter;
}

static int ImportDictionary(unsigned char **buffer, size_t n_times)
{
    /* declare a file pointer */
    FILE *infile = NULL;
    long numbytes = 0;
    size_t i = 0;
    unsigned char *runner = NULL;

    /* open an existing file for reading */
    infile = fopen("words.txt", "r");

    /* quit if the file does not exist */
    if (infile == NULL)
    {
        return 1;
    }
    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    /* reset the file position indicator to
    the beginning of the file */

    *buffer = (unsigned char *)calloc((numbytes * n_times) + 1, sizeof(unsigned char));
    if (*buffer == NULL)
    {
        return 1;
    }

    runner = *buffer;
    for (i = 0; i < n_times; ++i)
    {
        fseek(infile, 0L, SEEK_SET);
        fread(runner, sizeof(unsigned char), numbytes, infile);
        runner = *buffer + (i * numbytes);
    }

    if (0 != fclose(infile))
    {
        printf("fail close\n");
        return -1;
    }

    return 0;
}