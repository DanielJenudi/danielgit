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
        
void TestBuildList();
void TestChangeData();
void TestSLinkedListAppend();
void TestSLinkedListFind();
void TestSLinkedListForEach();
int action_func(void *data, void* parameter);
int match_func(const void *data, void* parameter);
int IntComper(int x, int y);
int IsNull(void *ptr);

enum
{
	SUCCESS,
	FAIL
};

int main()
{
	TestBuildList();
	TestChangeData();
	TestSLinkedListAppend();
	TestSLinkedListFind();
	TestSLinkedListForEach();
	
	
	return 0;
}

void TestBuildList()/*begin, next, end, insert befor, get data, count*/
{
	size_t a = 5;
	size_t b = 6;
	size_t c = 18;
	
	s_linked_list_t *list = SLinkedListCreate();
	iterator_t itur = SLinkedListBegin(list);
	
	printf("--- TestBuildList ---\n");
	
	RUNTEST(IntComper(SLinkedListCount(list) ,0));
	
	itur = SLinkedListInsertBefore(itur, &a);
	itur = SLinkedListInsertBefore(itur, &b);
	itur = SLinkedListInsertBefore(itur, &c);
	
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(itur) ,c));
	itur = SlinkedListNext(itur);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(itur) ,b));
	itur = SlinkedListNext(itur);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(itur) ,a));
	
	RUNTEST(IntComper(SLinkedListCount(list) ,3));
	
	itur = SLinkedListBegin(list);
	itur = SLinkedListEnd(list);
	RUNTEST(IsNull(SlinkedListNext(itur)));
	
	SLinkedListDestroy(list);
	list = NULL;
	itur = NULL;
} 

void TestChangeData()/*equel, set data, remove, is empty*/
{
	size_t a = 5;
	size_t b = 6;
	size_t c = 18;
	
	s_linked_list_t *list = SLinkedListCreate();
	iterator_t itur = SLinkedListBegin(list);
	iterator_t itur_for_equal = SLinkedListBegin(list);
	
	printf("--- TestChangeData ---\n");
	
	RUNTEST(IntComper(SLinkedListIsIterEqual(itur, itur_for_equal), 1));
	RUNTEST(IntComper(SLinkedListIsEmpty(list), 1));
	
	itur = SLinkedListInsertBefore(itur, &a);
	itur = SLinkedListInsertBefore(itur, &b);
	itur = SLinkedListInsertBefore(itur, &c);
	
	RUNTEST(IntComper(SLinkedListIsEmpty(list), 0));
	
	SLinkedListSetData(itur, &a);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(itur) ,a));
	itur = SlinkedListNext(itur);
	SLinkedListSetData(itur, &b);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(itur) ,b));
	itur = SlinkedListNext(itur);
	SLinkedListSetData(itur, &c);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(itur) ,c));
	
	itur = SLinkedListRemove(itur);
	RUNTEST(IsNull(SlinkedListNext(itur)));
	
	SLinkedListDestroy(list);
	list = NULL;
	itur = NULL;
	itur_for_equal = NULL;
} 

void TestSLinkedListAppend()/*SLinkedListAppend*/
{
	size_t a = 5;
	size_t b = 6;
	size_t c = 18;
	size_t d = 100;
	size_t e = 10;
	
	
	s_linked_list_t *list1 = SLinkedListCreate();
	s_linked_list_t *list2 = SLinkedListCreate();
	iterator_t iter1 = SLinkedListBegin(list1);
	iterator_t iter2 = SLinkedListBegin(list1);
	
	printf("--- TestSLinkedListAppend ---\n");
	
	iter1 = SLinkedListInsertBefore(iter1, &e);
	iter1 = SLinkedListInsertBefore(iter1, &d);
	iter1 = SLinkedListInsertBefore(iter1, &c);
	iter2 = SLinkedListInsertBefore(iter2, &b);
	iter2 = SLinkedListInsertBefore(iter2, &a);
	
	SLinkedListAppend(list1, list2);
	
	
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(iter1) ,a));
	iter1 = SlinkedListNext(iter1);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(iter1) ,b));
	iter1 = SlinkedListNext(iter1);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(iter1) ,c));
	iter1 = SlinkedListNext(iter1);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(iter1) ,d));
	iter1 = SlinkedListNext(iter1);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(iter1) ,e));
	
	
	SLinkedListDestroy(list1);
	
	
	list1 = NULL;
	list2 = NULL;
	iter1 = NULL;
	iter2 = NULL;
}

void TestSLinkedListFind()/*SLinkedListFind*/
{
	size_t a = 5;
	size_t b = 6;
	size_t c = 18;
	size_t d = 100;
	size_t e = 10;
	size_t param = 80;
	
	int i = 0;
	
	s_linked_list_t *list = SLinkedListCreate();
	iterator_t from = SLinkedListBegin(list);
	iterator_t to = SLinkedListBegin(list);
	
	printf("--- TestSLinkedListFind ---\n");
	
	from = SLinkedListInsertBefore(from, &e);
	from = SLinkedListInsertBefore(from, &d);
	from = SLinkedListInsertBefore(from, &c);
	from = SLinkedListInsertBefore(from, &b);
	from = SLinkedListInsertBefore(from, &a);
	
	for(i = 0; i < 4; ++i)
	{
		to = SlinkedListNext(to);
	}
	
	from = SLinkedListFind(match_func, &param, from, to);
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(from) ,d));
	
	SLinkedListDestroy(list);
	list = NULL;
	from = NULL;
	to = NULL;
}

void TestSLinkedListForEach()/*SLinkedListForEach*/
{
	size_t a = 5;
	size_t b = 6;
	size_t c = 18;
	size_t d = 30;
	size_t e = 55;
	size_t param = 80;
	
	int i = 0;
	
	s_linked_list_t *list = SLinkedListCreate();
	iterator_t from = SLinkedListBegin(list);
	iterator_t to = SLinkedListBegin(list);
	
	printf("--- TestSLinkedListFind ---\n");
	
	from = SLinkedListInsertBefore(from, &e);
	from = SLinkedListInsertBefore(from, &d);
	from = SLinkedListInsertBefore(from, &c);
	from = SLinkedListInsertBefore(from, &b);
	from = SLinkedListInsertBefore(from, &a);
	
	for(i = 0; i < 4; ++i)
	{
		to = SlinkedListNext(to);
	}
	
	RUNTEST(IntComper(SLinkedListForEach(action_func, &param, from, to), 
	SUCCESS));
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(from) ,15));
	RUNTEST(IntComper(*(size_t *)SLinkedListGetData(to) ,55));
	
	SLinkedListDestroy(list);
	list = NULL;
	from = NULL;
	to = NULL;
}

int match_func(const void *data, void *parameter)
{
	return *(const size_t *)data > *(size_t *)parameter ? SUCCESS : FAIL;
}

int action_func(void *data, void* parameter)
{
	if(*(size_t *)data < *(size_t *)parameter)
	{
		*(size_t *)data += 10;
		return SUCCESS;
	}
	
	return FAIL;
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


