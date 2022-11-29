/*******************************************************************************
 						
Author: Daniel Jenudi 
Date: 18/5/22
Reviewed By: Karen

********************************************************************************
                             😵️  SORTS 🤯️
********************************************************************************
DESCRIPTION


*******************************************************************************/

#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef int (*s_cmp_func_t)(const void *, const void *);

/*******************************************************************************
								Operations
*******************************************************************************/

int BinarySearchIter(int *arr, int to_find, size_t len);

int BinarySearchRec(int *arr, int to_find, size_t len);

int MergeSort(int *arr, size_t num_elems);

void QuickSort(void *arr, size_t num_elems, size_t elem_size, s_cmp_func_t cmp);


#endif /*__SORTS_H__*/
