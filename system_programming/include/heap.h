/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 25/05/2022
File: Data Structures - Heap
Description: Implementing heap data structure
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/***************************************************************************
                                    DS
****************************************************************************  
attributes and policy:
-	
-------------------------------------------------------------------------------

Operations on DS:
- 

*******************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/
typedef int (*heap_cmp_func_t)(const void *new_data, const void *current_data,
							   void *cmp_param);
/*
return 0 if equal
returns > 1 if new_data > current_data
returns < 1 if new_data < current_data
*/

typedef int (*is_match_t)(const void *data, const void *heap_data, void *param);
/*
bool return: 1 if match, 0 if not a match
*/
typedef struct heap heap_t;

/*******************************************************************************
                                Functions
*******************************************************************************/

heap_t *HeapCreate(heap_cmp_func_t cmp, void *cmp_param);
/*O(1) */

void HeapDestroy(heap_t *heap);
/*O(1)*/

int HeapPush(heap_t *heap, void *new_data);
/*O(lon n) */

void *HeapPop(heap_t *heap);
/*O(lon n) */

void *HeapRemove(heap_t *heap, void *to_remove, 
				is_match_t match_func, void *match_param);
/*O(n) */

void *HeapPeek(heap_t *heap); 
/*O(1)*/

size_t HeapSize(const heap_t *heap);
/*O(1) */

int HeapIsEmpty(const heap_t *heap);
/*O(1)*/

void PrintTree(heap_t *heap);

/******************************************************************************
-----
Description: ----
Parameters: 
	- 
Return value:
	- 
Complexity: 
Notes:

*****************************************************************************/

#endif /* __HEAP_H__ */