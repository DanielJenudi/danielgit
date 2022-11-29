#include <stdio.h> /* printf */
#include <ctype.h> /*isupper*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "strings.h" /* strlen */

size_t StrLen(const char *str)
{
	int length = 0;
	assert(NULL != str);
	while ('\0' != *str)
	{
		++length;
		++str;
	}	
	return length;
} 

int StrCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	while( (*str1 == *str2) && ('\0' != *str1) )
	{	
		++str1;   
		++str2;
	}

	return *str1-*str2;
}

int StrnCmp(const char *str1, const char *str2, size_t n)
{
	size_t i = 1;
	assert(NULL != str1);
	assert(NULL != str2);
	if ( 0 == n )
	{
		return 0;
	}
	while(*str1 == *str2 && i < n)
	{	
		++str1;   
		++str2;
		++i;
	}

	return *str1-*str2;
}

