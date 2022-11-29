/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Chen A
Date: 20/04/2022
File: linear_sort
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef __LINEAR_SORT_H__
#define __LINEAR_SORT_H__

#include <stddef.h>/* size_t */

int CountSort(int *arr, size_t length);

int RadixSort(int *arr, size_t len, size_t chunk_size);

#endif /*__LINEAR_SORT_H__*/
