/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 01/03/2022
File: Word Boundary Optimization part2
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "ex10.h"

static char *Reverse(char *str);
static void InitBaseItoaLUT(int *arr);
static void InitBaseAtoiLUT(char *arr);
static int findIndex (const char *LUT, char look, int base);
static void Adding(int *LUT, const char *arr, int size, int counter);

/*****Itoa base 10*************************************************************/

char *Itoa(int num, char *str)
{
	char *runner = str;
	
	assert(NULL != str);
	
	while(0 != num)
	{
		*runner = (char)((num % 10) + ASCII_DIFFERENCE);
		++runner;
		num /= 10;
	}
	
	return Reverse(str);
}

static char *Reverse(char *str)
{
	 char *start = NULL;
	 char *end = NULL;
	 char swap = '\0';
	 
	 assert(NULL != str);
	 
	 start = str;
	 end = (str + (strlen(str) - 1));
	 
	 while(end > start)
	 {
	 	swap = *start;
		*start = *end;
		*end = swap;	
		
		--end;
		++start; 
	 }
	 
	return str;
}

/*****Atoi base 10*************************************************************/

int Atoi(char *str)
{
	int resulte = 0;
	int positivity = 1;
	
	assert(NULL != str);
	
	if('-' == *str)
	{
		positivity = (-1);
		++str;
	}
	
	while('\0' != *str && '.' != *str)
	{
		if( ASCII_0 > (int)(*str) || ASCII_9 < (int)(*str))
		{
			return 0;
		}
		
		resulte *= 10;
		resulte += (((int)(*str) - ASCII_DIFFERENCE) % 10);
		++str;	
	}
	
	return resulte * positivity;
}

/*****Itoa any base************************************************************/

char *ItoaBase36(int num, char *str, int base)
{
	char *runner = str;
	int remainder = 0;
	static int is_LUT_init = 0;
	static int base_LUT[36];
	
	assert(NULL != str);
	
	if(0 == is_LUT_init)
	{
		InitBaseItoaLUT(base_LUT);
		++is_LUT_init;
	}
	
	while(0 != num)
	{
		remainder = (num % base);
		*runner = base_LUT[remainder];
		++runner;
		num /= base;
	}
	
	return Reverse(str);
}

static void InitBaseItoaLUT(int *arr)
{
	int i = 0;
	
	assert(NULL != arr);
	
	for(i = ASCII_0; i <= ASCII_9; ++i)
	{
		*arr = i;
		++arr;	
	} 
	
	for(i = ASCII_A; i <= ASCII_Z; ++i)
	{
		*arr = i;
		++arr;	
	} 
}

/*******Atoi any base**********************************************************/

int AtoiBase36(char *str, int base)
{
	int resulte = 0;
	int positivity = 1;
	int temp_value = 0;
	static int is_LUT_init = 0;
	static char base_LUT[36];
	
	assert(NULL != str);
	
	if(0 == is_LUT_init)
	{
		InitBaseAtoiLUT(base_LUT);
		++is_LUT_init;
	}
	
	if('-' == *str)
	{
		positivity = (-1);
		++str;
	}
	
	while('\0' != *str && '.' != *str)
	{
		temp_value = findIndex(base_LUT, *str, base);
		if((-1) == temp_value)
		{
			return 0;
		}
		
		resulte *= base;
		resulte += temp_value;
		++str;	
	}
	
	return resulte * positivity;
}

static int findIndex (const char *LUT, char look, int base)
{
	int i = 0;

	assert(NULL != LUT);
	
	for(i = 0; i < base; ++i)
	{
		if(look == LUT[i])
		{
			return i;
		}
	}
	
	return -1;
}

static void InitBaseAtoiLUT(char *arr)
{
	int i = 0;
	
	assert(NULL != arr);
	
	for(i = ASCII_0; i <= ASCII_9; ++i)
	{
		*arr = (char)i;
		++arr;	
	} 
	
	for(i = ASCII_A; i <= ASCII_Z; ++i)
	{
		*arr = (char)i;
		++arr;	
	} 
}

/*******Print3Arr**************************************************************/


void Print3Arr(const char *arr1, const char *arr2, const char *arr3,
			   size_t size1, size_t size2, size_t size3)
{
	int LUT[ASCII_SIZE] = {0};
	size_t i = 0;
	
	assert(NULL != arr1);
	assert(NULL != arr2);
	assert(NULL != arr3);

	Adding(LUT, arr1, size1, 0);
	Adding(LUT, arr2, size2, 1);
	Adding(LUT, arr3, size3, 2);
	
	for(i = 0; i < ASCII_SIZE; ++i)
	{
		if(2 == LUT[i])
		{
			printf("%c", (char)i);
		}
	}	
}

static void Adding(int *LUT, const char *arr, int size, int round)
{
	int i = 0;

	for(i = 0; i < size; ++i)
	{
		if(round == LUT[(int)arr[i]])
		{
			LUT[(int)arr[i]] += 1;
		}
	}
}
	
/*******WhichEndian - fuction and macro****************************************/

void WhichEndian()
{
	int x = 1;
	
	printf("\nWhichEndian - function:\n");
	
	if('0' == *(char *)&x)
	{
		printf("big endian\n");
	}
	else
	{
		printf("little endian\n");
	}
	
	printf("\nWhichEndian - macro:\n");
	
	if(IS_BIG_ENDIAN)
	{
		printf("big endian\n");
	}
	else
	{
		printf("little endian\n");
	}
	
}

/******************************************************************************/
