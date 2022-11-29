/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 10/03/2022
File: Data struct - Singly linked list
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "link_list.h"

enum
{
	SUCCESS = 0,
	FAIL
};


struct s_list_node
{
    void *data;
    s_list_node_t *next;
};

struct s_linked_list 
{
    s_list_node_t *head;
    s_list_node_t *tail;
};


static int AddOne(void *data, void *parameter);


s_linked_list_t *SLinkedListCreate(void)
{
	s_linked_list_t *list = NULL;
	s_list_node_t *dummy_node = NULL;
	
	list = (s_linked_list_t *)malloc(sizeof(s_linked_list_t));
	if(NULL == list)
	{
		return NULL;
	}
	
	dummy_node = (s_list_node_t *)malloc(sizeof(s_list_node_t));
	if(NULL == dummy_node)
	{
		free(list);
		return NULL;
	}
	
	dummy_node->data = list;
	dummy_node->next = NULL;
	list->head = dummy_node;
	list->tail = dummy_node;

	return list;
}

void SLinkedListDestroy(s_linked_list_t *list)
{
	iterator_t runner = SLinkedListBegin(list);
	iterator_t temp_next = NULL;
	
	assert(NULL != list);
	
	while(NULL != runner)
	{
		temp_next = runner->next;
		free(runner);
		runner = temp_next;
	}
	
	free(runner);
	free(list);
}

iterator_t SLinkedListBegin(const s_linked_list_t *list)
{
	assert(NULL != list);
	
	return list->head;
}

iterator_t SlinkedListNext(const iterator_t iter)
{
	assert(NULL != iter);
	
	return iter->next;
}

iterator_t SLinkedListEnd(const s_linked_list_t *list)
{
	return list->tail;
}

void *SLinkedListGetData(const iterator_t iter)
{
	assert(NULL != iter);
	
	return iter->data;	
}

void SLinkedListSetData(iterator_t iter, const void *new_data)
{
	assert(NULL != iter);
	
	iter->data = (void *)new_data;
}

