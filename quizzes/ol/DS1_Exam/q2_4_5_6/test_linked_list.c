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

#define RUNTEST(test) {\
            if (!test)\
            {\
                printf("\x1b[0;34m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;35m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }
 
int IntComper(int x, int y);
int IsNull(void *ptr);
void TestQ2();
void TestQ4();
void TestQ5();

enum
{
	SUCCESS,
	FAIL
};

int main()
{
	TestQ2();
	TestQ4();
	TestQ5();
	
	return 0;
}

void TestQ2()
{
	size_t a = 1;
	size_t b = 2;
	size_t c = 3;
	size_t d = 4;
	size_t e = 5;
	size_t checker = 0;
	
	s_linked_list_t *list = SLinkedListCreate();
	iterator_t iter = SLinkedListBegin(list);
	iterator_t end = NULL;
	
	
	printf("--- TestQ2 ---\n");
	
	iter = SLinkedListInsertBefore(iter, &a);
	iter = SLinkedListInsertBefore(iter, &b);
	iter = SLinkedListInsertBefore(iter, &c);
	iter = SLinkedListInsertBefore(iter, &d);
	iter = SLinkedListInsertBefore(iter, &e);
	
	iter = SLinkedListBegin(list);
	end = SLinkedListEnd(list);
	checker = 5;
	
	printf("befor flip:\n");
	while(!SLinkedListIsIterEqual(iter, end))
	{
		RUNTEST(IntComper(*(size_t *)SLinkedListGetData(iter) ,checker));
		--checker;
		iter = SlinkedListNext(iter);
	}
	
	Flip(list);
	
	iter = SLinkedListBegin(list);
	end = SLinkedListEnd(list);
	checker = 1;
	
	printf("after flip:\n");
	while(!SLinkedListIsIterEqual(iter, end))
	{
		RUNTEST(IntComper(*(size_t *)SLinkedListGetData(iter) ,checker));
		++checker;
		iter = SlinkedListNext(iter);
	}
	
	SLinkedListDestroy(list);
	list = NULL;
	iter = NULL;
}

void TestQ4()
{
	size_t a = 1;
	size_t b = 2;
	size_t c = 3;
	size_t d = 4;
	size_t e = 5;
	
	s_linked_list_t *list = SLinkedListCreate();
	iterator_t iter = SLinkedListBegin(list);
	iterator_t end = NULL;
	
	
	printf("\n--- TestQ4 ---\n");
	
	iter = SLinkedListInsertBefore(iter, &a);
	iter = SLinkedListInsertBefore(iter, &b);
	iter = SLinkedListInsertBefore(iter, &c);
	iter = SLinkedListInsertBefore(iter, &d);
	iter = SLinkedListInsertBefore(iter, &e);
	
	iter = SLinkedListBegin(list);
	iter = SlinkedListNext(iter);
	iter = SlinkedListNext(iter);
	end = SLinkedListEnd(list);
	
	ConnectTwoNodes(end, iter);
	printf("has loop:\n");
	RUNTEST(IntComper(HasLoop(list) ,1));
	OpenLoop(list);
	printf("open loop:\n");
	RUNTEST(IntComper(HasLoop(list) ,0));
	
	SLinkedListDestroy(list);
	list = NULL;
	iter = NULL;
}

void TestQ5()
{
	size_t a = 1;
	size_t b = 2;
	size_t c = 3;
	size_t d = 4;
	size_t e = 5;
	
	size_t A = 10;
	size_t B = 20;
	size_t C = 30;
	size_t D = 40;
	size_t E = 50;
	
	s_linked_list_t *list1 = SLinkedListCreate();
	s_linked_list_t *list2 = SLinkedListCreate();
	
	iterator_t iter1 = SLinkedListBegin(list1);
	iterator_t iter2 = SLinkedListBegin(list2);
	
	iterator_t end2 = NULL;
	
	
	printf("\n--- TestQ5 ---\n");
	
	iter1 = SLinkedListInsertBefore(iter1, &a);
	iter1 = SLinkedListInsertBefore(iter1, &b);
	iter1 = SLinkedListInsertBefore(iter1, &c);
	iter1 = SLinkedListInsertBefore(iter1, &d);
	iter1 = SLinkedListInsertBefore(iter1, &e);
	
	iter2 = SLinkedListInsertBefore(iter2, &A);
	iter2 = SLinkedListInsertBefore(iter2, &B);
	iter2 = SLinkedListInsertBefore(iter2, &C);
	iter2 = SLinkedListInsertBefore(iter2, &D);
	iter2 = SLinkedListInsertBefore(iter2, &E);
	
	iter1 = SLinkedListBegin(list1);
	iter1 = SlinkedListNext(iter1);
	iter1 = SlinkedListNext(iter1);
	end2 = SLinkedListEnd(list2);
	
	ConnectTwoNodes(end2, iter1);
	printf("has intersect:\n");
	RUNTEST(IntComper(HasIntersect(list1, list2) ,1));
	SeparatLists(list1, list2);
	printf("open intersect:\n");
	RUNTEST(IntComper(HasIntersect(list1, list2) ,0));
	
	
	SLinkedListDestroy(list1);
	list1 = NULL;
	SLinkedListDestroy(list2);
	list2 = NULL;
} 

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}

int IsNull(void *ptr)
{
	return !(NULL == ptr);
}


