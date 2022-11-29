/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 24/02/2022
File: Structs
Description: Exercise 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc, realloc*/
#include <string.h>/*strcpy, sprintf, strlen*/

#define ARR_SIZE 3
#define ADD_NUM_MAX_SIZE 200

enum check
{
	SUCCESS,
	FAIL
};

typedef struct Elements
{
	void *data;
	int (*add)(void *, int);
	int (*print)(void *);
	int (*free)(void *);
} element_t;

/*Print*/
int PrintArray(element_t *arr);
int PrintInt(void *value);
int PrintFloat(void *value);
int PrintString(void *value);
/*Add*/
int AddArray(element_t *arr, int num);
int AddToInt(void *value, int num);
int AddToFloat(void *value, int num);
int AddToString(void *value, int num);
/*Free*/
int FreeArray(element_t *arr);
int FreeSring(void *value);
int FreeNothing(void *value);
/*Initielize*/
int Init(element_t *arr_elements);

int main()
{
	int add_num = 0;

	element_t arr_elements[ARR_SIZE] =
	{
		{NULL, AddToInt, PrintInt, FreeNothing},
		{NULL, AddToFloat, PrintFloat, FreeNothing},
		{NULL, AddToString, PrintString, FreeSring}
	};
	
	if(FAIL == Init(arr_elements))
	{
		return FAIL;
	}
	
	add_num = 10;
	
	PrintArray(arr_elements);
	AddArray(arr_elements, add_num);
	PrintArray(arr_elements);
	FreeArray(arr_elements);
	
	return SUCCESS;
}

int Init(element_t *arr_elements)
{
	*(int *)&arr_elements[0].data = 4;
	*(float *)&arr_elements[1].data = 6.3;
	
	arr_elements[2].data = (char *)malloc(sizeof("hello") + 1);
	
	if(NULL == (char *)arr_elements[2].data)
	{
		return FAIL;
	}
	
	strcpy(arr_elements[2].data, "hello");
	
	return SUCCESS;
}

int PrintArray(element_t *arr)
{
	int i = 0;
	
	for(i = 0; ARR_SIZE > i; ++i)
	{
		(arr[i].print)(arr[i].data);
	}
	
	return SUCCESS;
}

int PrintInt(void *value)
{
	printf("%d\n", *((int *)&value));
	
	return SUCCESS;
}

int PrintFloat(void *value)
{
	printf("%f\n", *((float *)&value));
	
	return SUCCESS;
}

int PrintString(void *value)
{
	printf("%s\n", (char *)value);
	return SUCCESS;
}

int AddArray(element_t *arr, int num)
{
	int i = 0;
	
	for(i = 0; ARR_SIZE > i; ++i)
	{
		(arr[i].add)(&arr[i].data, num);
	}
	
	return SUCCESS;
}

int AddToInt(void *value, int num)
{
	*((int *)value) += num;
	return SUCCESS;
}

int AddToFloat(void *value, int num)
{
	*((float *)value) += num;
	return SUCCESS;
}

int AddToString(void *value, int num)
{
	char str[ADD_NUM_MAX_SIZE];
	size_t len1 = 0;
	size_t len2 = 0;

	sprintf(str, "%d", num);
	len1 = strlen(*(char **)value);
	len2 = strlen(str);
	
	*(char **)value = realloc(*(char **)value, len1 + len2 + 1);
	
	if(NULL == *(char **)value)
	{
		return FAIL;
	}
	
	strcat(*(char **)value, str);
	
	return SUCCESS;
}

int FreeArray(element_t *arr)
{
	int i = 0;
	
	for(i = 0; i < ARR_SIZE; ++i)
	{
		(arr[i].free)(&arr[i].data);
	}
	
	return SUCCESS;
}

int FreeSring(void *value)
{
	free(*(char **)value);
	value = NULL;
	
	return SUCCESS;
}

int FreeNothing(void *value)
{
	(void)value;
	return SUCCESS;
}



