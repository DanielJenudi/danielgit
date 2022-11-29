/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: adiya 
Date: 24/03/2022
File: Data struct - Sorted List
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h>/*printf*/

#include "sl.h"/* sl.h */

#ifdef NDEBUG
static int SameList(sl_iterator_t from, sl_iterator_t to);
#endif /* NDEBUG */
static sl_iterator_t InitIter(void);


struct sl
{
    dll_list_t *list;
    sl_cmp_func_t cmp_func;
    void *param;
};

static sl_iterator_t InitIter(void)
{
	return	NULL;
}

sl_t *SLCreate(sl_cmp_func_t cmp_func, void *param)
{
	sl_t *sl_list = NULL;

	assert(NULL != cmp_func);

	sl_list = (sl_t *)malloc(sizeof(sl_t));	
	if(NULL == sl_list)
	{	
		return NULL;	
	}
	
	sl_list->list = DLLCreate();
	if(NULL == sl_list->list)
	{	
		free(sl_list);
		return NULL;	
	}
	
	sl_list->cmp_func = cmp_func;
	sl_list->param = param;

	return sl_list;
}

void SLDestroy(sl_t *list)
{
	assert(NULL != list);
	DLLDestroy(list->list);
	free(list);
	list = NULL;
}


static sl_iterator_t SLSearch(const sl_t *list, const sl_iterator_t from,
 					          const sl_iterator_t to, const void *data, 
 					          int exit_status)
{
	sl_iterator_t runner = InitIter();
	int checker = 0;
	
	assert(NULL != list);
	assert(InitIter() != from);
	assert(InitIter() != to);
	assert(0 == exit_status || 1 == exit_status);
	#ifdef NDEBUG
	assert(SameList(from, to));
	#endif /* NDEBUG */	
	
	runner = (sl_iterator_t)from;
	checker = list->cmp_func(data, SLGetData(runner), list->param);
	
 	while(
 		  !SLIsIterEqual(runner, to) && 
		  ((!!checker != exit_status) || (0 > checker))
		 )
	{
		runner = SLNext(runner);
		checker = list->cmp_func(data, SLGetData(runner), list->param);
	}
	
	return runner; 
}

sl_iterator_t SLFind(const sl_t *list, const sl_iterator_t from,
 					 const sl_iterator_t to, const void *data)
{
	assert(NULL != list);
	assert(NULL != data);
	assert(InitIter() != from);
	assert(InitIter() != to);
	#ifdef NDEBUG
	assert(SameList(from, to));
	#endif /* NDEBUG */
	
	
	return SLSearch(list, from, to, data, 0);
}

sl_iterator_t SLFindIf(sl_is_match_func_t is_match, void *param, 
					   const sl_iterator_t from, const sl_iterator_t to)
{
	assert(NULL != is_match);
	assert(NULL != param);
	assert(InitIter() != from);
	assert(InitIter() != to);
	#ifdef NDEBUG
	assert(SameList(from, to));
	#endif /* NDEBUG */
	

	return DLLFindMatch(is_match, param, from, to);
}

sl_iterator_t SLInsert(sl_t *list, void *data)
{
	sl_iterator_t where = InitIter();
	
	assert(NULL != list);
	assert(NULL != data);

	where = SLSearch(list, SLBegin(list), SLEnd(list), data, 1);
	
	return DLLInsertBefore(where, data);
}

sl_iterator_t SLRemove(sl_iterator_t where)
{
	assert(InitIter() != where);
	return DLLRemove(where);
}

void *SLPopFront(sl_t *list)
{
	return DLLPopFront(list->list);
}
void *SLPopBack(sl_t *list)
{
	return DLLPopBack(list->list);
}

sl_iterator_t SLBegin(const sl_t *list)
{
	assert(NULL != list);
	return DLLBegin(list->list);
}

sl_iterator_t SLEnd(const sl_t *list)
{
	assert(NULL != list);
	return DLLEnd(list->list);
}

sl_iterator_t SLNext(const sl_iterator_t iter)
{
	assert(InitIter() != iter);
	return DLLNext(iter);
}

sl_iterator_t SLPrev(const sl_iterator_t iter)
{
	assert(InitIter() != iter);
	return DLLPrev(iter);	
}

int SLIsIterEqual(const sl_iterator_t iter1, const sl_iterator_t iter2)
{
	return DLLIsIterEqual(iter1, iter2);
}

size_t SLCount(const sl_t *list)
{
	assert(NULL != list);
	return DLLCount(list->list);
}

void *SLGetData(const sl_iterator_t iter)
{
	assert(InitIter() != iter);
	return DLLGetData(iter);
}

int SLIsEmpty(const sl_t *list)
{
	assert(NULL != list);
	return DLLIsEmpty(list->list);
}

int SLForEach(sl_action_func_t action_func, void *param, 
			  const sl_iterator_t from, const sl_iterator_t to)
{
	assert(NULL != action_func);
	assert(NULL != param);
	assert(InitIter() != from);
	assert(InitIter() != to);
	#ifdef NDEBUG
	assert(SameList(from, to));
	#endif /* NDEBUG */
	
	return DLLForEach(action_func, param, from, to);
}

sl_t *SLMerge(sl_t *dest, sl_t *src)
{
	sl_iterator_t dest_iter = InitIter();
	sl_iterator_t src_iter = InitIter();
	
	assert(NULL != dest);
	assert(NULL != src);
	
	dest_iter = SLBegin(dest);
	src_iter = SLBegin(src);
	
	while(!SLIsEmpty(src))
	{
		dest_iter = SLSearch(dest, dest_iter, SLEnd(dest),
							 SLGetData(SLBegin(src)), 1);
		
		if(!SLIsIterEqual(dest_iter, SLEnd(dest)))
		{
			src_iter = SLSearch(src, src_iter, SLEnd(src),
							SLGetData(dest_iter), 0);
							
			if(SLIsIterEqual(src_iter, SLEnd(src)))
			{
				src_iter = SLSearch(src, SLBegin(src), SLEnd(src),
							SLGetData(dest_iter), 1);
			}
		}
		else
		{
			src_iter = SLEnd(src);
		}
				
		DLLSplice(dest_iter, SLBegin(src), src_iter);
	}	

	return dest;
}

#ifdef NDEBUG
static int SameList(sl_iterator_t from, sl_iterator_t to)
{
	assert(InitIter() != from);
	assert(InitIter() != to);
	
	while(!SLIsIterEqual(from, to) && InitIter() != from)
	{
		from = SLNext(from);
	}
	
	return to == from;
}
#endif /* NDEBUG */










