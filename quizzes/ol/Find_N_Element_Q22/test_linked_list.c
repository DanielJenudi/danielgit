/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 10/03/2022
File: Data struct - Singly linked list
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/
#include "link_list.h"

void *FindElement(s_linked_list_t *sll, size_t index);

int main()
{
	int a = 10, b = 15, c = 20, d = 25;
	s_linked_list_t *sll = SLinkedListCreate();
	
	SLinkedListInsertBefore(SLinkedListBegin(sll), &a);
	SLinkedListInsertBefore(SLinkedListBegin(sll), &b);
	SLinkedListInsertBefore(SLinkedListBegin(sll), &c);
	SLinkedListInsertBefore(SLinkedListBegin(sll), &d);
	
	printf("%d\n", *(int *)FindElement(sll, 1));

	SLinkedListDestroy(sll);

	return 0;
}

void *FindElement(s_linked_list_t *sll, size_t index)
{
	iterator_t runner = SLinkedListBegin(sll);
	int count = 0;
	
	count = SLinkedListCount(sll) - index;
	
	if(0 > count)
	{
		return NULL;
	}
	
	while(0 != count)
	{
		runner = SlinkedListNext(runner);
		--count;
	}

	return SLinkedListGetData(runner);
}

