/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Rani 
Date: 27/03/2022
File: Data struct - Priorety queue
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc, free*/


#include "pq_sl.h"/* pq.h */
#include "sl.h"/* sl.h */

struct pq
{
	sl_t *queue;
};

typedef sl_iterator_t pq_iterator_t;


pq_t *PQCreate(pq_cmp_func_t cmp_func, void *param)
{
	pq_t *pq = NULL;
	
	assert(NULL != cmp_func);
	
	pq = (pq_t *)malloc(sizeof(pq_t));
	
	if(NULL == pq)
	{	
		return NULL;	
	}
	
	pq->queue = SLCreate(cmp_func, param);
	
	if(NULL == pq->queue)
	{
		free(pq);
		pq = NULL;
		return NULL;
	} 
	
	return pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	SLDestroy(pq->queue);
	pq->queue = NULL;
	free(pq);
	pq = NULL;
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	assert(NULL != data);
	
	return DLLIsIterEqual(SLInsert(pq->queue, data), SLEnd(pq->queue));
}

void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	return SLPopFront(pq->queue);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	return SLIsEmpty(pq->queue);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);	
	return SLGetData(SLBegin(pq->queue));
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);	
	return SLCount(pq->queue);
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);	

	while(!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pq_t *pq, void *param, pq_is_match_t is_match)
{
	pq_iterator_t iter = NULL;
	void *data = NULL;
	
	assert(NULL != pq);		
	assert(NULL != is_match);

	iter = SLFindIf(is_match, param, SLBegin(pq->queue), SLEnd(pq->queue));
	if(SLEnd(pq->queue) == iter)
	{
		return NULL;
	}
	
	data = SLGetData(iter);
	SLRemove(iter);
	
	return data;
}



