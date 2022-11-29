/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Osher 
Date: 19/03/2022
File: Data struct - Circular Buffer
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include <string.h>/*memcopy*/

#include "cbuffer.h"

#define SMALLEST(X, Y) (X > Y ? Y : X)

#define BUFFER (char *)(c_buffer->buffer)
#define START_INDEX 0
#define EMPTY_INDEX -1


struct circular_buffer
{
	ssize_t r_pos;
	ssize_t w_pos;
	size_t capacity;
	char buffer[1];
};


static size_t CBSize(const c_buffer_t *c_buffer);


c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *buffer = (c_buffer_t *)calloc(sizeof(c_buffer_t) + capacity,
						  sizeof(char));
	if(NULL == buffer)
	{
		return NULL;
	}
	
	buffer->r_pos = EMPTY_INDEX;
	buffer->w_pos = EMPTY_INDEX;
	buffer->capacity = capacity;
	
	return buffer;
}

void CBufferDestroy(c_buffer_t *c_buffer)
{
	free(c_buffer);
	c_buffer = NULL;
}

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t byte_to_copy = 0;
	size_t rest = 0;
	
	assert(NULL != c_buffer);
	assert(NULL != src);
	
	count = SMALLEST(CBufferFreeSpace(c_buffer), count);

	if(c_buffer->r_pos == EMPTY_INDEX && 0 < count)
	{
		c_buffer->r_pos = START_INDEX;
		c_buffer->w_pos = START_INDEX;
	}
	
	byte_to_copy = SMALLEST(c_buffer->capacity - c_buffer->w_pos, count);
	rest = count - byte_to_copy;
	
	memcpy(BUFFER + c_buffer->w_pos, src, byte_to_copy);
	c_buffer->w_pos = c_buffer->w_pos + byte_to_copy;
	
	if(0 < rest)
	{
		memcpy(BUFFER, (char *)src + byte_to_copy, rest);
		c_buffer->w_pos = rest;
	}
	
	return count;
}

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t byte_to_copy = 0;
	size_t rest = 0;
		
	assert(NULL != c_buffer);
	assert(NULL != dest);	
	
	count = SMALLEST(CBSize(c_buffer), count);
	byte_to_copy = SMALLEST(c_buffer->capacity - c_buffer->r_pos, count);
	rest = count - byte_to_copy;
	
	memcpy(dest, BUFFER + c_buffer->r_pos, byte_to_copy);
	c_buffer->r_pos = c_buffer->r_pos + byte_to_copy;
	
	if(0 < rest)
	{
		memcpy((char *)dest + byte_to_copy, BUFFER, rest);
		c_buffer->r_pos = rest;
	}
	
	if(c_buffer->r_pos == c_buffer->w_pos)
	{
		c_buffer->r_pos = EMPTY_INDEX;
		c_buffer->w_pos = EMPTY_INDEX;
	}

	return count;
}

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	return CBufferCapacity(c_buffer) - CBSize(c_buffer);
}

size_t CBufferCapacity(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	return c_buffer->capacity;
}

int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	return (0 == CBSize(c_buffer));
}

static size_t CBSize(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	if(-1 == c_buffer->r_pos)
	{
		return 0;
	}
	
	if(c_buffer->r_pos < c_buffer->w_pos)
	{
		return c_buffer->w_pos - c_buffer->r_pos; 
	}
	else
	{
		return (c_buffer->capacity - c_buffer->r_pos) + c_buffer->w_pos; 
	}
}



