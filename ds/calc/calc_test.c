/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: 
Date: 01/05/2022
File: Calculate
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include "calc.h"
#include <stdlib.h>
#include <stdio.h>

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
                printf("\nTest TEST_FAILed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

enum Test_Status
{
    TEST_SUCCESS,
	TEST_FAIL
};

static void ResultTEST_FAILTest();
static void ResultTEST_SUCCESSTest();

static int IntComper(int x, int y);


int main()
{
	printf("~~~ ResultTEST_FAILTest ~~~\n");
	ResultTEST_FAILTest();
	printf("~~~ ResultTEST_SUCCESSTest ~~~\n");
	ResultTEST_SUCCESSTest();
	
	return TEST_SUCCESS; 
}

static void ResultTEST_SUCCESSTest()
{
	char str1[100] = "-1+5*3/(1+1+1+1+1)*(-5)";
	char str2[100] = "(1*(2/1))/((0.1+0.3+0.1)*2)";
	char str3[100] = "(-5)*(2*(3*(4/(1+1+1+1)))-1)";
	char str4[100] = "1+(-1)*(-3)-4";
	char str5[100] = "5*23/(2*2.5)";
	char str6[100] = "-2*((1.5*(-1.5)+0.25)*(-2))*(-3)";
	char str7[100] = "(-2)+(-3)+((5))+(((2*21/(11+10))))";
	char str8[100] = "50/5/5*(1+(+1))";
	char str9[100] = "1+100*100/2/2/2/2-1";
	
	double result = 0;

	
	printf("str1: %s\n",str1);
	RUNTEST(IntComper(Calculate(str1, &result), 0));
	RUNTEST(IntComper(result, -16));
	
	printf("str2: %s\n",str2);
	RUNTEST(IntComper(Calculate(str2, &result), 0));
	RUNTEST(IntComper(result, 2));
	
	printf("str3: %s\n",str3);
	RUNTEST(IntComper(Calculate(str3, &result), 0));
	RUNTEST(IntComper(result, -25));
	
	printf("str4: %s\n",str4);
	RUNTEST(IntComper(Calculate(str4, &result), 0));
	RUNTEST(IntComper(result, 0));
	
	printf("str5: %s\n",str5);
	RUNTEST(IntComper(Calculate(str5, &result), 0));
	RUNTEST(IntComper(result, 23));
	
	printf("str6: %s\n",str6);
	RUNTEST(IntComper(Calculate(str6, &result), 0));
	RUNTEST(IntComper(result, 24));
	
	printf("str7: %s\n",str7);
	RUNTEST(IntComper(Calculate(str7, &result), 0));
	RUNTEST(IntComper(result, 2));
	
	printf("str8: %s\n",str8);
	RUNTEST(IntComper(Calculate(str8, &result), 0));
	RUNTEST(IntComper(result, 4));
	
	printf("str9: %s\n",str9);
	RUNTEST(IntComper(Calculate(str9, &result), 0));
	RUNTEST(IntComper(result, 625));
}

static void ResultTEST_FAILTest()
{
	char str1[100] = "11111*()";
	char str2[100] = "1*(2/0)";
	char str3[100] = "(";
	char str4[100] = "+";
	char str5[100] = "((1+1+1)*3)/0";
	char str6[100] = "1++1";
	char str7[100] = "2*3*";
	char str8[100] = "12+{*1}";
	char str9[100] = "34@3)";
	
	double result = 0;

	
	printf("str1: %s\n",str1);
	RUNTEST(IntComper(Calculate(str1, &result), 1));
	
	printf("str2: %s\n",str2);
	RUNTEST(IntComper(Calculate(str2, &result), 2));
	
	printf("str3: %s\n",str3);
	RUNTEST(IntComper(Calculate(str3, &result), 1));
	
	printf("str4: %s\n",str4);
	RUNTEST(IntComper(Calculate(str4, &result), 1));
	
	printf("str5: %s\n",str5);
	RUNTEST(IntComper(Calculate(str5, &result), 2));
	
	printf("str6: %s\n",str6);
	RUNTEST(IntComper(Calculate(str6, &result), 1));
	
	printf("str7: %s\n",str7);
	RUNTEST(IntComper(Calculate(str7, &result), 1));
	
	printf("str8: %s\n",str8);
	RUNTEST(IntComper(Calculate(str8, &result), 1));
	
	printf("str9: %s\n",str9);
	RUNTEST(IntComper(Calculate(str9, &result), 1));
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return TEST_FAIL;
	}
	
	return TEST_SUCCESS;
}

