/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 25/05/2022
File: Data Structures - Heap
Description: Implementing heap data structure
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/* printf */

#include "heap.h"

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

enum Status
{
    SUCCESS = 0,
    FALSE = 0,
    TRUE = 1,
    FAIL
};

int CmpFunction(const void *new_data, const void *current_data, void *cmp_param);
int MatchFunction(const void *data, const void *heap_data, void *param);
int IntComper(int x, int y);
void TestBasicHeap();

int main()
{
    printf("~~~ TestBasicHeap ~~~\n");
    TestBasicHeap();

    return SUCCESS;
}

void TestBasicHeap()
{
    int a = 0, b = 10, c = 20, d = 30, e = 40, f = -10, g = -40;
    
    heap_t *heap = NULL;
    heap = HeapCreate(&CmpFunction, NULL);

    printf("HeapIsEmpty after creat:\n");
    RUNTEST(IntComper(HeapIsEmpty(heap), TRUE));
    printf("HeapSize after creat:\n");
    RUNTEST(IntComper(HeapSize(heap), 0));

    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);
    HeapPush(heap, &e);
    HeapPush(heap, &a);
    HeapPush(heap, &f);
    HeapPush(heap, &g);
    
    printf("HeapIsEmpty after push:\n");
    RUNTEST(IntComper(HeapIsEmpty(heap), FALSE));
    printf("HeapSize after push:\n");
    RUNTEST(IntComper(HeapSize(heap), 7));

    printf("peek after insert: %d\n", g);
    RUNTEST(IntComper(*(int *)HeapPeek(heap), g));

    printf("after insert shoud be: %d %d %d %d %d %d %d\n", g, b, f, e, c, d, a);
    PrintTree(heap);

    printf("remove: %d\n", f);
    RUNTEST(IntComper(*(int *)HeapRemove(heap, &f, &MatchFunction, NULL), f));
    printf("remove not found:\n");
    RUNTEST(IntComper(NULL == HeapRemove(heap, &f, &MatchFunction, NULL), TRUE));
    printf("after remove shoud be: %d %d %d %d %d %d\n", g, a, b, c, d, e);
    PrintTree(heap);

    printf("pop: %d\n", g);
    RUNTEST(IntComper(*(int *)HeapPop(heap), g));
    printf("peek after pop: %d\n", a);
    RUNTEST(IntComper(*(int *)HeapPeek(heap), a));
    printf("pop: %d \n", a);
    RUNTEST(IntComper(*(int *)HeapPop(heap), a));
    printf("pop: %d\n", b);
    RUNTEST(IntComper(*(int *)HeapPop(heap), b));
    printf("pop: %d\n", c);
    RUNTEST(IntComper(*(int *)HeapPop(heap), c));
    printf("pop: %d\n", d);
    RUNTEST(IntComper(*(int *)HeapPop(heap), d));
    printf("pop: %d\n", e);
    RUNTEST(IntComper(*(int *)HeapPop(heap), e));

    printf("HeapIsEmpty after pop all:\n");
    RUNTEST(IntComper(HeapIsEmpty(heap), TRUE));
    printf("HeapSize after pop all:\n");
    RUNTEST(IntComper(HeapSize(heap), 0));

    HeapDestroy(heap);
}

int CmpFunction(const void *new_data, const void *current_data, void *cmp_param)
{
    (void)cmp_param;

    return  *(int *)current_data - *(int *)new_data;
}

int MatchFunction(const void *data, const void *heap_data, void *param)
{
    (void)param;
    return *(int *)data == *(int *)heap_data;
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}