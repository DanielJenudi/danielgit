#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>


/*return the length of string*/
size_t StrLen(const char *str)
{
	size_t count = 0; 

	assert(NULL != str);/*check for null pointer*/
	
	while( *(count + str) != '\0')
	{
		count ++;
	}	
	
	return count;
}

/*copy array to new array*/
char *StrCpy(char *dest, const char *src)
{	
	while( '\0' != *src )
	{
		*dest = *src;
		++dest;
		++src;			
	}
	
	*dest = '\0';
	
	return dest;
}

/*copy n chars of array to new array*/
char *StrnCpy(char *dest, const char *src, size_t n)
{
	
	assert(NULL != src);
	assert(NULL != dest);
	
	while( 0 < n && '\0' != *src )
	{
		*dest = *src;
		++dest;
		++src;	
		--n;		
	}
	
	while(n > 0)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return dest;
}

/*check if tow strings are the same*/
int StrCmp(const char *str1, const char *str2)
{		
	assert(NULL != str1);/*check for null pointer*/
	assert(NULL != str2);/*check for null pointer*/

	while('\0' != *str1 || '\0' != *str2)
	{
		
		if ( *str1 != *str2 )
			{
				return	(int)*str1 - (int)*str2;	
			}
		++str1;
		++str2;
	}	
	return 0;
}

/*check if tow strings are the same until n char*/
int StrnCmp(const char *str1, const char *str2, size_t n)
{		
	assert(NULL != str1);/*check for null pointer*/
	assert(NULL != str2);/*check for null pointer*/

	while( ('\0' != *str1 || '\0' != *str2) && 0 < (int)n)
	{
		
		if ( *str1 != *str2 )
			{
				return	(int)*str1 - (int)*str2;	
			}
		++str1;
		++str2;
		--n;
	}	
	return 0;
}

/*check if tow strings are the same without alphbetic UPPER/lower diffrents*/
int StrCasecmp(const char *str1, const char *str2)
{	
	assert(NULL != str1);/*check for null pointer*/
	assert(NULL != str2);/*check for null pointer*/

	while( '\0' != *str1 || '\0' != *str2 )
	{
		
		if ( tolower(*str1) != tolower(*str2) )
			{
				return	(int)*str1 - (int)*str2;	
			}
		++str1;
		++str2;
	}	
	return 0;
}

/*return the addres of char in the first appearance*/
char *StrChr(const char *str, int c)
{	
	assert(NULL != str);/*check for null pointer*/
	
	while( '\0' != *str )
	{
		if( *str == c )
		{
			return (char *)str;
		}
		++str;
	}
	
	if( 0 == c)
		{
			return (char *)str;
		}
		
	return NULL;
}

/*return new pointer with a copy of a string*/
char *StrDup(const char *str1)
{	
	char *ptr = NULL;
	
	assert(NULL != str1);/*check for null pointer*/
		
	ptr = (char *)calloc(StrLen(str1) + 1, sizeof(char));
	
	if(NULL == ptr)
	{
		return NULL;
	}
	
	StrCpy(ptr, str1);
	
	return ptr;
}

/*return contcatenat tow strings*/
char *StrCat(char *dest, const char *src)
{
	assert(NULL != dest);/*check for null pointer*/
	assert(NULL != src);/*check for null pointer*/
	
	StrCpy(dest + StrLen(dest), src);
	return dest;
}

/*return contcatenat n chars form src string to dest string*/
char *StrnCat(char *dest, const char *src, size_t n)
{
	assert(NULL != dest);/*check for null pointer*/
	assert(NULL != src);/*check for null pointer*/

	StrnCpy(dest + StrLen(dest), src, n);
	return dest;
}

/*return the location of needle in haystack*/
char *StrStr(const char *haystack, const char *needle)
{	
	size_t size = StrLen(needle);
	char *temp = NULL;
	
	assert(NULL != haystack);/*check for null pointer*/
	assert(NULL != needle);/*check for null pointer*/
	
	temp = StrChr(haystack, (int)*needle);

	while(NULL != temp)
	{
		if(0 == StrnCmp(temp, needle, size))
		{
			return temp;
		}
		temp = StrChr(temp + 1, (int)*needle);
	}
	return temp;		
}

size_t StrSpn(const char *str1, const char *str2)
{
	size_t count = 0;
	
	assert(NULL != str1);/*check for null pointer*/
	assert(NULL != str2);/*check for null pointer*/	
	
	while('\0' != *str1) 
	{
		if(NULL == StrChr(str2, (int)*str1))
		{
			return count;
		}
		++count;
		++str1;	
	}
	
	return count;
}




