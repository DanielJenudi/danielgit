/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Rani 
Date: 27/03/2022
File: Data struct - Priorety queue
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/

#include "pq_sl.h"/* pq.h */

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
int match_func(const void *data, void *parameter);
int IntComper(int x, int y);


int main()
{
	int param = 10, a = 1005, b = 3000, c = 7201, d = 1000, e = 3123, f = 2222;
	pq_t *pq = PQCreate(CmpFunc, &param);
	
	printf("~~~ TEST ~~~\n");
	
	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);
	PQEnqueue(pq, &c);
	PQEnqueue(pq, &d);
	PQEnqueue(pq, &e);
	PQEnqueue(pq, &f);
	
	printf("count: ");
	RUNTEST(IntComper(PQSize(pq), 6));
	printf("isempty: ");
	RUNTEST(IntComper(PQIsEmpty(pq), 0));
	
	printf("Peek & Dequeue: \n");
	RUNTEST(IntComper(*(int *)PQPeek(pq), b));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), d));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), c));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), f));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), e));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), a));
	PQDequeue(pq);
	
	printf("count: ");
	RUNTEST(IntComper(PQSize(pq), 0));
	printf("isempty: ");
	RUNTEST(IntComper(PQIsEmpty(pq), 1));
	
	printf("~~~ Clear ~~~\n");
	
	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);
	PQEnqueue(pq, &c);
	PQEnqueue(pq, &d);
	PQEnqueue(pq, &e);
	PQEnqueue(pq, &f);
	
	printf("befor clear - count: ");
	RUNTEST(IntComper(PQSize(pq), 6));
	printf("befor clear - isempty: ");
	RUNTEST(IntComper(PQIsEmpty(pq), 0));
	
	PQClear(pq);
	
	printf("after clear - count: ");
	RUNTEST(IntComper(PQSize(pq), 0));
	printf("after clear - isempty: ");
	RUNTEST(IntComper(PQIsEmpty(pq), 1));
	
	printf("~~~ Erase ~~~\n");
	
	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);
	PQEnqueue(pq, &c);
	PQEnqueue(pq, &d);
	PQEnqueue(pq, &e);
	PQEnqueue(pq, &f);
	
	printf("erase: ");
	RUNTEST(IntComper(*(int *)PQErase(pq, &e, match_func), c));
	
	printf("Erase - Peek & Dequeue: \n");
	RUNTEST(IntComper(*(int *)PQPeek(pq), b));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), d));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), f));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), e));
	PQDequeue(pq);
	RUNTEST(IntComper(*(int *)PQPeek(pq), a));
	PQDequeue(pq);
	
	
	PQDestroy(pq);
	
	return 0;
}

int CmpFunc(const void *new_data, const void *list_data, void *param)
{
	int new_data_int = *(int *)new_data;
	int list_data_int = *(int *)list_data;
	int param_int = *(int *)param;
	
	return (list_data_int % param_int) - (new_data_int % param_int);
}

int match_func(const void *data, void *parameter)
{
	return *(const int *)data > *(int *)parameter ? TRUE : FALSE;
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}
















