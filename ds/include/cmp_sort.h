/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Tom
Date: 20/04/2022
File: cmp_sort
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef __CMP_SORT_H__
#define __CMP_SORT_H__

#include <stddef.h>/* size_t */




int *BubbleSort(int *arr , size_t length);
/*
	BubbleSort
		-O(n^2) time complexity
		-O(1) space complexity
*/
int *SelectionSort(int *arr, size_t length);
/*
	SelectionSort
		-O(n^2) time complexity
		-O(1) space complexity
*/
int *InsertionSort(int *arr ,size_t length);
/*
	InsertionSort
		-O(n^2) time complexity
		-O(1) space complexity
*/


int CountSort(int *arr, size_t length);




#endif /*__CMP_SORT_H__*/

