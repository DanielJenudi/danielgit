/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Tom
Date: 20/04/2022
File: linear_sort
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stddef.h>/* size_t */
#include <assert.h>/* assert */
#include <stdlib.h>/* calloc, malloc, free */
#include <string.h>/* memcpy */

#include "linear_sort.h"

#define BASE 10

enum status
{
	SUCCESS = 0,
	FAIL = 1 
};



static void HistogramMinMax(const int *arr, int *min, int *max, size_t length);
static void SetHistogram(const int *arr, size_t arr_len,
						 int *histogram, int min, int max);
static void SortArr(int *arr, size_t arr_len, int *sort_arr, int *histogram, int min);

int RadixSort(int *arr, size_t len, size_t chunk_size);
static size_t NumOfRounds(int *arr, size_t len, size_t chunk_size);
static int Pow(int x, size_t y);
static void SortArrRadix(int *arr, size_t arr_len, int *sort_arr, int *histogram,
						 size_t chunk_size, size_t chunk_index);
static void SetHistogramRadix(const int *arr, size_t arr_len,
							  int *histogram, size_t histogram_len,
							  size_t chunk_size, size_t chunk_index);
static int CountingRadixSort(int *arr, size_t len, 
						   	 size_t chunk_size, size_t chunk_index);



int CountSort(int *arr, size_t length)
{
	int min = 0;
	int max = 0;
	int *histogram = NULL;
	int *sort_arr = NULL;
	
	assert(NULL != arr);
	
	HistogramMinMax(arr, &min, &max, length);
	
	histogram = (int *)calloc((max - min + 1), sizeof(int));
	if(NULL == histogram)
	{
		return FAIL;
	}
	
	sort_arr = (int *)malloc(length * sizeof(int));
	if(NULL == sort_arr)
	{
		free(histogram);
		histogram = NULL;
		return FAIL;
	}
	
	SetHistogram(arr, length, histogram, min, max);
	SortArr(arr, length, sort_arr, histogram, min);
	
	memcpy(arr, sort_arr, length * sizeof(int));
	
	free(histogram);
	histogram = NULL;
	free(sort_arr);
	sort_arr = NULL;
	
	return SUCCESS;
}

static void HistogramMinMax(const int *arr, int *min, int *max, size_t length)
{
	size_t i = 0;
	
	assert(NULL != arr);
	assert(NULL != min);
	assert(NULL != max);
	
	*min = *arr;
	*max = *arr;
	
	for(i = 1; i < length; ++i)
	{
		if(*(arr + i) < *min)
		{
			*min = *(arr + i);  	
		}
		else if(*(arr + i) > *max)
		{
			*max = *(arr + i);
		}
	}
}

static void SetHistogram(const int *arr, size_t arr_len,
						 int *histogram, int min, int max)
{
	size_t i = 0;
	size_t histogram_len = (max - min + 1);
	
	assert(NULL != arr);
	assert(NULL != histogram);
	
	for(i = 0; i < arr_len; ++i)
	{
		++*(histogram + *(arr + i) - min);
	}
	
	for(i = 0; i < (histogram_len - 1); ++i)
	{
		*(histogram + i + 1) += *(histogram + i);
	}
}

static void SortArr(int *arr, size_t arr_len, int *sort_arr, int *histogram, int min)
{
	size_t offset = 0;
	long i = 0;
	
	assert(NULL != arr);
	assert(NULL != histogram);

	for(i = (long)(arr_len - 1); 0 <= i; --i)
	{
		offset = *(arr + i) - min;
		--*(histogram + offset);
		*(sort_arr + *(histogram + offset)) = *(arr + i);
	} 
}

                
int RadixSort(int *arr, size_t len, size_t chunk_size)
{
	size_t chunk_index = 0;
	size_t rounds = 0;
	int status = SUCCESS;

	rounds = NumOfRounds(arr, len, chunk_size);

	for(chunk_index = 0; chunk_index < rounds; ++chunk_index)
	{
		status = CountingRadixSort(arr, len, chunk_size, chunk_index);
		if(FAIL == status)
		{
			return status;
		}
	}
	
	return status;
}

static int CountingRadixSort(int *arr, size_t len, 
						   	 size_t chunk_size, size_t chunk_index)
{
	int *histogram = NULL;
	int *sort_arr = NULL;
	size_t histogram_len = Pow(BASE, chunk_size);
	
	histogram = (int *)calloc(histogram_len, sizeof(int));
	if(NULL == histogram)
	{
		return FAIL;
	}

	sort_arr = (int *)malloc(len * sizeof(int));
	if(NULL == sort_arr)
	{
		free(histogram);
		histogram = NULL;
		return FAIL;
	}
	
	SetHistogramRadix(arr, len, histogram, histogram_len, chunk_size, chunk_index);
	SortArrRadix(arr, len, sort_arr, histogram, chunk_size, chunk_index);
	
	memcpy(arr, sort_arr, len * sizeof(int));
	
	free(histogram);
	histogram = NULL;
	free(sort_arr);
	sort_arr = NULL;
	
	return SUCCESS;
}

static size_t NumOfRounds(int *arr, size_t len, size_t chunk_size)
{
	size_t i = 0;
	int max = 0;
	size_t rounds = 0;
	
	for(i = 0; i < len; ++i)
	{
		if(max < *(arr + i))
		{
			max = *(arr + i); 
		} 
	}
	
	while(0 != max)
	{
		max /= BASE;
		++rounds;
	}
	
	return rounds / chunk_size;
}

static void SetHistogramRadix(const int *arr, size_t arr_len,
							  int *histogram, size_t histogram_len,
							  size_t chunk_size, size_t chunk_index)
{
	size_t i = 0;
	int arr_chunk_index = 0;
	
	assert(NULL != arr);
	assert(NULL != histogram);
	
	chunk_size = Pow(BASE, chunk_size);
	
	for(i = 0; i < arr_len; ++i)
	{
		arr_chunk_index = *(arr + i) / Pow(chunk_size, chunk_index);
		arr_chunk_index %= chunk_size;
		++*(histogram + arr_chunk_index);
	}
	
	for(i = 0; i < (histogram_len - 1); ++i)
	{
		*(histogram + i + 1) += *(histogram + i);
	}
}

static void SortArrRadix(int *arr, size_t arr_len, int *sort_arr, int *histogram,
						 size_t chunk_size, size_t chunk_index)
{
	int arr_chunk_index = 0;
	long i = 0;
	
	assert(NULL != arr);
	assert(NULL != histogram);

	chunk_size = Pow(BASE, chunk_size);

	for(i = (long)(arr_len - 1); 0 <= i; --i)
	{
		arr_chunk_index = *(arr + i) / Pow(chunk_size, chunk_index);
		arr_chunk_index %= chunk_size;
		--*(histogram + arr_chunk_index);
		*(sort_arr + *(histogram + arr_chunk_index)) = *(arr + i);
	} 
}

static int Pow(int x, size_t y)
{
    size_t i = 0;
    int result = x;
    
    if (0 == y)
    {
        return 1;
    }
    
    for (i = 1; i < y; ++i)
    {
        result *= x;
    }
    
    return result;
}



