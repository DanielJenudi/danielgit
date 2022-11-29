/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Eyad
Date: 01/03/2022
File: Word Boundary Optimization part2
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "ex10.h"

void Test_Itoa();
void Test_Atoi();
void Test_ItoaBase36();
void Test_AtoiBase36();
void Test_Print3Arr();

int main()
{
	Test_Itoa();
	Test_Atoi();
	Test_ItoaBase36();
	Test_AtoiBase36();
	Test_Print3Arr();
	WhichEndian();
	
	return 0;
}

void Test_Itoa()
{
	char str[100];
	int num = 123456;
	
	printf("Test_Itoa:\n");
	Itoa(num, str);
	printf("str:%s\n", str);
}

void Test_Atoi()
{
	char str1[] = "3.109";
	char str2[] = "-09";
	
	printf("\nTest_Atoi:\n");
	printf("str1:%d\n", Atoi(str1));
	printf("str2:%d\n", Atoi(str2));
}

void Test_ItoaBase36()
{
	char str[100];
	int num = 1234567;
	
	printf("\nTest_ItoaBase36:\n");
	ItoaBase36(num, str, 36);
	printf("str:%s\n", str);
}

void Test_AtoiBase36()
{
	char str1[] = "QGLJ";
	char str2[] = "-0A9";
	
	printf("\nTest_ItoaBase36:\n");
	printf("str1:%d\n", AtoiBase36(str1, 36));
	printf("str2:%d\n", AtoiBase36(str2, 17));
}

void Test_Print3Arr()
{
	char arr1[] = {'a', 'b', 'c', 'D', '!', 'q', 'q'};
	char arr2[] = {'D', '!', 'c', 'D', 'a', 'q'};
	char arr3[] = {'l', 'l', 'c', 'c', 'r'};
	
	size_t size1 = sizeof(arr1)/sizeof(char);
	size_t size2 = sizeof(arr2)/sizeof(char);
	size_t size3 = sizeof(arr3)/sizeof(char);

	printf("\nTest_Print3Arr:\n");
	Print3Arr(arr1, arr2, arr3, size1, size2, size3);
	printf("\n");
}


