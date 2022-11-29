/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Date: 28/02/2022
File: Word Boundary Optimization
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "ex9.h"

void *Memset(void *str, int c, size_t n)
{
	size_t i = 0;
	size_t word = c;
	unsigned char *buffer = (unsigned char *)str;
	
	for(i = 0; WORD_SIZE > i; ++i)
	{
		word <<= BYTE_SIZE;
		word |= (char)c; 
	}
	
	i = 0;
	
	while(i != n)
	{
		if(0 == (size_t)(buffer + i) % WORD_SIZE && (n - i) >= WORD_SIZE)
		{
			*(size_t *)(buffer + i) = word;
			i += WORD_SIZE;
		}
		else
		{
			*(buffer + i) = (unsigned char)c;
			++i;	
		}
	}
	
	return str;
}

void *Memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	unsigned char *buffer_dest = (unsigned char *)dest;
	unsigned char *buffer_src = (unsigned char *)src;

	while(i != n) 
	{	
		if(0 == (size_t)(buffer_dest + i) % WORD_SIZE && (n - i) >= WORD_SIZE)
		{
			*(size_t *)(buffer_dest + i) = *(size_t *)(buffer_src + i);
			i += WORD_SIZE;
		}
		else
		{
			*(buffer_dest + i) = *(buffer_src + i);
			++i;	
		}
	}
	
	return dest;
}

void *Memmove(void *str1, const void *str2, size_t n)
{
	unsigned char *runner_dest = (unsigned char *)str1;
	const unsigned char *runner_src = (const unsigned char *)str2;
	
	if((runner_src < runner_dest) && ((runner_src + n) > runner_dest))
	{
		while(0 != n)
		{
			*(runner_dest + n - 1) = *(runner_src + n - 1);
			--n;
		}	
	}
	else
	{
		Memcpy(str1, str2, n);
	}
	
	return str1;
}


