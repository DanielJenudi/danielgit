/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Tom 
Date: 18/05/2022
File: Data struct - Hash Table
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/*******************************************************************************
                                    DS
****************************************************************************  
attributes and policy:
-	?FIFO,  random access?
-	Holds elements by value? reference?
-	growth factor - dynamic. 

-------------------------------------------------------------------------------

Operations on DS:
- 

*******************************************************************************/


#ifndef __HT__
#define __HT__

#include <stddef.h> /* size_t */
#include "dll.h"

typedef struct ht ht_t;

typedef size_t (*ht_hash_func_t)(const void *data, void *param);
typedef int (*ht_cmp_func_t)(const void *data, const void *ht_data, void *param);
typedef int (*ht_action_func_t)(void *data, void *param); 



ht_t *HTCreate(ht_hash_func_t ht_func, void *ht_param, ht_cmp_func_t cmp, void *cmp_param,  size_t entries);
/*O(1) / O(n)*/

void HTDestroy(ht_t *ht);
/*O(n)*/

int HTInsert(ht_t *ht, void *data);
/*O(1)*/

void HTRemove(ht_t *ht, void *data);
/*O(1)*/

size_t HTSize(const ht_t *ht);
/*O(n)*/

void *HTFind(ht_t *ht, void *data);
/*O(1) - amortized*/

int HTIsEmpty(const ht_t *ht);
/*O(n)*/

int HTForEach(ht_t *ht, ht_action_func_t act, void *action_param);
/*O(n)*/


/*******************************************************************************
                                 Typedefs
*******************************************************************************/


/*******************************************************************************
                                Functions
*******************************************************************************/

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

#endif /* __HT__ */

