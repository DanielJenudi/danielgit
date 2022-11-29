/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Rani
Date: 20/03/2022
File: Data struct - DLL
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "dll.h"

typedef struct DLL_node dll_node_t;

struct DLL_node
{
    void *data;
    dll_node_t *next;
    dll_node_t *prev;
};

struct DLL_list 
{
    dll_node_t *head;
    dll_node_t *tail;
};

enum
{
	ALLFAIL = -1,
	FALSE = 0,
	SUCCESS = 0,
	FAIL = 1,
	TRUE = 1
};

static dll_iterator_t InitIter(void);
static int IsHead(dll_iterator_t iter);
static dll_iterator_t DLLSpliceDestHead(dll_iterator_t dest, dll_iterator_t from,
						 dll_iterator_t to);


static dll_iterator_t InitIter(void)
{
	return	NULL;
}

dll_list_t *DLLCreate(void)
{
	dll_list_t *list = NULL;
	dll_node_t *dummy_node = NULL;
	
	list = (dll_list_t *)malloc(sizeof(dll_list_t));
	if(NULL == list)
	{
		return NULL;	
	}
	
	dummy_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	if(NULL == dummy_node)
	{
		free(list);
		return NULL;
	}
	
	dummy_node->data = list;
	dummy_node->next = NULL;
	dummy_node->prev = dummy_node;
	
	list->head = dummy_node;
	list->tail = dummy_node;

	return list;
}

void DLLDestroy(dll_list_t *list)
{
	dll_iterator_t runner = InitIter();
	dll_iterator_t temp_next = InitIter();
	
	assert(NULL != list);
	
	runner = DLLBegin(list);
	
	while(NULL != runner)
	{
		temp_next = runner->next;
		free(runner);
		runner = temp_next;
	}
	
	free(list);
	list = NULL;
}

static int IsHead(dll_iterator_t iter)
{
	assert(InitIter() != iter);
	
	return NULL == iter->prev->next; 
}

dll_iterator_t DLLBegin(const dll_list_t *list)
{
	assert(NULL != list);
	
	return list->head;
}

dll_iterator_t DLLEnd(const dll_list_t *list)
{
	assert(NULL != list);
	
	return list->tail;
}

dll_iterator_t DLLNext(const dll_iterator_t iter)
{
	assert(InitIter() != iter);
	
	return iter->next;
}

dll_iterator_t DLLPrev(const dll_iterator_t iter)
{
	assert(InitIter() != iter);
	assert(!IsHead(iter));
	
	return iter->prev;
}

int DLLIsEmpty(const dll_list_t *list)
{
	assert(NULL != list);
	
	return (NULL == list->head->next);
}

void *DLLGetData(const dll_iterator_t where)
{
	assert(InitIter() != where);
	
	return where->data;	
}

void DLLSetData(dll_iterator_t where, void *new_data)
{
	assert(InitIter() != where);
	
	where->data = (void *)new_data;
}

int DLLIsIterEqual(const dll_iterator_t iter1, const dll_iterator_t iter2)
{
	return (iter1 == iter2);
}

size_t DLLCount(const dll_list_t *list)
{
	dll_iterator_t runner = InitIter();
	int count = 0;
	
	assert(NULL != list);
	
	runner = DLLBegin(list);
	
	while(InitIter() != DLLNext(runner))
	{
		++count;
		runner = DLLNext(runner);
	} 

	return count;
}

dll_iterator_t DLLInsertBefore(dll_iterator_t where, void *data)
{
	dll_node_t *new_node = NULL;
	
	assert(InitIter() != where);
	
	new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	if(NULL == new_node)
	{
		while(InitIter() != where->next)
		{
			where = where->next;
		}
		return where;
	}
	
	new_node->data = (void *)data;
	new_node->next = where;
	new_node->prev = where->prev;
	
	where->prev = new_node;
	
	if(IsHead(new_node))
	{
		((dll_list_t *)(new_node->prev->data))->head = new_node;
	}
	else
	{	
		new_node->prev->next = new_node;
	}
	
	
	return new_node;
}

dll_iterator_t DLLRemove(dll_iterator_t iter)
{
	dll_iterator_t next = InitIter();
	dll_iterator_t prev = InitIter();
    
    assert(InitIter() != iter);
    assert(InitIter() != iter->next);
    
    next = iter->next;
    prev = iter->prev;
    
    next->prev = prev;
    
    if(IsHead(iter))
	{ 
		((dll_list_t *)(prev->data))->head = next;
	}
	else
	{	
		prev->next = next;
	}
    
    free(iter);
    iter = InitIter();
    
    return next;
}

