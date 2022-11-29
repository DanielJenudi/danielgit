
#include <stdio.h> /* printf */
#include <ctype.h> /*isupper*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "strings.h" /* strlen */

char *StrCat(char *dest, const char *src)
{
	int dest_length = StrLen((char*)dest);
	int src_length = StrLen((char*)src);
	dest += dest_length;
	while ( *(src) )
	{
		*dest = *src;
		++dest;
		++src;
	}
	dest -= (dest_length + src_length);
	return dest;
}

char *StrnCat(char *dest, const char *src, size_t n)
{
	size_t i = 0;
	int length_d = StrLen((char*)dest);
	int length_s = StrLen((char*)src);
	for ( i = 0 ; i < length_s && i < n ; ++i)
	{
		*(dest + i + length_d) = *(src ++);
	}
	return dest;
}

char *StrStr(const char *haystack, const char *needle)
{
	int count = 0 ;
	int length_needle = StrLen((char*)needle);
	if (!*needle)
	{
		return (char *)haystack;
	}
	while  (*haystack)
	{
		while (*needle && *needle == *(haystack + count))
		{
			if (count == length_needle-1)
			{
				return (char *)haystack;
			}
			++count;
			++needle;
		}
		++haystack;
	} 
	return NULL;
}

size_t StrSpn(const char *str1, const char *str2)
{
	size_t count = 0;
	while (*str1)
	
	{
		if (!StrChr(str2 , *str1) ) 
		{
			return count;
		}
		++count;
		++str1;
	}
	return count;
}


