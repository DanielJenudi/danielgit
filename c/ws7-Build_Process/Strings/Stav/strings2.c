
#include <stdio.h> /* printf */
#include <ctype.h> /*isupper*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "strings.h" /* strlen */

int StrCasecmp(const char *str1, const char *str2)
{
	char *copy_str1 = 0;
	char *copy_str2 = 0;
	copy_str1 =(char *) str1;
	copy_str2 =(char *)str2;
	while(*copy_str1 && tolower(*copy_str1) == tolower(*copy_str2))
	{	
	        ++copy_str1;
	        ++copy_str2;
	}
	return tolower(*copy_str1) - tolower(*copy_str2) ;
}

char *StrCpy (char *dest, const char *src)
{
	int i = 0;
	assert(NULL != dest);
	assert(NULL != src);
	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		++i;
	}
	
	return dest;
}

