/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Tom
Date: 20/04/2022
File: cmp_sort
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stddef.h>/* size_t */
#include <assert.h>/* assert */

#include "cmp_sort.h"

enum
{
	UNSORT = 0,
	SORT = 1
};

static void SwapArrInts(int *arr, size_t index1, size_t index2);

int *SelectionSort(int *arr, size_t length)
{
	size_t i = 0;
	size_t j = 0;
	size_t min = 0;
	
	assert(NULL != arr);
	
	for(i = 0; i < length - 1; ++i)
	{
		min = i;
		
		for(j = i; j < length; ++j)
		{
			if(*(arr + min) > *(arr + j))
			{
				min = j;
			}
		}
		SwapArrInts(arr, i, min);
	}
	
	return arr;
}

int *BubbleSort(int *arr, size_t length)
{
	size_t i = 0;
	size_t j = 0;
	int flag = SORT;

	assert(NULL != arr);	
	
	for(i = 0; i < (length - 1); ++i)
	{
		flag = SORT;
		for(j = 0; j < (length - 1); ++j)
		{
			if(*(arr + j) > *(arr + (j + 1)))
			{
				flag = UNSORT;
				SwapArrInts(arr, (j + 1), j);
			}
		}
		
		if(flag == SORT) 
		{
			break;	
		}
	}
	
	return arr;
}

int *InsertionSort(int *arr, size_t length)
{
	size_t i = 0;
	size_t j = 0;
	int cur_search = 0;
	
	assert(NULL != arr);
	
	for (i = 1; i < length; ++i)
	{
		j = i - 1;
		cur_search = arr[i];
		
		while (0 <= (long)j && cur_search < arr[j])
		{
			arr[j + 1] = arr[j];
			--j;
		}
		
		arr[j + 1] = cur_search;
	}

	return arr;
}

static void SwapArrInts(int *arr, size_t index1, size_t index2)
{
	int temp = 0;
	
	assert(NULL != arr);
	
	temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}



