/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Chen Rudi
Date: 09/03/2022
File: Data struct - Dynamic vactor
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/
#include <string.h>/*strcmp*/
#include "d_vector.h"

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
	SUCCESS,
	FAIL
};


int TestIntVactor();
int TestStringVactor();
int StringComper(char *x, char *y);
int IntComper(int x, int y);

int main()
{
	/*RUNTEST(TestIntVactor());	*/
	RUNTEST(TestStringVactor());
	
	return 0;
}

int TestIntVactor()
{

	int count = 0;
	d_vector_t *vector = VectorCreate(sizeof(int), 10);
	
	printf("--- TestIntVactor ---\n");
	
	count += IntComper(*(int *)VectorGetElement(vector, 1), 0);
	count += IntComper(VectorIsEmpty(vector), 1);
	
	VectorPushBack(vector, (void *)5);
	VectorPushBack(vector, (void *)8);
	
	count += IntComper(VectorIsEmpty(vector), 0);
	count += IntComper(VectorSize(vector), 2);
	count += IntComper(Vectorcapacity(vector), 10);
	count += IntComper(*(int *)VectorGetElement(vector, 0), 5);
	count += IntComper(*(int *)VectorGetElement(vector, 1), 8);
	
	VectorPopBack(vector);
	
	count += IntComper(VectorSize(vector), 1);
	
	VectorPushBack(vector, (void *)10);
	VectorPushBack(vector, (void *)11);
	VectorPushBack(vector, (void *)12);
	VectorPushBack(vector, (void *)13);
	
	count += IntComper(VectorSize(vector), 5);
	count += IntComper(Vectorcapacity(vector), 10);
	count += IntComper(*(int *)VectorGetElement(vector, 1), 10);
	
	VectorReserve(vector, 2);
	count += IntComper(VectorSize(vector), 5);
	count += IntComper(Vectorcapacity(vector), 6);
	count += IntComper(*(int *)VectorGetElement(vector, 2), 11);
	
	count += IntComper(VectorReserve(vector, 20), 0);
	count += IntComper(Vectorcapacity(vector), 20);
	count += IntComper(VectorShrinkToFit(vector), 0);
	count += IntComper(Vectorcapacity(vector), 6);
	
	VectorDestroy(vector);
	vector = NULL;
	
	return count;
}

int TestStringVactor()
{
	int count = 0;
	d_vector_t *vector = VectorCreate(sizeof(char *), 10);
	
	char str1[] = "chen";
	char str2[] = "happy";
	char str3[] = "woman";
	char str4[] = "day!";
	char str5[] = "now go to the kitchen";
	
	printf("--- TestStringVactor ---\n");
	
	count += IntComper(VectorIsEmpty(vector), 1);
	
	VectorPushBack(vector, (void *)str1);
	VectorPushBack(vector, (void *)str2);
	
	count += IntComper(VectorIsEmpty(vector), 0);
	count += IntComper(VectorSize(vector), 2);
	count += IntComper(Vectorcapacity(vector), 10);
	count += StringComper((char *)VectorGetElement(vector, 0), str1);
	count += StringComper((char *)VectorGetElement(vector, 1), str2);
	
	VectorPopBack(vector);
	
	count += IntComper(VectorSize(vector), 1);
	
	VectorPushBack(vector, (void *)str2);
	VectorPushBack(vector, (void *)str3);
	VectorPushBack(vector, (void *)str4);
	VectorPushBack(vector, (void *)str5);
	
	count += IntComper(VectorSize(vector), 5);
	count += IntComper(Vectorcapacity(vector), 10);
	count += StringComper((char *)VectorGetElement(vector, 1), str2);
	
	VectorReserve(vector, 2);
	count += IntComper(VectorSize(vector), 5);
	count += IntComper(Vectorcapacity(vector), 6);
	count += StringComper((char *)VectorGetElement(vector, 2), str3);
	
	count += IntComper(VectorReserve(vector, 20), 0);
	count += IntComper(Vectorcapacity(vector), 20);
	count += IntComper(VectorShrinkToFit(vector), 0);
	count += IntComper(Vectorcapacity(vector), 6);
	
	VectorDestroy(vector);
	
	return count;
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}

int StringComper(char *x, char *y)
{
	if(0 != strcmp(x, y))
	{
		return FAIL;
	}
	
	return SUCCESS;
}



















