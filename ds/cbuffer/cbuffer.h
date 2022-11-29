/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Osher 
Date: 19/03/2022
File: Data struct - Circular Buffer
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/*******************************************************************************
                        Data struct - Circular Buffer
********************************************************************************

Attributes and policy:
-   add or remove number of bytes from the circular buffer to a buffer,
    in FIFO methodology.
-   fixed size, the user determine the capicity, in bytes, at start.
-   can insert element only to the end of the circular buffer. 
-   Holds value by bytes.
-   can't overwrite data.

-------------------------------------------------------------------------------

Operations on DS:
- create circular buffer.
- destroy circular buffer.
- add number of bytes to the back of the circular buffer, FIFO.
- remove to buffer number of bytes to the of the circular buffer.
- removes an element from the front of the circular buffer.
- get the number of bytes in circular buffer.
- get the bytes capacity of a circular buffer.
- get if circular buffer is empty.
- get free space in circular buffer.

*******************************************************************************/

#ifndef __CBUFFER__
#define __CBUFFER__


#include <stddef.h>/*size_t*/
#include <unistd.h>/*ssize_t*/

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct circular_buffer c_buffer_t;

/*******************************************************************************
CBufferCreate
Description: creates a new circular buffer.
Parameters: 
	- capacity(in bytes).
Return value:
	- return a new circular buffer, in case of failure return null.
Complexity: O(1) time
*******************************************************************************/
c_buffer_t *CBufferCreate(size_t capacity);

/******************************************************************************
CBufferDestroy
Description: destroy a circular buffer
Parameters: 
	- circular buffer
Complexity: O(1) time
*******************************************************************************/
void CBufferDestroy(c_buffer_t *c_buffer);

/*******************************************************************************
CBufferWrite
Description: insert number of bytes from a buffer to a circular buffer.
Parameters: 
	- circular buffer
	- buffer source
	- count(number of bytes)
	undifine behavior for count larger then source.
Return value:
	- the number of bytes that successfully copied into the circular buffer.
Complexity: O(n) time 
*******************************************************************************/
ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count);

/*******************************************************************************
CBufferRead
Description: insert number of bytes from a circular buffer to a buffer.
Parameters: 
	- circular buffer
	- buffer destenation
	- count(number of bytes)
	- undifine behavior for count larger then dest.
Return value:
	- the number of bytes that successfully copied into the buffer.
Complexity: O(n) time 
*******************************************************************************/
ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count);

/*******************************************************************************
CBufferCapacity
Description: return the capacity of circular buffer
Parameters: 
	- circular buffer
Return value:
	- the capacity of circular buffer
Complexity: O(1) time 
*******************************************************************************/
size_t CBufferCapacity(const c_buffer_t *c_buffer);

/*******************************************************************************
CBufferIsEmpty
Description: return if circular buffer is empty
Parameters: 
	- circular buffer
Return value:
	- return 1 if circular buffer is empty, else return 0
Complexity: O(1) time
*******************************************************************************/
int CBufferIsEmpty(const c_buffer_t *c_buffer);

/*******************************************************************************
CBufferFreeSpace
Description: return free space (in bytes) in circular buffer.
Parameters: 
	- circular buffer
Return value:
	- free space (in bytes) in circular buffer.
Complexity: O(1) time
*******************************************************************************/
size_t CBufferFreeSpace(const c_buffer_t *c_buffer);

#endif /*__QUEUE_H__*/



