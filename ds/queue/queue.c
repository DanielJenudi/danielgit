#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include <stddef.h> /* size_t */

#include "queue.h"
#include "/home/daniel/git/quizzes/PrintTreeByLevel/link_list/link_list.h"

enum CHECK
{
	SUCCESS = 0,
	FAIL
};

struct queue
{
	s_linked_list_t *list;
};

queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}

	queue->list = SLinkedListCreate();
	if (NULL == queue)
	{
		free(queue);
		return NULL;
	}

	return queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);

	SLinkedListDestroy(queue->list);
	free(queue);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	assert(NULL != data);

	if (NULL == SLinkedListInsertBefore(SLinkedListEnd(queue->list), data))
	{
		return FAIL;
	}

	return SUCCESS;
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);

	SLinkedListRemove(SLinkedListBegin(queue->list));
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);

	return SLinkedListGetData(SLinkedListBegin(queue->list));
}

int QueueIsEmpty(const queue_t *queue)
{
	return SLinkedListIsEmpty(queue->list);
}

size_t QueueGetSize(const queue_t *queue)
{
	assert(NULL != queue);

	return SLinkedListCount(queue->list);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	dest->list = SLinkedListAppend(dest->list, src->list);
	free(src);

	return dest;
}
