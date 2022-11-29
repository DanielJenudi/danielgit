/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 28/02/2022
File: Word Boundary Optimization
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "ex9.h"

void Test_Memset();
void Test_Memcpy();
void Test_Memmove();

int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	char str[] = "hello my name is daniel";
	int i = 0;
	
	printf("defulte:\n");
	
	for(i = 0; 5 > i; ++i)
	{
		printf("%d\n",arr[i]); 
	}
	
	printf("%s\n",str);
	
	Test_Memset();
	Test_Memcpy();
	Test_Memmove();
	
	return 0;
}

void Test_Memset()
{
	int arr[] = {1, 2, 3, 4, 5};
	char str[] = "hello my name is daniel";
	int i = 0;	
	
	Memset(arr, 1, 9);
	Memset(str, '!', 9);
	
	printf("\nMemset:\n");
	
	for(i = 0; 5 > i; ++i)
	{
		printf("%d\n",arr[i]); 
	}
	
	printf("%s\n",str);
}

void Test_Memcpy()
{
	int arr[] = {1, 2, 3, 4, 5};
	int arr_c[50] = {0};
	char str[] = "hello my name is daniel";
	char str_c[100] = {'\0'};
	int i = 0;
	
	Memcpy(arr_c, arr, 15);
	Memcpy(str_c, str, 11);
	
	printf("\nMemcpy:\n");
	
	for(i = 0; 5 > i; ++i)
	{
		printf("%d\n",arr_c[i]); 
	}
	
	printf("%s\n",str_c);
}

void Test_Memmove()
{
	int arr[] = {1, 2, 3, 4, 5};
	char str[] = "hello my name is daniel";
	int i = 0;
	
	Memmove(arr + 3, arr, 8);
	Memmove(str + 2, str, 4);
	
	printf("\nMemmove:\n");
	
	for(i = 0; 5 > i; ++i)
	{
		printf("%d\n",arr[i]); 
	}
	
	printf("%s\n",str);
}


