/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Chen A
Date: 20/04/2022
File: linear_sort
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/* printf */

#include "linear_sort.h"


void TestCountSort();
void TestRadixSort();
void PrintArr(int *arr, size_t size);

int main()
{
    printf("~~~ TestCountSort ~~~\n");
    TestCountSort();
    printf("~~~ TestRadixSort ~~~\n");
    TestRadixSort();
  
    return 0;
}

void TestRadixSort()
{
    int arr[] = {5, 7, 0, 2, 4, 1000, 5, 1, 12, 14, 12, 10, 20, 99, 71, 321};

    PrintArr(arr, sizeof(arr)/sizeof(int));
    RadixSort(arr, sizeof(arr)/sizeof(int), 2);
    PrintArr(arr, sizeof(arr)/sizeof(int));
}

void TestCountSort()
{
    int arr[] = {5, -7, 1, 2, 4, 21, 5, 1, -12, -14, -12};

    PrintArr(arr, sizeof(arr)/sizeof(int));
    CountSort(arr, sizeof(arr)/sizeof(int));
    PrintArr(arr, sizeof(arr)/sizeof(int));
}

void PrintArr(int *arr, size_t size)
{
    size_t i = 0;
    
    for(i = 0; i < size; ++i)
    {
        printf("index %lu: %d\n", i, *(arr + i));
    }
    
    printf("\n");
}
