/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 16/02/2022
File: Files
Description: Exercise 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include<stdio.h>/*printf*/

#define SIZE 10

typedef struct print_me
{
	int x;
	void (*func)(int);
} print_me;

void Print(const int x);
void PrintMeTest(print_me *arr);
void PrintMeInitialize(print_me *arr);

int main()
{
	print_me arr_print_me[SIZE];
	
	PrintMeTest(arr_print_me);
	
	return 0;
}

void Print(const int x)
{
	printf("%d ", x);
}

void PrintMeInitialize(print_me *arr)
{
	int i = 0;	
	
	for(i = 0; i < SIZE; ++i)
	{
		arr[i].x = i * 2;
		arr[i].func = Print;
	}
}

void PrintMeTest(print_me *arr)
{
	int i = 0;
	
	PrintMeInitialize(arr);
	
	printf("Exercise 1: ");
	
	for(i = 0; i < SIZE; ++i)
	{
		arr[i].func(arr[i].x);
	}
	
	printf("\nTotal size of print_me arr: %d\n", i);
}

