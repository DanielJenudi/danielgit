#include <stdio.h> /* printf */

#include "dll.h"

static void RunTest(int test);
int match_func(const void *data, void *parameter);
int action_func(void *data, void* parameter);
void SimpelTest();
void DLLSpliceTest1();
void DLLSpliceTest2();
void DLLFindMatchTest();
void DLLForEachTest();
void DLLMultiFindTest();


enum
{
	ALLFAIL = -1,
	FALSE = 0,
	SUCCESS = 0,
	FAIL = 1,
	TRUE = 1
};

int main()
{
	printf("\n--- SimpelTest ---\n");
	SimpelTest();
	printf("\n--- DLLSpliceTest1 ---\n");
	DLLSpliceTest1();
	printf("\n--- DLLSpliceTest2 ---\n");
	DLLSpliceTest2();
	printf("\n--- DLLFindMatchTest ---\n");
	DLLFindMatchTest();
	printf("\n--- DLLForEachTest ---\n");
	DLLForEachTest();
	printf("\n--- DLLMultiFindTest(); ---\n");
	DLLMultiFindTest();
	
	return SUCCESS;
}

void DLLMultiFindTest()
{
	int a = 100, b = 200, c = 300, d = 400, pram = 250;

	dll_list_t *list = DLLCreate();
	dll_list_t *result = DLLCreate();
	dll_iterator_t iter = DLLEnd(list);

	DLLInsertBefore(iter, &a); 
	DLLInsertBefore(iter, &b);
	DLLInsertBefore(iter, &c);
	DLLInsertBefore(iter, &d);
	
	RunTest(DLLCount(list) == 4);
	
	DLLMultiFind(match_func, &pram, DLLBegin(list) ,DLLEnd(list), result);
	
	RunTest(DLLCount(result) == 2);
	
	iter = DLLBegin(result);
	
	RunTest(c == *(int *)DLLGetData(iter));
	iter = DLLNext(iter);
	RunTest(d == *(int *)DLLGetData(iter));
	iter = DLLNext(iter);
	
	DLLDestroy(list);
	DLLDestroy(result);
}

void DLLFindMatchTest()
{
	int a = 100, b = 200, c = 300, d = 400, pram = 250;

	dll_list_t *list = DLLCreate();
	dll_iterator_t iter = DLLEnd(list);

	DLLInsertBefore(iter, &a); 
	DLLInsertBefore(iter, &b);
	DLLInsertBefore(iter, &c);
	DLLInsertBefore(iter, &d);
	
	RunTest(DLLCount(list) == 4);
	
	iter = DLLFindMatch(match_func, &pram, DLLBegin(list) ,DLLEnd(list));
	
	RunTest(c == *(int *)DLLGetData(iter));
	
	DLLDestroy(list);
}


void DLLForEachTest()
{
	int a = 100, b = 200, c = 300, d = 400, pram = 250;

	dll_list_t *list = DLLCreate();
	dll_iterator_t iter = DLLEnd(list);

	DLLInsertBefore(iter, &a); 
	DLLInsertBefore(iter, &b);
	DLLInsertBefore(iter, &c);
	DLLInsertBefore(iter, &d);
	
	RunTest(DLLCount(list) == 4);
	
	RunTest(2 == DLLForEach(action_func, &pram, DLLBegin(list) ,DLLEnd(list)));
	
	iter = DLLBegin(list);
	
	RunTest(pram == *(int *)DLLGetData(iter));
	iter = DLLNext(iter);
	RunTest(pram == *(int *)DLLGetData(iter));
	iter = DLLNext(iter);
	RunTest(c == *(int *)DLLGetData(iter));
	iter = DLLNext(iter);
	RunTest(d == *(int *)DLLGetData(iter));
	
	
	DLLDestroy(list);
}

void DLLSpliceTest1()
{
	int a = 100, b = 200, c = 300, d = 400;

	dll_list_t *list_src = DLLCreate();
	dll_list_t *list_dest = DLLCreate();
	
	dll_iterator_t iter_src = DLLEnd(list_src);
	dll_iterator_t iter_dest = DLLEnd(list_dest);

	DLLInsertBefore(iter_src, &a); 
	DLLInsertBefore(iter_src, &b);
	DLLInsertBefore(iter_src, &c);
	DLLInsertBefore(iter_src, &d);
	
	RunTest(4 == DLLCount(list_src));
	
	DLLSplice(iter_dest, DLLBegin(list_src), DLLEnd(list_src));
	
	RunTest(0 == DLLCount(list_src));
	RunTest(4 == DLLCount(list_dest));
	
	DLLDestroy(list_src);
	DLLDestroy(list_dest);
}

