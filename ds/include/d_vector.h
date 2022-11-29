/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Chen Rudi 
Date: 09/03/2022
File: Data struct - Dynamic vactor
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Data struct - Dynamic vactor
********************************************************************************

Attributes and policy:
-   LIFO 
-	Random access
-   Holds elements by value
-   growth : when push, element capacity multiplier by 2 when reach max capacity
			 when pop, element capacity divid by 2 when reach to 1\4 capacity
-------------------------------------------------------------------------------

Operations on DS:
- create vector
- destroy vector
- push back  
- pop back
- get value of  the index place in vector
- get element capacity
- get the number of elements in vector
- get if vector is empty
- resize vector
- fit vector to minimaize size

*******************************************************************************/

#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct vector d_vector_t; 

/*******************************************************************************
VectorCreate
Description: creates a new dynamic vector
Parameters: 
	- capacity: initial number of elements to be stored. 
	- element_size: size of each element
Return value:
	- in case of failure, will return null
Complexity: O(n) time, 
Notes: if num of elements is zero, default capacity will be given.
*******************************************************************************/
d_vector_t *VectorCreate(size_t element_size, size_t capacity);

/******************************************************************************
VectorDestroy
Description: destroy a dynamic vector
Parameters: 
	- vector
Complexity: O(n) time, 
*******************************************************************************/
void VectorDestroy(d_vector_t *vector);

/*******************************************************************************
VectorSize
Description: return the number of elements in a vector
Parameters: 
	- vector
Return value:
	- the number of elements in a vector
Complexity: O(1) time, 
*******************************************************************************/
size_t VectorSize(const d_vector_t *vector);

/*******************************************************************************
Vectorcapacity
Description: return the max number of elements that can fit in a vector
Parameters: 
	- vector
Return value:
	- the max number of elements that can fit in a vector
Complexity: O(1) time, 
*******************************************************************************/
size_t Vectorcapacity(const d_vector_t *vector);

/*******************************************************************************
VectorPushBack
Description: push element to the end of a vector
Parameters: 
	- vector 
	- data: get in (void *) but save by value
Return value:
	- in case of realloc failure, will return 1
Complexity: O(1) time, 
Notes: if num of elements reach max capacity, capacity multiplier by 2
*******************************************************************************/
int VectorPushBack(d_vector_t *vector,const void *data);

/*******************************************************************************
VectorPopBack
Description: pop element from the end of a vector
Parameters: 
	- vector
Return value:
	- in case of realloc failure, will return 1
Complexity: O(1) time, 
Notes: if num of elements reach 1/4 capacity or below, capacity divid by 2
*******************************************************************************/
int VectorPopBack(d_vector_t  *vector);

/*******************************************************************************
VectorGetElement
Description: get value of the index place in vector
Parameters: 
	- vector
	- index
Return value:
	- the value of index place in vector
Complexity: O(1) time, 
Notes: reach to index place that bigger then vector size is undifine.
*******************************************************************************/
void *VectorGetElement(const d_vector_t *vector, size_t index);

/*******************************************************************************
VectorIsEmpty
Description: return if vector is empty
Parameters: 
	- vector
Return value:
	- return 1 if vector is empty, else return 0
Complexity: O(1) time, 
*******************************************************************************/
int VectorIsEmpty(const d_vector_t *vector);

/*******************************************************************************
VectorReserve
Description: realloc vector capacity
Parameters: 
	- vector. 
	- new_capacity
Return value:
	- in case of failure, will return 1 else return 0
Complexity: O(n) time, 
Notes: if num of elements is biger from new_capacity, vector resize to number of
elements + 1.
*******************************************************************************/
int VectorReserve(d_vector_t *vector, size_t new_capacity);

/*******************************************************************************
VectorShrinkToFit
Description: fit vector to minimaize size
Parameters: 
	- vector. 
Return value:
	- in case of failure, will return 1 else return 0
Complexity: O(n) time, 
Notes: vector resize to number of elements + 1.
*******************************************************************************/
int VectorShrinkToFit(d_vector_t *vector);

#endif /*__DYNAMIC_VECTOR_H__*/

