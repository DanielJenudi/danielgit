/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 25/05/2022
File: Data Structures - Priority Queue heap
Description: Implementing Priority Queue data structure with heap
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h> /*printf*/
#include <string.h> /*strlen*/

#include "pq_heap.h"

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

enum status
{
	BOOL_FALSE = 0,
	BOOL_TRUE = 1,
	PASS = 0,
	FAILURE = 1,
	ERROR = -1
};

int ValCheck(size_t recieved_val, size_t expected_val, int line);
int ValCheckPtr(void *recieved_val, void *expected_val, int line);
int ValCheckAddress(void *recieved_val, void *expected_val, int line);
int CmpStrings(void *recieved_val, void *expected_val, int line);
int CreateDestroyTest();
int PriorityToBigger(const void *new_data, const void *queue_data, void *param);
int PriorityToLongerStringLen(const void *new_data, const void *queue_data, void *param);
int EnqueueTest();
int DequeuePeekTest();
int SizeIsEmptyTest();
int ClearTest();
int FindInt(const void *current_data, void *param);
int FindEqualStrLen(const void *current_data, void *param);
int EraseTest();

int total_fails = 0;

int main()
{
	RUNTEST(CreateDestroyTest());
	RUNTEST(EnqueueTest());
	RUNTEST(DequeuePeekTest());
	RUNTEST(SizeIsEmptyTest());
	RUNTEST(ClearTest());
	RUNTEST(EraseTest());
	
	if (0 < total_fails)
	{
		printf("\n\n****** TOTAL FAILS = %d ******\n\n", total_fails);
	}


	return 0;
}

int ValCheck(size_t recieved_val, size_t expected_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("----------------FAIL line %d----------------\n", line);
		printf("got %lu, when wanted %lu\n",recieved_val, expected_val);
		++total_fails;
		return 1;
	}
	return 0;
}

int ValCheckPtr(void *recieved_val, void *expected_val, int line)
{
	if (*(int *)recieved_val != *(int *)expected_val)
	{
		printf("----------------FAIL line %d----------------\n", line);
		printf("got %d, when wanted %d\n",*(int *)recieved_val, *(int *)expected_val);
		++total_fails;
		return 1;
	}
	return 0;
}

int ValCheckAddress(void *recieved_val, void *expected_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("----------------FAIL line %d----------------\n", line);
		printf("got %p, when wanted %p\n", recieved_val, expected_val);
		++total_fails;
		return 1;
	}
	return 0;
}

int CmpStrings(void *recieved_val, void *expected_val, int line)
{
	if (0 != strcmp((char *)recieved_val, (char *)expected_val))
	{
		printf("----------------FAIL line %d----------------\n", line);
		printf("got %s, when wanted %s\n",(char *)recieved_val, (char *)expected_val);
		++total_fails;
		return 1;
	}
	return 0;
}

int CreateDestroyTest()
{
	int status = 0;
	int a = 1;
	pq_t *queue1 = NULL;
	pq_t *queue2 = NULL;
	pq_cmp_func_t priority_func = PriorityToBigger;
	
	printf("\n~~~~~CreateDestroyTest~~~~~\n");
	queue1 = PQCreate(priority_func, NULL);
	queue2 = PQCreate(priority_func, NULL);
	PQDestroy(queue1);
	
	PQEnqueue(queue2, &a);
	PQDestroy(queue2);
	
	return status;
}

int PriorityToBigger(const void *new_data, const void *current_data, \
void *param)
{
	(void)param;
	if (*(int *)new_data > *(int *)current_data)
	{
		return 1;
	}
	else if (*(int *)new_data < *(int *)current_data)
	{
		return -1;
	}
	return 0;
}

int PriorityToLongerStringLen(const void *new_data, const void *current_data, \
void *param)
{
	(void)param;
	if (strlen((char *)new_data) > strlen((char *)current_data))
	{
		return 1;
	}
	else if (strlen((char *)new_data) < strlen((char *)current_data))
	{
		return -1;
	}
	return 0;
}

