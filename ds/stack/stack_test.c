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
#include "stack.h"

void Stack_Int_Test();
void Stack_Char_Test();
void Stack_Strings_Test();

int main()
{
	Stack_Int_Test();
	Stack_Char_Test();
	Stack_Strings_Test();
	
	return 0;
}

void Stack_Int_Test()
{
	stack_t *stack = StackCreate(8, sizeof(int));
	int a = 7, b = 4;
	
	printf("----------int test----------\n");
	StackPush(stack, &a);
	StackPush(stack, &b);
	
	printf("is empty? : %d\n", StackIsEmpty(stack));
	printf("stack size: %ld\n", StackSize(stack));
	printf("stack capacity : %ld\n", StackCapacity(stack));
	
	printf("first int: %d\n",*(int *)StackPeek(stack));
	StackPop(stack);
	printf("secound int: %d\n",*(int *)StackPeek(stack));
	StackPop(stack);
	
	printf("is empty? : %d\n", StackIsEmpty(stack));
	printf("stack size: %ld\n", StackSize(stack));
	
	StackDestroy(stack);
	
}

void Stack_Char_Test()
{
	stack_t *stack = StackCreate(20, sizeof(char));
	char a = a, b = b;
	
	
	printf("\n---------char test----------\n");
	StackPush(stack, &a);
	StackPush(stack, &b);
	
	printf("is empty? : %d\n", StackIsEmpty(stack));
	printf("stack size: %ld\n", StackSize(stack));
	printf("stack capacity : %ld\n", StackCapacity(stack));
	
	printf("first char: %c\n",*(char *)StackPeek(stack));
	StackPop(stack);
	printf("secound char: %c\n",*(char *)StackPeek(stack));
	StackPop(stack);
	
	printf("is empty? : %d\n", StackIsEmpty(stack));
	printf("stack size: %ld\n", StackSize(stack));
	
	StackDestroy(stack);
}

void Stack_Strings_Test()
{
	stack_t *stack = StackCreate(40, sizeof(char *));
	
	char str1[] = {"daniel"};
	char str2[] = {"is"};
	char str3[] = {"name"};
	char str4[] = {"my"};
	char str5[] = {"hi"};
	
	printf("\n-------string test----------\n");
	StackPush(stack, &str1);
	StackPush(stack, &str2);
	StackPush(stack, &str3);
	StackPush(stack, &str4);
	StackPush(stack, &str5);
	
	printf("is empty? : %d\n", StackIsEmpty(stack));
	printf("stack size: %ld\n", StackSize(stack));
	printf("stack capacity : %ld\n", StackCapacity(stack));
	
	printf("%s\n",(char *)StackPeek(stack));
	StackPop(stack);
	printf("%s\n",(char *)StackPeek(stack));
	StackPop(stack);
	printf("%s\n",(char *)StackPeek(stack));
	StackPop(stack);
	printf("%s\n",(char *)StackPeek(stack));
	StackPop(stack);
	printf("%s\n",(char *)StackPeek(stack));
	StackPop(stack);

	printf("is empty? : %d\n", StackIsEmpty(stack));
	printf("stack size: %ld\n", StackSize(stack));
	
	StackDestroy(stack);
}


