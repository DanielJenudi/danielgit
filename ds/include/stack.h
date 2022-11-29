/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: 
Date: 06/03/2022
File: Data struct - Bit Array
Description: Header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef __ILRDSTACK__
#define __ILRDSTACK__

typedef struct Stack stack_t; 

stack_t *StackCreate(size_t capacity,size_t element_size);/*new stack allocate*/
void StackDestroy(stack_t *stack);/*free allocate stack*/

void StackPop(stack_t *stack);/*remove the top variable*/
void StackPush(stack_t *stack, void *data);/*add new variable to the top*/

void *StackPeek(const stack_t *stack);/*returns the top variable*/
int StackIsEmpty(const stack_t *stack);/*if the stack empty return true*/

size_t StackSize(const stack_t *stack);/*return the stack size*/
size_t StackCapacity(const stack_t *stack);/*return the stack Capacity*/

#endif   /*__ILRDSTACK__*/
