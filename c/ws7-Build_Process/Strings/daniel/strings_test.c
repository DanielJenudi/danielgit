#include"strings.h"
#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>

void TestStrCpy();
void TestStrnCpy();
void TestStrDup(); 
void TestStrCat();
void TestStrnCat();
void TestStrStr();
void TestStrSpn();


int main()
{

	char string_1[] = {"hi my name is daniel"};
	char string_2[] = {"hi mY Name is daniel"};
		
	printf("strln: %lu\n",StrLen(string_1));/*check strln*/
	
	printf("StrCmp: %d\n",StrCmp(string_1, string_2));/*check strcmp*/
	printf("StrnCmp: %d\n",StrnCmp(string_1, string_2, 5));/*check strncmp*/
	printf("StrCasecmp: %d\n",StrCasecmp(string_1, string_2));/*strcasecmp*/
	
	printf("StrChr: %s\n",StrChr(string_1, 'd'));/*check StrChr*/
	
	TestStrCpy();/*check strcpy*/
	TestStrnCpy();/*check strncpy*/
	TestStrDup();/*check StrDup*/ 
	TestStrCat();/*check strcat*/
	TestStrnCat();/*check strncat*/
	TestStrStr();/*check strstr*/
	TestStrSpn();/*check strspn*/

	return 0;
	
}

void TestStrCpy() 
{
	char string_1[] = {"hi my name is daniel"};
	char string_2[100] = {""};
	
	StrCpy(string_2, string_1);
	printf("StrCpy: ");
	
	printf("%s\n",string_2);		
}

void TestStrnCpy() 
{
	char string_1[] = {"hi my name is daniel"};
	char string_2[100] = {""};
	int n = 5;
	
	StrnCpy(string_2, string_1, n);
	printf("StrnCpy: ");
	
	printf("%s\n",string_2);	
}

void TestStrDup() 
{
	char string[] = {"hi my name is daniel"};
	char *new_str;
	
	new_str = StrDup(string);
	printf("StrnDup: ");
	
	printf("%s\n",new_str);
	
	free(new_str);
	new_str = NULL;
}

void TestStrCat() 
{
	char string_1[100] = {"hi my name is daniel"};
	char string_2[] = {" jenudi"};
	
	StrCat(string_1, string_2);
	printf("StrCat: ");
	printf("%s\n",string_1);		
}

void TestStrnCat() 
{
	char string_1[100] = {"hi my name is daniel"};
	char string_2[] = {" jenudi daniel"};
	
	StrnCat(string_1, string_2, 7);
	printf("StrnCat: ");
	printf("%s\n",string_1);		
}

void TestStrStr() 
{
	char haystack[] = {"hi my name is daniel"};
	char needle[] = {"is"};
	char *result = NULL;
	
	result = StrStr(haystack, needle);
	
	printf("StrnStr: ");
	if(NULL != result)
	{
		printf("%s\n",result);
	}
	else
	{
		printf("not found\n");
	}
}

void TestStrSpn() 
{
	char *str1 = {"abXcd"};
	char *str2 = {"abcd"};
	
	printf("StrnSpn: %lu\n", StrSpn(str1, str2));
}


























