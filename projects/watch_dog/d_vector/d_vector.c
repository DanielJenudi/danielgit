/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Chen Rudi
Date: 09/03/2022
File: Data struct - Dynamic vactor
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdlib.h>/*malloc, realloc, free*/
#include <assert.h>/*assert*/
#include <string.h>/*memmove*/
#include "d_vector.h"

#define DEFULTE_SIZE 5

struct vector 
{
    void *data;
    size_t size;
    size_t element_size;
    size_t capacity;
};

d_vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	d_vector_t *vector = (d_vector_t *)malloc(sizeof(d_vector_t));
	if(NULL == vector)
	{
		return NULL;
	}
	
	capacity = (capacity == 0 ? DEFULTE_SIZE : capacity);
	
	vector->data = malloc(capacity * element_size);
	if(NULL == vector->data)
	{
		free(vector);
		return NULL;
	}
	
	vector->size = 0;
	vector->element_size = element_size;
	vector->capacity = capacity;
	
	return vector;
}

void VectorDestroy(d_vector_t *vector)
{
	assert(NULL != vector);
	free(vector->data);
	free(vector);
}

int VectorReserve(d_vector_t *vector, size_t new_capacity)
{
	void *backup = NULL;
	assert(NULL != vector);

	if(new_capacity == vector->capacity)
	{
		return 0;
	}
	
	if(new_capacity <= vector->size)
	{
		new_capacity = vector->size + 1;
	}
	
	backup = vector->data;
	vector->data = realloc(vector->data, new_capacity * vector->element_size);
	
	if(NULL == vector->data)
	{
		vector->data = backup;
		return 1;
	}

	vector->capacity = new_capacity;
	
	return 0;
}

int VectorShrinkToFit(d_vector_t *vector)
{
	assert(NULL != vector);
	return VectorReserve(vector, vector->size + 1);
}

int VectorPushBack(d_vector_t *vector,const void *data)
{
	size_t input_position = 0;
	
	assert(NULL != vector);
	assert((vector->size) != vector->capacity);

	input_position = (vector->size)*(vector->element_size);
	
	memmove(((char *)(vector->data) + input_position), data,
		vector->element_size);
		
	vector->size += 1;
	
	if(vector->size == vector->capacity)
	{
		return VectorReserve(vector, vector->size * 2);	
	}
	
	return 0;
}

int VectorPopBack(d_vector_t  *vector)
{
	vector->size -= 1;
	
	assert(NULL != vector);
	
	if(vector->size <= (vector->capacity / 4))
	{
		return VectorReserve(vector, vector->capacity / 2);	
	}
	
	return 0;
}

void *VectorGetElement(const d_vector_t *vector, size_t index)
{
	size_t position = (index)*(vector->element_size);
	
	assert(NULL != vector);
	assert(index <= (vector->capacity));
	
	return (char *)(vector->data) + position;
}

size_t VectorSize(const d_vector_t *vector)
{
	assert(NULL != vector);
	return vector->size;
}

size_t Vectorcapacity(const d_vector_t *vector)
{
	assert(NULL != vector);
	return vector->capacity;
}

int VectorIsEmpty(const d_vector_t *vector)
{
	assert(NULL != vector);
	return (0 == vector->size ? 1 : 0);	
}