int EnqueueTest()
{
	int status = 0;
	int a = 2;
	int b = 5;
	int c = 3;
	int d = 4;
	int e = -1;
	
	char str1[] = "All"; 
	char str2[] = "the"; 
	char str3[] = "rage"; 
	char str4[] = "back";  
	char str5[] = "home";
	
	pq_cmp_func_t priority_func = PriorityToBigger;
	pq_t *queue1 = PQCreate(priority_func, NULL);
	
	printf("\n~~~~~EnqueueTest~~~~~\n");
	status += PQEnqueue(queue1, &a); 
	status += ValCheckPtr(PQPeek(queue1), &a, __LINE__);
	status += PQEnqueue(queue1, &b); 
	status += ValCheckPtr(PQPeek(queue1), &b, __LINE__);
	status += PQEnqueue(queue1, &c); 
	status += ValCheckPtr(PQPeek(queue1), &b, __LINE__);
	status += PQEnqueue(queue1, &d); 
	status += ValCheckPtr(PQPeek(queue1), &b, __LINE__);
	status += PQEnqueue(queue1, &e); 
	status += ValCheckPtr(PQPeek(queue1), &b, __LINE__);

	PQDestroy(queue1);
	
	priority_func = PriorityToLongerStringLen;
	queue1 = PQCreate(priority_func, NULL);
	
	status += PQEnqueue(queue1, &str1);
	status += CmpStrings(PQPeek(queue1), str1, __LINE__);
	status += PQEnqueue(queue1, &str2);
	status += CmpStrings(PQPeek(queue1), str1, __LINE__);
	status += PQEnqueue(queue1, &str3);
	status += CmpStrings(PQPeek(queue1), str3, __LINE__);
	status += PQEnqueue(queue1, &str4);
	status += CmpStrings(PQPeek(queue1), str3, __LINE__);
	status += PQEnqueue(queue1, &str5);
	status += CmpStrings(PQPeek(queue1), str3, __LINE__);
	
	PQDestroy(queue1);

	return status;
}

int DequeuePeekTest()
{
	int status = 0;
	char str1[] = "All"; 
	char str2[] = "th"; 
	char str3[] = "rage"; 
	char str4[] = "back.";  
	char str5[] = "home..";

	pq_cmp_func_t priority_func = PriorityToLongerStringLen;
	pq_t *queue1 = PQCreate(priority_func, NULL);
	
	printf("\n~~~~~DequeuePeekTest~~~~~\n");
	status += PQEnqueue(queue1, &str1);
	status += PQEnqueue(queue1, &str2);
	status += PQEnqueue(queue1, &str3);
	status += PQEnqueue(queue1, &str4);
	status += PQEnqueue(queue1, &str5);
	
	status += CmpStrings(PQPeek(queue1), str5, __LINE__);
	status += CmpStrings(PQDequeue(queue1), str5, __LINE__);
	status += CmpStrings(PQPeek(queue1), str4, __LINE__);
	status += CmpStrings(PQDequeue(queue1), str4, __LINE__);
	status += CmpStrings(PQPeek(queue1), str3, __LINE__);
	status += CmpStrings(PQDequeue(queue1), str3, __LINE__);
	status += CmpStrings(PQPeek(queue1), str1, __LINE__);
	status += CmpStrings(PQDequeue(queue1), str1, __LINE__);
	status += CmpStrings(PQPeek(queue1), str2, __LINE__);
	status += CmpStrings(PQDequeue(queue1), str2, __LINE__);

	PQDestroy(queue1);
	
	return status;
}

int SizeIsEmptyTest()
{
	int status = 0;
	int a = 11;
	int b = 10;
	int c = 20;
	
	pq_cmp_func_t priority_func = PriorityToBigger;
	pq_t *queue1 = PQCreate(priority_func, NULL);
	
	printf("\n~~~~~SizeIsEmptyTest~~~~~\n");
	status += ValCheck(PQSize(queue1), 0, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_TRUE, __LINE__);
	status += PQEnqueue(queue1, &a);
	status += ValCheck(PQSize(queue1), 1, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_FALSE, __LINE__);
	status += PQEnqueue(queue1, &b);
	status += ValCheck(PQSize(queue1), 2, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_FALSE, __LINE__);
	status += PQEnqueue(queue1, &c);
	status += ValCheck(PQSize(queue1), 3, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_FALSE, __LINE__);
	
	PQDequeue(queue1);
	status += ValCheck(PQSize(queue1), 2, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_FALSE, __LINE__);
	PQDequeue(queue1);
	status += ValCheck(PQSize(queue1), 1, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_FALSE, __LINE__);
	PQDequeue(queue1);
	status += ValCheck(PQSize(queue1), 0, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_TRUE, __LINE__);
	
	PQDestroy(queue1);
	
	return status;
}

