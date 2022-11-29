/*******************************************************************************
 						
Author: Daniel Jenudi 
Date: 18/5/22
Reviewed By: Karen

********************************************************************************/
#include <stdlib.h> /* for srand */
#include <time.h> /* for time */
#include <stdio.h> /* for printf */


#include "sorts.h"

#define ARRSIZE 5000  
static size_t INT = sizeof(int);

#define RUNTEST(test) {\
            if (!(test))\
            {\
                printf("\x1b[0;34m");\
                printf("OK!\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }


enum return_val
{
	SUCCESS = 0,
	FALSE = 0,
	EQUAL = 0,
	FAILURE = 1,
	TRUE = 1
};

static int CompereInt(int expected_val, int recieved_val, int line);
int CheckArraySorting(int *arr, size_t length);
void PrintArray(int *arr, size_t length);
static void RandomArr(int *arr, size_t length);
static int CmpFunc(const void *pivot, const void *pointer);

int BinarySearchIterTest();
int BinarySearchRecTest();
int MergeSortTest();
int QuickSortTest();

int main()
{
	RUNTEST(BinarySearchIterTest());
	RUNTEST(BinarySearchRecTest());
	RUNTEST(MergeSortTest());
	RUNTEST(QuickSortTest());
	return 0;
}


int BinarySearchIterTest()
{
	int status = 0;
	int arr[] = {1, 3, 6, 9, 10, 11, 13, 15};
	size_t len = sizeof(arr) / sizeof(arr[0]);
	int arr2[] = {1};
	size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
	
	status += CompereInt(SUCCESS, BinarySearchIter(arr, 9, len), __LINE__);
	status += CompereInt(SUCCESS, BinarySearchIter(arr, 15, len), __LINE__);
	status += CompereInt(FAILURE, BinarySearchIter(arr, 28, len), __LINE__);
	
	status += CompereInt(SUCCESS, BinarySearchIter(arr2, 1, len2), __LINE__);
	status += CompereInt(FAILURE, BinarySearchIter(arr2, 5, len2), __LINE__);
	
	return status;
}

int BinarySearchRecTest()
{
	int status = 0;
	int arr[] = {1, 3, 6, 9, 10, 11, 13, 15, 20};
	size_t len = sizeof(arr) / sizeof(arr[0]);
	int arr2[] = {1};
	size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
	
	status += CompereInt(SUCCESS, BinarySearchRec(arr, 1, len), __LINE__);
	status += CompereInt(SUCCESS, BinarySearchRec(arr, 15, len), __LINE__);
	status += CompereInt(FAILURE, BinarySearchRec(arr, 28, len), __LINE__);
	
	status += CompereInt(SUCCESS, BinarySearchRec(arr2, 1, len2), __LINE__);
	status += CompereInt(FAILURE, BinarySearchRec(arr2, 5, len2), __LINE__);
	
	return status;
}

int MergeSortTest()
{
	int status = 0;
	int arr[ARRSIZE];
	    
    clock_t before = 0;
    clock_t after = 0;
    clock_t count_time = 0;
   
    RandomArr(arr, ARRSIZE);
    
	before = clock();
	status += CompereInt(FAILURE, CheckArraySorting(arr, ARRSIZE), __LINE__);
    MergeSort(arr, ARRSIZE);  
    after = clock();
	status += CompereInt(SUCCESS, CheckArraySorting(arr, ARRSIZE), __LINE__);
    count_time = after - before;
    printf("MergeSort Took %lu CPU Time\n", count_time);

	return status;
}

int QuickSortTest()
{
	int status = 0;
	int arr[] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
	size_t len = sizeof(arr) / sizeof(arr[0]);
    int arr2[ARRSIZE];
	int arr3[ARRSIZE];
	    
    clock_t before = 0;
    clock_t after = 0;
    clock_t count_time = 0;
    clock_t qsort_time = 0;
   
    RandomArr(arr2, ARRSIZE);
    RandomArr(arr3, ARRSIZE);
		
	status += CompereInt(FAILURE, CheckArraySorting(arr, len), __LINE__);
	QuickSort(arr, len, INT, CmpFunc);
	status += CompereInt(SUCCESS, CheckArraySorting(arr, len), __LINE__);
	PrintArray(arr, len);
	
	before = clock();
    QuickSort(arr2, ARRSIZE, INT, CmpFunc);  
    after = clock();
    count_time = after - before;
    printf("QuickSort Took %lu CPU Time\n", count_time);


    before = clock();
    qsort(arr3, ARRSIZE, INT, CmpFunc);
    after = clock();
    qsort_time = after - before;
    printf("qsort Took %lu CPU Time\n", qsort_time);
	
    printf("QuickSort Took %lu double CPU Time then qsort\n\n", count_time / qsort_time);
 
	return status;
}

static void RandomArr(int *arr, size_t length)
{
	size_t i = 0;
	
    srand(time(NULL));

    for(i = 0 ; i < length ; ++i)
    {
        arr[i] = rand()%1000;
    }
}

int CheckArraySorting(int *arr, size_t length) 
{
	int status = 0;
	size_t i = 0;
	
	for(i = 0 ; i < (length - 1) ; ++i)/*fix logic to stop at first fail*/
	{
		arr[i] > arr[i + 1] ? ++status : 0;
	}
	
    return !!status;
}

void PrintArray(int *arr, size_t length) 
{
    size_t i = 0;
    
    printf("\n");
    for(i = 0 ; i < length ; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

static int CmpFunc(const void *pivot, const void *pointer) /*my cmp_func*/
{
	return *(int *)pivot - *(int *)pointer;
}
/*אם פיבוט גדול מהפוינטר, יחזיר חיובי 
אחרת יחזיר שלילי  */

/*************************************************************************/


static int CompereInt(int expected_val, int recieved_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("\x1b[1;33m");
		printf("----------------FAIL line %d----------------\n", line);
		printf("expected %d, recieved %d\n",expected_val, recieved_val);
		printf("\x1b[0m");
		return 1;
	}
	
	return 0;
}

