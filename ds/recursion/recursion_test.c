/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Amir L
Date: 09/05/2022
File: Recursion
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h>/* printf */

#include "recursion.h"

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
                printf("\nTest fail!\n\n");\
                printf("\x1b[0m");\
            }\
        }

enum Test_Status
{
    TEST_SUCCESS, 
	TEST_FAIL
};

static void Fibonaci();
static void String();
static void SinglyLinkedList();
static void Stack();

static int IntComper(int x, int y);

int main()
{
	printf("~~~ Fibonaci ~~~\n\n");	
	Fibonaci();
	printf("\n~~~ String ~~~\n\n");	
	String();
	printf("\n~~~ SinglyLinkedList ~~~\n\n");	
	SinglyLinkedList();
	printf("\n~~~ Stack ~~~\n\n");	
	Stack();
		
	return 0;
}

static void Fibonaci()
{
	int i = 0;
	
	printf("~~~ RecFibonacciIterative ~~~\n");
	
	for(i = 1; i <= 8; ++i)
	{
		printf("RecFibonacciIterative %d: %d\n", i, RecFibonacciIterative(i));
	}
	
	printf("\n~~~ RecFibonacciIterative ~~~\n");
	
	for(i = 1; i <= 8; ++i)
	{
		printf("RecFibonacciIterative %d: %d\n", i, RecFibonacci(i));
	}

}

static void String()
{
	char str1[20] = "hello";
	char str2[20] = "hello";
	char str3[20] = "hello world";
	char str4[20] = "";
	char str5[20] = " world";
	char hysrtack[20] = "i love bananas";
	char needle[20] = "love";
	char result[] = "love bananas";
	char *search_result = NULL;
	
	

	printf("~~~ RecStrLen ~~~\n");
	RUNTEST(IntComper(RecStrLen(str1), 5));
	
	printf("~~~ RecStrCmp ~~~\n");
	RUNTEST(IntComper(!!RecStrCmp(str1, str2), 0));
	RUNTEST(IntComper(!!RecStrCmp(str1, str3), 1));
	RUNTEST(IntComper(!!RecStrCmp(str1, str4), 1));
	
	printf("~~~ RecStrCpy ~~~\n");
	RUNTEST(IntComper(!!RecStrCmp(RecStrCpy(str4 ,str3), str3), 0));
	
	printf("~~~ RecStrCat ~~~\n");
	RUNTEST(IntComper(!!RecStrCmp(RecStrCat(str1 ,str5), str3), 0));
	
	printf("~~~ RecStrStr ~~~\n");
	search_result = RecStrStr(hysrtack, needle);
	RUNTEST(IntComper(!!RecStrCmp(search_result ,result), 0));
	
	search_result = RecStrStr(hysrtack, str1);
	RUNTEST(IntComper(NULL == search_result, 1));
}

static void SinglyLinkedList()
{
	node_t *start_node = NULL;
	node_t *runner = NULL;
	
	start_node = SLLCreate(1);
	start_node = SLLInsertBefore(start_node , 2);
	start_node = SLLInsertBefore(start_node , 3);
	start_node = SLLInsertBefore(start_node , 4);
	start_node = SLLInsertBefore(start_node , 5);
	
	printf("Before flip\n");
	runner = start_node;
	while(NULL != runner)
	{
		printf("sll: %d\n", SLLGetValue(runner));
		runner = SLLNext(runner);
	}

	start_node = RecFlipList(start_node);
	
	printf("\nAfter flip\n");
	runner = start_node;
	while(NULL != runner)
	{
		printf("sll: %d\n", SLLGetValue(runner));
		runner = SLLNext(runner);
	}
	
	SLLDestroy(start_node);
	start_node = NULL;
	runner = NULL;
}

static void Stack()
{
	stack_t *stack = NULL;
	
	stack = StackCreate(10);
	
	StackPush(stack, 2);
	StackPush(stack, 8);
	StackPush(stack, 5);
	StackPush(stack, 6);
	StackPush(stack, 1);
	StackPush(stack, 9);
	StackPush(stack, 0);
	StackPush(stack, 3);
	StackPush(stack, 7);
	StackPush(stack, 4);
	
	RecSortStack(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 9));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 8));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 7));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 6));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 5));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 4));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 3));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 2));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 1));
	StackPop(stack);
	
	RUNTEST(IntComper(StackPeek(stack), 0));
	StackPop(stack);
	
	StackDestroy(stack);
}

static int IntComper(int x, int y)
{
	if(x != y)
	{
		return TEST_FAIL;
	}
	
	return TEST_SUCCESS;
}