int DLLPushFront(dll_list_t *list, void *data)
{
	dll_iterator_t iter = InitIter();

	assert(NULL != list);
	assert(NULL != data);
	
	iter = DLLBegin(list);
	iter = DLLInsertBefore(iter, data);
	
	return (DLLEnd(list) == iter);
}

int DLLPushBack(dll_list_t *list, void *data)
{
	dll_iterator_t iter = InitIter();

	assert(NULL != list);
	assert(NULL != data);
	
	iter = DLLEnd(list);
	iter = DLLInsertBefore(iter, data);
	
	return (DLLEnd(list) == iter);
}

void *DLLPopFront(dll_list_t *list)
{
	void *data = NULL;
	
	assert(NULL != list);
	
	data = DLLGetData((DLLBegin(list)));
	
	DLLRemove(DLLBegin(list));
	
	return data;
}

void *DLLPopBack(dll_list_t *list)
{
	void *data = NULL;
	
	assert(NULL != list);
	
	data = DLLGetData(DLLPrev(DLLEnd(list)));
	
	DLLRemove(DLLPrev(DLLEnd(list)));
	
	return data;
}

int DLLForEach(action_func_t action_func, 
			   void *param, const dll_iterator_t from, const dll_iterator_t to)
{

	dll_iterator_t runner = InitIter();
	int status = 0;
	
	assert(NULL != action_func);
	assert(NULL != param);
	assert(InitIter() != from);
	assert(InitIter() != to);
	
	runner = (dll_iterator_t)from;

	while(!DLLIsIterEqual(runner, to) &&
		  FAIL != action_func(DLLGetData(runner), param))
	{
		runner = DLLNext(runner);
		++status;
	}
	
	if(to != runner)
	{
		status = (0 == status ? -1 : status);
	}
	else
	{
		status = 0;
	}
	
	
	return status;
}

dll_iterator_t DLLFindMatch(is_match_func_t is_match, void *param, 
							const dll_iterator_t from, const dll_iterator_t to)
{
	dll_iterator_t runner = InitIter();

	assert(NULL != is_match);
	assert(NULL != param);
	assert(InitIter() != from);
	assert(InitIter() != to);
	
	runner = (dll_iterator_t)from;

	while(!DLLIsIterEqual(runner, to) && 
		  !is_match(DLLGetData(runner), param))
	{	
		runner = DLLNext(runner);
	}
	
	return runner;
}

int DLLMultiFind(is_match_func_t is_match, void *param,
		         const dll_iterator_t from, const dll_iterator_t to,
		         dll_list_t *result)
{
	dll_iterator_t runner = InitIter();
	int status = 0;
	
	assert(NULL != result);
	assert(NULL != is_match);
	assert(NULL != param);
	assert(InitIter() != from);
	assert(InitIter() != to);
	
	
	runner = (dll_iterator_t)from;
	
	while(!DLLIsIterEqual(runner, to))
	{	
		if(TRUE == is_match(DLLGetData(runner), param))
		{
			if(FAIL == DLLPushBack(result, DLLGetData(runner)))
			{
				return (0 == status ? ALLFAIL : status);
			}
			
			++status;
		}
		
		runner = DLLNext(runner);
	}
	
	return SUCCESS;
}    

dll_iterator_t DLLSplice(dll_iterator_t dest, dll_iterator_t from,
						 dll_iterator_t to)
{
	dll_iterator_t dest_original_prev = InitIter();
	dll_iterator_t to_original_prev = InitIter();
	
	assert(InitIter() != dest);
	assert(InitIter() != from);
	assert(InitIter() != to);

	if(IsHead(dest))
	{
		return DLLSpliceDestHead(dest, from, to);
	}
	
	dest_original_prev = DLLPrev(dest);
	to_original_prev = DLLPrev(to);

	if(IsHead(from))
	{
		((dll_list_t *)(from->prev->data))->head = to;
	}
	else
	{	
		from->prev->next = to;
	}	
	
	to->prev = from->prev;	
	
	dest_original_prev->next = from;
	from->prev = dest_original_prev;
	to_original_prev->next = dest;
	dest->prev = to_original_prev;


	return to_original_prev; 	
}

static dll_iterator_t DLLSpliceDestHead(dll_iterator_t dest, dll_iterator_t from,
						 dll_iterator_t to)
{
	dll_iterator_t to_original_prev = InitIter();
	
	assert(InitIter() != dest);
	assert(InitIter() != from);
	assert(InitIter() != to);

	to_original_prev = DLLPrev(to);
	
	if(IsHead(from))
	{
		((dll_list_t *)(from->prev->data))->head = to;
	}
	else
	{	
		from->prev->next = to;
	}	
	
	to->prev = from->prev;
	to_original_prev->next = dest;
	((dll_list_t *)(dest->prev->data))->head = from;
	
	return to_original_prev;
}












