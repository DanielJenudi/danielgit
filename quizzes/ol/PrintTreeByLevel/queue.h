/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Amir Topaz 
Date: 15/03/2022
File: Data struct - Queue
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Data struct - Queue
********************************************************************************

Attributes and policy:
-   peek or remove the first element that enter the queue, FIFO 
-   can insert element only to the end of the line 
-   Holds elements by reference
-------------------------------------------------------------------------------

Operations on DS:
- create queue
- destroy queue
- add an element to the back of the queue, FIFO
- peek the front element of the queue
- removes an element from the front of the queue
- get the number of elements in queue 
- get if queue is empty
- append two queues together

*******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */


/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct queue queue_t;

/*******************************************************************************
QueueCreate
Description: creates a new queue
Return value:
	- return a new queue, in case of failure return null
Complexity: O(1) time
Notes: create dummy node ,that alwase be the last node, pointing to NULL and
store data pointer to NULL.
*******************************************************************************/
queue_t *QueueCreate(void);

/******************************************************************************
QueueDestroy
Description: destroy a queue
Parameters: 
	- queue
Complexity: O(1) time
*******************************************************************************/
void QueueDestroy(queue_t *queue);

/*******************************************************************************
QueueEnqueue
Description: insert new element to the end of the line
Parameters: 
	- queue
	-pointer to data
Return value:
	- boulian value if the insert succeeded
Complexity: O(n) time 
*******************************************************************************/
int QueueEnqueue(queue_t *queue, void *data);

/*******************************************************************************
QueueDequeue
Description: removes an element from the front of the queue
Parameters: 
	- queue
Complexity: O(1) time
Notes: if the queue is empty, the behavior is undefined.
*******************************************************************************/
void QueueDequeue(queue_t *queue);

/*******************************************************************************
QueueGetSize
Description: return the number of elements in a queue
Parameters: 
	- queue
Return value:
	- the number of elements in a queue
Complexity: O(n) time 
*******************************************************************************/
size_t QueueGetSize(const queue_t *queue);

/*******************************************************************************
QueueIsEmpty
Description: return if queue is empty
Parameters: 
	- queue
Return value:
	- return 1 if queue is empty, else return 0
Complexity: O(1) time
*******************************************************************************/
int QueueIsEmpty(const queue_t *queue);

/*******************************************************************************
QueuePeek
Description: get pointer to the front element data
Parameters: 
	- queue
Return value:
	- pointer to element data
Complexity: O(1) time
*******************************************************************************/
void *QueuePeek(const queue_t *queue);

/*******************************************************************************
QueueAppend
Description: append two queues together and returns the combain queue
Parameters: 
	- two queues
Return value:
	- queue of the appended two queues
Complexity: O(1) time
Notes: queue src will destroy
*******************************************************************************/
queue_t *QueueAppend(queue_t *dest ,queue_t *src);

#endif /*__QUEUE_H__*/


