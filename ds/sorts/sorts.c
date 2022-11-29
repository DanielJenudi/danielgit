/*******************************************************************************
 						
Author: Daniel Jenudi 
Date: 18/5/22
Reviewed By: Karen

********************************************************************************/

#include <assert.h>/* assert */
#include <string.h>/* memcpy */
#include <stdlib.h>/* malloc, free */

#include "sorts.h"

enum status
{
	SUCCESS = 0,
	ALLOC_FAIL = 1,
	FAIL = 1
};

static void MergAndSort(int *arr1, size_t len1, int *arr2, size_t len2, 
						int *result);
static void SwapData(char *data1, char *data2, size_t elem_size);

int BinarySearchIter(int *arr, int to_find, size_t len)
{
	int *middle = NULL;
	int *end = NULL;
	
	assert(NULL != arr);
	assert(0 != len);
	
	end = arr + (len - 1);
	
	while(0 != len)
	{
		middle = arr + (len / 2);
		
		if(*middle == to_find)
		{
			return SUCCESS;
		}
		else if((to_find > *middle) && (middle != end))
		{
			arr = middle + 1;
		}
		
		len /= 2;
	}
	
	return FAIL;
}

int BinarySearchRec(int *arr, int to_find, size_t len)
{
	int *middle = NULL;
	int *end = NULL;

	assert(NULL != arr);

	end = arr + (len - 1);

	if(0 != len)
	{
		middle = arr + (len / 2);

		if(*middle == to_find)
		{
			return SUCCESS;
		}
		else if((to_find > *middle) && (middle != end))
		{
			return BinarySearchRec(middle + 1, to_find, len / 2);
		}
		else
		{
			return BinarySearchRec(arr, to_find, len / 2);
		}
	}

	return FAIL;
}

int MergeSort(int *arr, size_t num_elems)
{
	size_t len_arr = 0;
	size_t len_arr2 = 0;
	int *arr2 = NULL;
	int *result = NULL;
	
	assert(NULL != arr);
	assert(0 != num_elems);

	if(1 == num_elems)
	{
		return SUCCESS;
	}

	result = (int *)malloc(num_elems * sizeof(int));
	if(NULL == result)
	{
		return ALLOC_FAIL;
	}

	len_arr = (num_elems / 2);
	len_arr2 = (num_elems - len_arr);
	
	arr2 = arr + len_arr;
	
	if(ALLOC_FAIL == MergeSort(arr, len_arr))
	{
		return ALLOC_FAIL;
	}
	
	if(ALLOC_FAIL == MergeSort(arr2 , len_arr2))
	{
		return ALLOC_FAIL;
	}
	
	MergAndSort(arr, len_arr, arr2, len_arr2, result);
	memcpy(arr, result, sizeof(int) * num_elems);
	
	free(result);
	result = NULL;
	
	return SUCCESS;
}

static void MergAndSort(int *arr1, size_t len1, int *arr2, size_t len2, 
						int *result)
{
	assert(NULL != arr1);
	assert(NULL != arr2);
	assert(NULL != result);

	if(0 != len1 && 0 != len2)
	{
		if(*arr1 < *arr2)
		{
			memcpy(result, arr1, sizeof(int));
			MergAndSort(arr1 + 1, len1 - 1, arr2, len2, result + 1);
		}
		else
		{
			memcpy(result, arr2, sizeof(int));
			MergAndSort(arr1, len1, arr2 + 1, len2 - 1, result + 1);
		}
	}
	else
	{
		if(0 != len1)
		{
			memcpy(result, arr1, sizeof(int) * len1);
		}
		else
		{
			memcpy(result, arr2, sizeof(int) * len2);
		}
	}
}

void QuickSort(void *arr, size_t num_elems, size_t elem_size, s_cmp_func_t cmp)
{
	char *pivot = NULL;
	char *start = NULL;
	char *end = NULL;

	size_t len_before_pivot = 0;
	size_t len_after_pivot = 0;

	assert(NULL != arr);
	assert(NULL != cmp);
	assert(0 < elem_size);

	if(2 > num_elems)
	{
		return;
	}

	start = arr;
	pivot = (char *)arr + (num_elems - 1) * elem_size;
	end = pivot - elem_size;

	while(start <= end)
	{
		if(0 < cmp(start, pivot))
		{
			SwapData(start, end, elem_size);
			SwapData(end, pivot, elem_size);
			pivot = end;
			end -= elem_size; 
		}
		else
		{
			start += elem_size;  
		}
	}

	len_before_pivot = (pivot - (char *)arr) / elem_size;
	len_after_pivot = num_elems - len_before_pivot - 1;

	QuickSort(arr, len_before_pivot, elem_size, cmp);
	QuickSort(pivot + elem_size, len_after_pivot, elem_size, cmp);
}

static void SwapData(char *data1, char *data2, size_t elem_size)
{
	char temp = 0;
	size_t i = 0;

	assert(NULL != data1);
	assert(NULL != data2);

	for(i = 0; i < elem_size; ++i)
	{
		temp = *data1;
		*data1 = *data2;
		*data2 = temp;

		++data1;
		++data2;
	}	
}


