
#include <assert.h> /* assert */
#include <stdio.h>	/* printf */
#include "stack.h"

enum status
{
	SUCCESS = 0,
	FAIL
};

void StackSortTest();
int SortStack(stack_t *stack);
void PrintStack(stack_t *stack);

int main()
{
	StackSortTest();

	return 0;
}

void StackSortTest()
{
	stack_t *stack = StackCreate(8, sizeof(int));
	int a = 7, b = 4, c = -1, d = -4, e = 13, f = 5;

	printf("----------Sort test----------\n");
	StackPush(stack, &a);
	StackPush(stack, &b);
	StackPush(stack, &c);
	StackPush(stack, &d);
	StackPush(stack, &e);
	StackPush(stack, &f);

	SortStack(stack);
	PrintStack(stack);

	StackDestroy(stack);
	stack = NULL;
}

void PrintStack(stack_t *stack)
{
	while (!StackIsEmpty(stack))
	{
		printf("%d\n", *(int *)StackPeek(stack));
		StackPop(stack);
	}
}

int SortStack(stack_t *stack)
{
	stack_t *full = NULL;
	stack_t *empty = NULL;
	int max = 0;

	assert(NULL != stack);

	full = StackCreate(StackSize(stack), sizeof(int));
	if (NULL == full)
	{
		return FAIL;
	}

	empty = StackCreate(StackSize(stack), sizeof(int));
	if (NULL == empty)
	{
		StackDestroy(full);
		return FAIL;
	}

	while (!StackIsEmpty(stack))
	{
		StackPush(full, StackPeek(stack));
		StackPop(stack);
	}

	while (!StackIsEmpty(full))
	{
		max = *(int *)StackPeek(full);
		while (!StackIsEmpty(full))
		{
			if (max < *(int *)StackPeek(full))
			{
				max = *(int *)StackPeek(full);
			}
			StackPush(empty, StackPeek(full));
			StackPop(full);
		}
		while (!StackIsEmpty(empty))
		{
			if (max == *(int *)StackPeek(empty))
			{
				StackPush(stack, StackPeek(empty));
			}
			else
			{
				StackPush(full, StackPeek(empty));
			}

			StackPop(empty);
		}
	}

	StackDestroy(full);
	full = NULL;

	StackDestroy(empty);
	empty = NULL;

	return SUCCESS;
}