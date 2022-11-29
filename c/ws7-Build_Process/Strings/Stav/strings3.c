
#include <stdio.h> /* printf */
#include <ctype.h> /*isupper*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "strings.h" /* strlen */

char *StrnCpy(char *dest, const char *src, size_t n)
{
	size_t len = n;
	assert(NULL != dest);
	assert(NULL != src);
	while ( '\0' != *src && n )
	{
		*dest= *src;
		++src;
		++dest;
		--n;
	}
	while (n)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return dest - len ;
}	

char *StrChr(const char *str, int c)
{
	while ( '\0' != *str )
	{
		if ( c == *str)
		{
			return  (char *)str;
		}
		++str;
	}	
	return NULL;
}

char *StrDup(const char *str1)
{
	size_t length = StrLen(str1) +1 ;
	char *str2 = malloc(length);
	if( NULL == str2)
	{
		return NULL;
	}
	return StrCpy(str2,str1);
}

