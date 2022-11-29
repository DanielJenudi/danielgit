#include <string.h>/*strlen*/
#include <stdio.h>/*printf*/
#include <assert.h> /*assert*/
#include <ctype.h> /*isspace*/
#include <stdlib.h> /*malloc , free*/


char *FlipSentence(char *str);

int main(void)
{
	char str[] = "I am student";
	printf("Before Flip: %s\n" , str);
	if (NULL == FlipSentence(str))
	{
		return 1;
	}
	printf("After Flip: %s\n" , str);
	return 0;
}

char *FlipSentence(char *str)
{
	int len = 0;
	char *buffer = NULL;
	char *runner = NULL;
	int n = 0;

	assert( NULL != str);
	
	len = (int)strlen(str);
	buffer = malloc(len + 1);
	runner = str;
	
	if (NULL == buffer)
	{
		return NULL;
	}
	
	*(buffer + len) = '\0';

	while('\0' != *runner)
	{
		++n;
		if(0 != isspace(*runner))
		{
			strncpy(buffer + len - n + 1, runner - n + 1, n - 1);
			buffer[len - n] = ' ';
			len -= n;
			n = 0;
		}
		++runner;
	}
	strncpy(buffer + len - n, runner - n, n);
	str = strcpy(str, buffer);
	free(buffer);
	
	return str;
}
