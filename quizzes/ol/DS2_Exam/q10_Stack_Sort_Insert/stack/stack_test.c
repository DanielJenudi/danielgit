
#include <assert.h> /* assert */
#include <stdio.h>	/* printf */
#include "stack.h"

enum status
{
	SUCCESS = 0,
	FAIL
};

void StackSortInsertTest();
void StackInsert(stack_t *stack, int *num);
void PrintStack(stack_t *stack);

int main()
{
	StackSortInsertTest();

	return 0;
}

void StackSortInsertTest()
{
	stack_t *stack = StackCreate(8, sizeof(int));
	int a = 7, b = 4, c = -1, d = -4, e = 13, f = 5;

	printf("----------Stack Sort Insert test----------\n");
	StackInsert(stack, &a);
	StackInsert(stack, &b);
	StackInsert(stack, &c);
	StackInsert(stack, &d);
	StackInsert(stack, &e);
	StackInsert(stack, &f);

	PrintStack(stack);

	StackDestroy(stack);
	stack = NULL;
}

void StackInsert(stack_t *stack, int *num)
{
	int temp = 0;

	assert(NULL != stack);

	if ((StackIsEmpty(stack)) || (*num > *(int *)StackPeek(stack)))
	{
		StackPush(stack, num);
		return;
	}

	temp = *(int *)StackPeek(stack);
	StackPop(stack);
	StackInsert(stack, num);
	StackPush(stack, &temp);
}

void PrintStack(stack_t *stack)
{
	while (!StackIsEmpty(stack))
	{
		printf("%d\n", *(int *)StackPeek(stack));
		StackPop(stack);
	}
}
