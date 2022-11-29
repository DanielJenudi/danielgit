/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: adiya 
Date: 24/03/2022
File: Data struct - Sorted List
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/

#include "sl.h" /* sl.h */


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

enum
{
	SUCCESS = 0,
	FAIL = 1,
	TRUE = 1,
	FALSE = 0
};


int CmpFunc(const void *new_data, const void *list_data, void *param);
int IntComper(int x, int y);
void PrintSL(sl_t *src, char *name);
int match_func(const void *data, void *parameter);
int action_func(void *data, void *parameter);

void SimpleTest();
void SLMergeTest();
void SLForEachTest();
void SLFindIfTest();

int main()
{
	printf("\n~~~ SimpleTest ~~~\n");
	SimpleTest();
	printf("\n~~~ SLMergeTest ~~~\n");
	SLMergeTest();
	printf("\n~~~ SLForEachTest ~~~\n");
	SLForEachTest();
	printf("\n~~~ SLFindIfTest ~~~\n");
	SLFindIfTest();
	
	return 0;
}

int CmpFunc(const void *new_data, const void *list_data, void *param)
{
	int new_data_int = *(int *)new_data;
	int list_data_int = *(int *)list_data;
	int param_int = *(int *)param;
	
	return (list_data_int % param_int) - (new_data_int % param_int);
}

void SimpleTest()
{
	int param = 10, a = 1005, b = 9000, c = 7201, d = 1000, e = 3123, f = 2222;

	sl_t *sl_list = SLCreate(CmpFunc, &param);
	sl_iterator_t iter = NULL;
	
	SLInsert(sl_list, &a);
	SLInsert(sl_list, &b);
	SLInsert(sl_list, &c);
	SLInsert(sl_list, &d);
	SLInsert(sl_list, &e);
	SLInsert(sl_list, &f);
	
	PrintSL(sl_list, "simple");
	
	printf("\nremove:\n");
	iter = SLBegin(sl_list);
	RUNTEST(IntComper(*(int *)SLGetData(iter), b));
	iter = SLRemove(iter);
	RUNTEST(IntComper(*(int *)SLGetData(iter), d));
	SLInsert(sl_list, &b);
	
	printf("\ncount + is empty:\n");
	RUNTEST(IntComper(SLCount(sl_list), 6));
	RUNTEST(IntComper(SLIsEmpty(sl_list), 0));
	
	
	printf("Find:\n");
	RUNTEST(IntComper(*(int *)SLGetData(
				   SLFind(sl_list, SLBegin(sl_list), SLEnd(sl_list), &c)), c ));
	
	printf("\npop front order:\n");
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), d));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), b));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), c));
	
	RUNTEST(IntComper(SLCount(sl_list), 3));
	RUNTEST(IntComper(SLIsEmpty(sl_list), 0));
	
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), f));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), e));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), a));
	
	printf("\ncount + is empty:\n");
	RUNTEST(IntComper(SLCount(sl_list), 0));
	RUNTEST(IntComper(SLIsEmpty(sl_list), 1));
	
	SLInsert(sl_list, &a);
	SLInsert(sl_list, &b);
	SLInsert(sl_list, &c);
	SLInsert(sl_list, &d);
	SLInsert(sl_list, &e);
	SLInsert(sl_list, &f);
	
	printf("\npop back order:\n");
	RUNTEST(IntComper(*(int *)SLPopBack(sl_list), a));
	RUNTEST(IntComper(*(int *)SLPopBack(sl_list), e));
	RUNTEST(IntComper(*(int *)SLPopBack(sl_list), f));
	RUNTEST(IntComper(*(int *)SLPopBack(sl_list), c));
	RUNTEST(IntComper(*(int *)SLPopBack(sl_list), d));
	RUNTEST(IntComper(*(int *)SLPopBack(sl_list), b));
	
	SLDestroy(sl_list);
}

void SLMergeTest()
{
	int param = 10, a = 1005, b = 9000, c = 7201, d = 1000, e = 3123, f = 2222,
					a2 = 3000, b2 = 9001, c2 =5432, d2 = 9999;

	sl_t *dest = SLCreate(CmpFunc, &param);
	sl_t *src = SLCreate(CmpFunc, &param);
	
	SLInsert(dest, &a);
	SLInsert(dest, &b);
	SLInsert(dest, &c);
	SLInsert(dest, &d);
	SLInsert(dest, &e);
	SLInsert(dest, &f);
	PrintSL(dest, "dest");
	
	SLInsert(src, &a2);
	SLInsert(src, &b2);
	SLInsert(src, &c2);
	SLInsert(src, &d2);
	PrintSL(src, "src");
	
	SLMerge(dest, src);
	PrintSL(dest, "dest");
	
	printf("\ncount: \n");
	RUNTEST(IntComper(SLCount(dest), 10));
	RUNTEST(IntComper(SLCount(src), 0));
	
	SLDestroy(dest);
	SLDestroy(src);
}

void SLForEachTest()
{
	int param = 10, a = 1005, b = 9000, c = 7201, d = 1000, e = 3123, f = 2222;

	sl_t *sl_list = SLCreate(CmpFunc, &param);
	
	SLInsert(sl_list, &a);
	SLInsert(sl_list, &b);
	SLInsert(sl_list, &c);
	SLInsert(sl_list, &d);
	SLInsert(sl_list, &e);
	SLInsert(sl_list, &f);
	
	SLForEach(action_func, &param, SLBegin(sl_list), SLEnd(sl_list));
	
	printf("\ncount: \n");
	RUNTEST(IntComper(SLCount(sl_list), 6));
	
	printf("\npop check: \n");
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), 9010));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), 1010));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), 7211));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), 2232));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), 3133));
	RUNTEST(IntComper(*(int *)SLPopFront(sl_list), 1015));
	
	printf("\ncount: \n");
	RUNTEST(IntComper(SLCount(sl_list), 0));
	
	SLDestroy(sl_list);
}

void SLFindIfTest()
{
	int param = 10, a = 1005, b = 1001, c = 7201, d = 1000, e = 3123, f = 2222;
	int param_act = 2000;

	sl_t *sl_list = SLCreate(CmpFunc, &param);
	sl_iterator_t iter = NULL;
	
	SLInsert(sl_list, &a);
	SLInsert(sl_list, &b);
	SLInsert(sl_list, &c);
	SLInsert(sl_list, &d);
	SLInsert(sl_list, &e);
	SLInsert(sl_list, &f);

	iter = SLFindIf(match_func, &param_act, SLBegin(sl_list), SLEnd(sl_list));
	
	printf("\nSLFindIf: \n");
	RUNTEST(IntComper(*(int *)SLGetData(iter), c));

	
	SLDestroy(sl_list);
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}

void PrintSL(sl_t *src, char *name)
{
	sl_iterator_t runner = NULL;
	
	
	runner = SLBegin(src); 
	printf("\nprint list %s\n", name);
	
	while(runner != SLEnd(src))
	{
		printf("%d\n",*(int *)SLGetData(runner));
		runner = SLNext(runner);
	}
}

int match_func(const void *data, void *parameter)
{
	return *(const int *)data > *(int *)parameter ? TRUE : FALSE;
}

int action_func(void *data, void *parameter)
{
	return *(int *)data += *(int *)parameter;
}


