
#include <stddef.h>
#include <stdlib.h>


#include "min_stack.h"

struct Mstack
{
	stack_t *data;
	stack_t *min;
};

mvstack_t *MVcreat(size_t capacity)
{
	mvstack_t *stack = NULL;
	
	stack = (mvstack_t *)malloc(sizeof(mvstack_t));
	
	stack->data = StackCreate(capacity, sizeof(int));
	stack->min = StackCreate(capacity, sizeof(int));

	return stack; 
}

void MVDestroy(mvstack_t *stack)
{
	StackDestroy(stack->data);
	StackDestroy(stack->min);
	free(stack);
}


void MVPush(mvstack_t *stack, void *data)
{
	StackPush(stack->data, data);
		
	if(StackIsEmpty(stack->min) || *(int *)MVGetMinVal(stack) >= *(int *)data)
	{
		StackPush(stack->min, data);
	}
} 

void MVPop(mvstack_t *stack)
{
	if(*(int *)MVGetMinVal(stack) == *(int *)MVPeek(stack))
	{
		StackPop(stack->min);
	}
	
	StackPop(stack->data);
} 

void *MVPeek(mvstack_t *stack)
{
	return StackPeek(stack->data);
}

void *MVGetMinVal(mvstack_t *stack)
{
	return StackPeek(stack->min);
}























