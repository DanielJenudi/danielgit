/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Schreiber 
Date: 10/04/2022
File: Varible-Size Allocator
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Varible-Size Allocator
********************************************************************************

Attributes and policy:
- get memory pool to mange
- for every allocation VSA take space for managing
- return only aligned address
- defragmentation empty blocks happens only for Prolonged blocks

-------------------------------------------------------------------------------

Operations on DS:
- init VSA
- alloc from VSA free space
- free block back to VSA for reuse
- get largest free space in VSA

*******************************************************************************/

#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct block_header_t vsa_t;

/*******************************************************************************
                                 Operations
*******************************************************************************/

/*******************************************************************************
VSAInit
Description: initialize memory pool to be managed by VSA
Parameters: 
	- memory pool
	- pool size
Return value:
	- VSA
Complexity: O(1) time
Notes: undefined behavior for pool size smaller than 2 words
*******************************************************************************/
vsa_t *VSAInit(void *m_pool, size_t pool_size);

/*******************************************************************************
FSAAlloc
Description: alloc block of memory from VSA for user use
Parameters: 
	- VSA
	-block size in bytes
Return value:
	- pointer to new free space, if fail return NULL
Complexity: O(n) time
Notes: fail in case of not enough free space, return only aligned address
*******************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t n_bytes);

/*******************************************************************************
VSAFree
Description: free block of memory back to VSA
Parameters: 
	- block to free
Complexity: O(1) time
Notes: free same block twice is undefined behavior
*******************************************************************************/
void VSAFree(void *block);

/*******************************************************************************
VSALargestFreeBlock
Description: return the largest free block in a VSA
Parameters: 
	- VSA
Return value:
	- the largest free block in a VSA
Complexity: O(n) time 
*******************************************************************************/
size_t VSALargestFreeBlock(vsa_t *vsa);

#endif /*__VSA_H__*/



