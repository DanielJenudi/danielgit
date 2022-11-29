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
#include <stdio.h>

#define BASE 10

enum status
{
	SUCCESS = 0,
	FAIL = 1 
};

int KvalueInArr(int *arr, size_t size, int k);
static int CountSort(int *arr, size_t length);
static void HistogramMinMax(const int *arr, int *min, int *max, size_t length);
static void SetHistogram(const int *arr, size_t arr_len,
						 int *histogram, int min, int max);
static void SortArr(int *arr, size_t arr_len, int *sort_arr, int *histogram, int min);

int main()
{
	int arr[] = {1, 2, 5, 8, 3};
	
	printf("%d\n", KvalueInArr(arr, 5, 4));

	return SUCCESS;
}

int KvalueInArr(int *arr, size_t size, int k)
{
	CountSort(arr, size);
	
	return arr[k - 1];
}

static int CountSort(int *arr, size_t length)
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

