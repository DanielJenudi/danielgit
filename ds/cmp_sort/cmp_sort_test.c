/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Tom
Date: 20/04/2022
File: cmp_sort
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/* printf */
#include <stdlib.h>/* srand, rand, qsort */
#include <time.h>/* time_t, clock_t */
#include <assert.h>/* assert */

#include "cmp_sort.h"

#define ARRSIZE 5000

void TestFunctionBubbleSort();
void TestFunctionSelectionSort();
void TestFunctionInsertionSort();

void TestBenchMarkBubbleSort();
void TestBenchMarkSelectionSort();
void TestBenchMarkInsertionSort();

void InitArr(int *arr);
int CmpFunc(const void *x, const void *y);
void TestResult(int *arr);

int main()
{
	printf("~~~ TestFunction BubbleSort ~~~\n");
	TestFunctionBubbleSort();
	TestBenchMarkBubbleSort();
	printf("~~~ TestFunction SelectionSort ~~~\n");
	TestFunctionSelectionSort();
	TestBenchMarkSelectionSort();
	printf("~~~ TestFunction InsertionSort ~~~\n");
	TestFunctionInsertionSort();
	TestBenchMarkInsertionSort();
	 
	return 0;
}

void TestBenchMarkBubbleSort()
{
	int arr[ARRSIZE];
	clock_t c_start = 0, c_end = 0;

	InitArr(arr);
	c_start = clock();
	BubbleSort(arr, ARRSIZE);
	c_end = clock();
	
	printf("BubbleSort Total time: %ld\n", c_end - c_start);
	
	InitArr(arr);
	c_start = clock();
	qsort(arr, ARRSIZE, sizeof(int), CmpFunc);
	c_end = clock();
	
	printf("qsort Total time: %ld\n\n", c_end - c_start);
}

void TestBenchMarkSelectionSort()
{
	int arr[ARRSIZE];
	clock_t c_start = 0, c_end = 0;

	InitArr(arr);
	c_start = clock();
	SelectionSort(arr, ARRSIZE);
	c_end = clock();
	
	printf("BubbleSort Total time: %ld\n", c_end - c_start);
	
	InitArr(arr);
	c_start = clock();
	qsort(arr, ARRSIZE, sizeof(int), CmpFunc);
	c_end = clock();
	
	printf("qsort Total time: %ld\n\n", c_end - c_start);
}

void TestBenchMarkInsertionSort()
{
	int arr[ARRSIZE];
	clock_t c_start = 0, c_end = 0;

	InitArr(arr);
	c_start = clock();
	InsertionSort(arr, ARRSIZE);
	c_end = clock();
	
	printf("BubbleSort Total time: %ld\n", c_end - c_start);
	
	InitArr(arr);
	c_start = clock();
	qsort(arr, ARRSIZE, sizeof(int), CmpFunc);
	c_end = clock();
	
	printf("qsort Total time: %ld\n\n", c_end - c_start);
}

void TestFunctionBubbleSort()
{
	int arr[ARRSIZE];

	InitArr(arr);	
	BubbleSort(arr, ARRSIZE);
	TestResult(arr);
}

void TestFunctionSelectionSort()
{
	int arr[ARRSIZE];
	
	InitArr(arr);	
	SelectionSort(arr, ARRSIZE);
	TestResult(arr);
}

void TestFunctionInsertionSort()
{
	int arr[ARRSIZE];
	
	InitArr(arr);	
	InsertionSort(arr, ARRSIZE);
	TestResult(arr);
}

void TestResult(int *arr)
{
	int i = 0;
	int result = 0;

	assert(NULL != arr);

	for(i = 0 ; i < (ARRSIZE - 1) ; ++i)
	{
		arr[i] > arr[i + 1] ? ++result : 0;
	}
	
	result > 0 ? printf("FAIL\n\n") : printf("OK\n\n");
}

void InitArr(int *arr)
{
	time_t t;
	int i = 0;
	
	assert(NULL != arr);
	
	srand((unsigned) time(&t));

	for(i = 0 ; i < ARRSIZE ; ++i)
	{
		arr[i] = rand();
	}
}

int CmpFunc(const void *x, const void *y)
{
	assert(NULL != x);
	assert(NULL != y);

	return (*(int *)x - *(int *)y);
}