int ClearTest()
{
	int status = 0;
	char str1[] = "All"; 
	char str2[] = "the";
	char str3[] = "rage";
	char str4[] = "back";
	char str5[] = "home";

	pq_cmp_func_t priority_func = PriorityToLongerStringLen;
	pq_t *queue1 = PQCreate(priority_func, NULL);
	
	printf("\n~~~~~ClearTest~~~~~\n");
	status += PQEnqueue(queue1, &str1);
	status += PQEnqueue(queue1, &str2);
	status += PQEnqueue(queue1, &str3);
	status += PQEnqueue(queue1, &str4);
	status += PQEnqueue(queue1, &str5);
	status += ValCheck(PQSize(queue1), 5, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_FALSE, __LINE__);
	
	PQClear(queue1);
	status += ValCheck(PQSize(queue1), 0, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_TRUE, __LINE__);
	
	status += PQEnqueue(queue1, &str1);
	status += ValCheck(PQSize(queue1), 1, __LINE__);
	status += ValCheck(PQIsEmpty(queue1), BOOL_FALSE, __LINE__);
	
	PQDestroy(queue1);
	
	return status;
}

int FindInt(const void *current_data, void *param)
{
	return (*(int *)current_data == *(int *)param);
}

int FindEqualStrLen(const void *current_data, void *param)
{
	return (strlen((char *)current_data) == *(size_t *)param);
}

int EraseTest()
{
	int status = 0;
	int a = 2;
	int b = 5;
	int c = 3;
	int d = 4;
	int e = -1;
	
	char str1[] = "All"; 
	char str2[] = "th"; 
	char str3[] = "rage"; 
	char str4[] = "back.";  
	char str5[] = "home..";
	
	void *res_val = NULL;
	size_t param = 0;
	pq_is_match_t is_match = FindInt;
	pq_cmp_func_t priority_func = PriorityToBigger;
	pq_t *queue1 = PQCreate(priority_func, NULL);
	
	printf("\n~~~~~EraseTest~~~~~\n");
	status += PQEnqueue(queue1, &a);
	status += PQEnqueue(queue1, &b);
	status += PQEnqueue(queue1, &c);
	status += PQEnqueue(queue1, &d);
	status += PQEnqueue(queue1, &e);
	status += ValCheck(PQSize(queue1), 5, __LINE__);
	
	param = 2;
	res_val = PQErase(queue1, &param, is_match);
	status += ValCheckPtr(res_val, &a, __LINE__);
	status += ValCheck(PQSize(queue1), 4, __LINE__);
	status += ValCheckPtr(PQPeek(queue1), &b, __LINE__);
	
	param = 5;
	res_val = PQErase(queue1, &param, is_match);
	status += ValCheckPtr(res_val, &b, __LINE__);
	status += ValCheck(PQSize(queue1), 3, __LINE__);
	status += ValCheckPtr(PQPeek(queue1), &d, __LINE__);
	
	param = -1;
	res_val = PQErase(queue1, &param, is_match);
	status += ValCheck(PQSize(queue1), 2, __LINE__);
	status += ValCheckPtr(PQPeek(queue1), &d, __LINE__);
	
	PQDestroy(queue1);
	
	is_match = FindEqualStrLen;
	priority_func = PriorityToLongerStringLen;
	queue1 = PQCreate(priority_func, NULL);
	
	status += PQEnqueue(queue1, &str1);
	status += PQEnqueue(queue1, &str2);
	status += PQEnqueue(queue1, &str3);
	status += PQEnqueue(queue1, &str4);
	status += PQEnqueue(queue1, &str5);
	
	param =1;
	res_val = PQErase(queue1, &param, is_match);
	status += ValCheck(PQSize(queue1), 5, __LINE__);
	status += ValCheckPtr(PQPeek(queue1), &str5, __LINE__);
	
	param = 6;
	res_val = PQErase(queue1, &param, is_match);
	status += CmpStrings(res_val, &str5, __LINE__);
	status += ValCheck(PQSize(queue1), 4, __LINE__);
	status += CmpStrings(PQPeek(queue1), &str4, __LINE__);
	
	param = 3;
	res_val = PQErase(queue1, &param, is_match);
	status += CmpStrings(res_val, &str1, __LINE__);
	status += ValCheck(PQSize(queue1), 3, __LINE__);
	status += CmpStrings(PQPeek(queue1), &str4, __LINE__);
	
	PQDestroy(queue1);

	return status;
}