int SLinkedListIsIterEqual(const iterator_t iter1, const iterator_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

iterator_t SLinkedListInsertBefore(iterator_t where, const void *data)
{
	s_list_node_t *new_node = NULL;
	
	assert(NULL != where);
	
	new_node = (s_list_node_t *)malloc(sizeof(s_list_node_t));
	if(NULL == new_node)
	{
		while(NULL != where->next)
		{
			where = where->next;
		}
		return where;
	}
	
	new_node->data = where->data;
	new_node->next = where->next;
	
	where->data = (void *)data;
	where->next = new_node;
	
	if(NULL == new_node->next)
	{
		((s_linked_list_t *)(where->next->data))->tail = new_node;
	}
	
	return where;
}

iterator_t SLinkedListRemove(iterator_t iter)
{
	iterator_t to_remove = NULL;
    
    assert(NULL != iter->next);
    
    to_remove = iter->next;
    iter->data = to_remove->data;
    iter->next = to_remove->next;
    free(to_remove);
    
    if (NULL == iter->next)
    {
        ((s_linked_list_t *)(iter->data))->tail = iter;
    }
    
    
    return iter;

}

size_t SLinkedListCount(const s_linked_list_t *list)
{
	size_t count = 0;
	
	assert(NULL != list);
	
	SLinkedListForEach(AddOne, (void *)&count, SLinkedListBegin(list), 
	                   SLinkedListEnd(list));
	
	return count;
}

static int AddOne(void *data, void *parameter)
{
	(void)data;
	*(size_t *)parameter += (size_t)1;
	
	return SUCCESS;
}

int SLinkedListIsEmpty(const s_linked_list_t *list)
{
	assert(NULL != list);
	
	return (NULL == list->head->next);
}

iterator_t SLinkedListFind(match_func_t is_match, void *param, iterator_t from,
                           iterator_t to)
{
	while(!SLinkedListIsIterEqual(from, to) && NULL != from->next)
	{
		if(SUCCESS == is_match(from->data, param))
		{
			return from;
		}
		
		from = SlinkedListNext(from);
	}
	
	return to;
}

int SLinkedListForEach(action_func_t action_func, void *param, iterator_t from,
			           iterator_t to)
{
	while(!SLinkedListIsIterEqual(from, to) && NULL != from->next)
	{
		if(FAIL == action_func(from->data, param))
		{	
			return FAIL;
		}
		
		from = SlinkedListNext(from);
	}
	
	return SUCCESS;
}

s_linked_list_t *SLinkedListAppend(s_linked_list_t *dest, s_linked_list_t *src)
{	
	dest->tail->next = src->head;
	SLinkedListRemove(dest->tail);
	src->tail->data = dest;
	dest->tail = src->tail;
	
	free(src);

	return dest;
}

void ConnectTwoNodes(iterator_t iter, iterator_t next)
{
	iter->next = next;
}

int HasLoop(s_linked_list_t *list)
{
	iterator_t jump1 = NULL;
	iterator_t jump2 = NULL;
	
	assert(NULL != list);
	
	jump1 = SLinkedListBegin(list);
	jump2 = SlinkedListNext(jump1);
	
	while(NULL != SlinkedListNext(jump2) && SlinkedListNext(jump2->next))
	{
		if(SLinkedListIsIterEqual(jump1, jump2))
		{
			return 1;
		}
		
		jump1 = SlinkedListNext(jump1);
		jump2 = SlinkedListNext(jump2->next);
	}

	return 0;
}

void OpenLoop(s_linked_list_t *list)
{
	iterator_t jump1 = NULL;
	iterator_t jump2 = NULL;
	iterator_t meet = NULL;
	
	assert(NULL != list);
	
	meet = SLinkedListBegin(list);
	jump1 = SLinkedListBegin(list);
	jump2 = SlinkedListNext(jump1);
	
	while(!SLinkedListIsIterEqual(jump1, jump2))
	{	
		jump1 = SlinkedListNext(jump1);
		jump2 = SlinkedListNext(jump2->next);
	}
	
	jump1 = SlinkedListNext(jump1);
	
	while(meet != SlinkedListNext(jump1))
	{	
		if(SLinkedListIsIterEqual(jump1, jump2))
		{
			meet = SlinkedListNext(meet);
		}
		
		jump1 = SlinkedListNext(jump1);	
	}
	
	jump1->next = NULL;
}

iterator_t RealEnd(const s_linked_list_t *list)
{
	iterator_t runner = SLinkedListBegin(list);
	
	while(NULL != SlinkedListNext(runner))
	{
		runner = SlinkedListNext(runner);
	}
	
	return runner;
}

size_t RealCount(const s_linked_list_t *list)
{
	size_t count = 0;
	iterator_t runner = SLinkedListBegin(list);
	
	while(NULL != SlinkedListNext(runner))
	{
		++count;
		runner = SlinkedListNext(runner);
	}
	
	return count;
}


int HasIntersect(s_linked_list_t *list1, s_linked_list_t *list2)
{
	return RealEnd(list1) == RealEnd(list2) ? 1 : 0;
}

iterator_t Alignd(iterator_t iter, size_t n)
{
	while(0 < n)
	{
		iter = SlinkedListNext(iter);
		--n;
	}
	
	return iter;
}

void SeparatLists(s_linked_list_t *list1, s_linked_list_t *list2)
{
	size_t list1_size = RealCount(list1);	
	size_t list2_size = RealCount(list2);
	iterator_t iter1 = SLinkedListBegin(list1);
	iterator_t iter2 = SLinkedListBegin(list2);
	
	
	if(list1_size > list2_size)
	{
		iter1 = Alignd(iter1, list1_size - list2_size);
	}
	else
	{
		iter2 = Alignd(iter2, list2_size - list1_size);
	}
	
	while(SlinkedListNext(iter1) != SlinkedListNext(iter2))
	{
		iter1 = SlinkedListNext(iter1);
		iter2 = SlinkedListNext(iter2);
	}
	
	iter1->next = NULL;
}

iterator_t Flip(s_linked_list_t *list)
{
	iterator_t iter_pre = NULL;
	iterator_t iter_current = NULL;
	iterator_t iter_next = NULL;
	
	assert(NULL != list);
	
	if(NULL == SlinkedListNext(SLinkedListBegin(list)))
	{
		return SLinkedListBegin(list);
	}
	
	iter_current = SLinkedListBegin(list);
	iter_next = SlinkedListNext(iter_current);
	iter_current->next = RealEnd(list);
	
	while(NULL != SlinkedListNext(iter_next))
	{
		iter_pre = iter_current;
		iter_current = iter_next;
		iter_next = SlinkedListNext(iter_next);
		iter_current->next = iter_pre;
	}
	
	list->head = iter_current;
	
	return iter_current;
}









































