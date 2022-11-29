/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: 
Date: 06/03/2022
File: Data struct - Bit Array
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include <string.h>/*memmove*/
#include "stack.h"

struct Stack 
{
    size_t size;
    size_t element_size;
    size_t capacity;
    void *data;
};

stack_t *StackCreate(size_t capacity,size_t element_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	if(NULL == stack)
	{ 
		return NULL;
	}
	
	stack->data = malloc(capacity * element_size);
	if(NULL == stack->data)
	{
		return NULL;
	}
	
	stack->size = 0;
	stack->element_size = element_size;
	stack->capacity = capacity;
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	free(stack->data);
	free(stack);
}

void StackPush(stack_t *stack, void *data)
{
	size_t input_position = (stack->size)*(stack->element_size);
	assert((stack->size) != stack->capacity);
	
	memmove(((char *)(stack->data) + input_position), data,
			stack->element_size);
	stack->size += 1;
}

void StackPop(stack_t *stack)
{
	assert(0 != (stack->size));
	stack->size -= 1;
}

void *StackPeek(const stack_t *stack)
{
	size_t current_position = (stack->size - 1)*(stack->element_size);
	assert(0 != (stack->size));
	
	return (char *)(stack->data) + current_position;
}

int StackIsEmpty(const stack_t *stack)
{
	return (0 == stack->size ? 1 : 0);
}

size_t StackSize(const stack_t *stack)
{
	return stack->size;
}

size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}