void DLLSpliceTest2()
{
	int a = 100, b = 200, c = 300, d = 400, e = 500;

	dll_list_t *list_src = DLLCreate();
	dll_list_t *list_dest = DLLCreate();
	
	dll_iterator_t iter_src = DLLEnd(list_src);
	dll_iterator_t iter_dest = DLLEnd(list_dest);
	
	iter_dest = DLLInsertBefore(iter_dest, &e);
	
	DLLInsertBefore(iter_src, &a); 
	DLLInsertBefore(iter_src, &b);
	DLLInsertBefore(iter_src, &c);
	DLLInsertBefore(iter_src, &d);
	
	RunTest(4 == DLLCount(list_src));
	
	iter_dest = DLLEnd(list_dest);
	DLLSplice(iter_dest, DLLBegin(list_src), DLLPrev(DLLEnd(list_src)));
	
	RunTest(4 == DLLCount(list_dest));
	RunTest(1 == DLLCount(list_src));
	
	iter_dest = DLLBegin(list_dest);
	
	RunTest(e == *(int *)DLLGetData(iter_dest));
	iter_dest = DLLNext(iter_dest);
	RunTest(a == *(int *)DLLGetData(iter_dest));
	iter_dest = DLLNext(iter_dest);
	RunTest(b == *(int *)DLLGetData(iter_dest));
	
	iter_src = DLLBegin(list_src);
	RunTest(d == *(int *)DLLGetData(iter_src));

	DLLDestroy(list_src);
	DLLDestroy(list_dest);
}

void SimpelTest()
{
	int a = 23, b = 10, c = 1997;
	int d = 11;
	
	dll_list_t *dll_list = DLLCreate();
	dll_iterator_t iterator = DLLEnd(dll_list);
	
	printf("List should be empty: ");
	RunTest(TRUE == DLLIsEmpty(dll_list));
	
	DLLInsertBefore(iterator, &a);
	DLLInsertBefore(iterator, &b);
	DLLInsertBefore(iterator, &c);
	
	/* 23 10 1997 */
	
	printf("List should not be empty: ");
	RunTest(FALSE == DLLIsEmpty(dll_list));
	
	printf("List size should be 3: ");
	RunTest(3 == DLLCount(dll_list));
	
	printf("List begin should be equal to a: ");
	RunTest(a == *(int *)DLLGetData(DLLBegin(dll_list)));
	
	printf("List end should be equal to c: ");
	RunTest(c == *(int *)DLLGetData(DLLPrev(DLLEnd(dll_list))));
	
	DLLSetData(DLLBegin(dll_list), &d);
	
	printf("List begin should be equal to d: ");
	RunTest(d == *(int *)DLLGetData(DLLBegin(dll_list)));
	
	DLLPushFront(dll_list, &a);
	
	printf("List size should be 4: ");
	RunTest(4 == DLLCount(dll_list));
	
	printf("List begin should be equal to a: ");
	RunTest(a == *(int *)DLLGetData(DLLBegin(dll_list)));
	
	DLLPushBack(dll_list, &d);
	
	printf("List size should be 5: ");
	RunTest(5 == DLLCount(dll_list));
	
	printf("List end should be equal to d: ");
	RunTest(d == *(int *)DLLGetData(DLLPrev(DLLEnd(dll_list))));
	
	DLLRemove(DLLBegin(dll_list));
	
	printf("List size should be 4: ");
	RunTest(4 == DLLCount(dll_list));
	
	printf("List pop front should be equal to d: ");
	RunTest(d == *(int *)DLLPopFront(dll_list));
	
	printf("List pop back should be equal to d: ");
	RunTest(d == *(int *)DLLPopBack(dll_list));
	
	printf("List size should be 2: ");
	RunTest(2 == DLLCount(dll_list));
	
	DLLDestroy(dll_list);
}

int match_func(const void *data, void *parameter)
{
	return *(const int *)data > *(int *)parameter ? TRUE : FALSE;
}

int action_func(void *data, void* parameter)
{
	if(*(int *)data < *(int *)parameter)
	{
		*(int *)data = *(int *)parameter;
		return SUCCESS;
	}
	
	return FAIL;
}

static void RunTest(int test)
{
	if (1 == test)
	{
		printf("\x1b[0;34m");
		printf("OK!\n\n");
		printf("\x1b[0m");
	}
	else
	{
		printf("\x1b[1;35m");
		printf("\nTest Failed!\n\n");
		printf("\x1b[0m");
	}
}




