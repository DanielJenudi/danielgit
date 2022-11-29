/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: 
Date: 06/03/2022
File: Data struct - Bit Array
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/
#include "min_stack.h"


int main()
{
	int a = 5, b = 10, c = 4, d = 20, e = 1;
	mvstack_t *stack = MVcreat(100);
	MVPush(stack, &a);
	MVPush(stack, &b);
	MVPush(stack, &c);
	MVPush(stack, &d);
	MVPush(stack, &e);
	
	printf("peek: %d\n", *(int *)MVPeek(stack));
	printf("min: %d\n", *(int *)MVGetMinVal(stack));
	MVPop(stack);
	printf("peek: %d\n", *(int *)MVPeek(stack));
	printf("min: %d\n", *(int *)MVGetMinVal(stack));
	MVPop(stack);
	printf("peek: %d\n", *(int *)MVPeek(stack));
	printf("min: %d\n", *(int *)MVGetMinVal(stack));
	MVPop(stack);
	printf("peek: %d\n", *(int *)MVPeek(stack));
	printf("min: %d\n", *(int *)MVGetMinVal(stack));
	MVPop(stack);
	printf("peek: %d\n", *(int *)MVPeek(stack));
	printf("min: %d\n", *(int *)MVGetMinVal(stack));
	MVPop(stack);

	
	MVDestroy(stack);
	
	
	return 0;
}

