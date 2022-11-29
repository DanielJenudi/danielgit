/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Amir L
Date: 09/05/2022
File: Recursion
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <assert.h>/* assert */
#include <stdlib.h>/* malloc, free */

#include "recursion.h"


static int StrnCmp(const char *str1, const char *str2, size_t n);
static void SortedInsert(stack_t *stack, int x);

struct singly_linked_list
{
    int data;
    node_t *next;
};

struct stack
{
    int *data;
    size_t capacity;
    size_t size;
};

/* ~~~ stack ~~~ */

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = NULL;
	
	stack = (stack_t *)malloc(sizeof(stack_t));
	if(NULL == stack)
	{
		return NULL;
	}
	
	stack->data = (int *)malloc(capacity * sizeof(int));
	if(NULL == stack->data)
	{
		free(stack);
		stack = NULL;
		return NULL;
	}
	
	stack->capacity = capacity;
	stack->size = 0;
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);

	free(stack->data);
	stack->data = NULL;
	free(stack);
	stack = NULL;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->size != 0);
	--stack->size;
}

int StackPeek(const stack_t *stack)
{
	int *data = NULL;
	assert(stack->size != 0);
	assert(NULL != stack);
	
	data = stack->data;
	return data[stack->size - 1];
}

void StackPush(stack_t *stack, int data)
{
	assert(stack->size != stack->capacity);
	assert(NULL != stack);

	*(stack->data + stack->size) = data;
	++stack->size;
}

int StackIsEmpty(stack_t *stack)
{
	return stack->size == 0;
}

/* ~~~ stack exrecise ~~~ */

stack_t *RecSortStack(stack_t *stack)
{
	int temp = 0;

	if (!StackIsEmpty(stack)) 
	{
     	temp = StackPeek(stack);
        StackPop(stack);
        RecSortStack(stack);
        SortedInsert(stack, temp);
    }
    
    return stack;
}

static void SortedInsert(stack_t *stack, int num)
{
	int temp = 0;

    if (StackIsEmpty(stack) || num > StackPeek(stack)) 
    {
        StackPush(stack, num);
    }
    else
    {
    	temp = StackPeek(stack);
    	StackPop(stack);
    	SortedInsert(stack, num);
 
	 	StackPush(stack, temp);
	}
}

/* ~~~ singly_linked_list ~~~ */

node_t *SLLCreate(int first_data)
{
	node_t *head = NULL;
	head = (node_t *)malloc(sizeof(node_t));
	if(NULL == head)
	{
		return NULL;
	}
	
	head->data = first_data;
	head->next = NULL;
	
	return head;
}

void SLLDestroy(node_t *node)
{
	node_t *runner = NULL;
	node_t *to_free = NULL;
	
	runner = node;
	
	while(NULL != runner)
	{
		to_free = runner;
		runner = SLLNext(runner);
		free(to_free);
		to_free = NULL;
	}
}
node_t *SLLInsertBefore(node_t *node, int data)
{
	node_t *new_node = NULL;
	
	assert(NULL != node);
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = node;
	
	return new_node;
}

node_t *SLLNext(node_t *node)
{
	return node->next;
}

int SLLGetValue(node_t *node)
{
	return node->data;
}

/* ~~~ singly_linked_list exrecise ~~~ */

node_t *RecFlipList(node_t *head)
{
	node_t *new_head = NULL;
	
	assert(NULL != head);
	
	if(NULL == SLLNext(head)) 
    {
        return head;
    }
    else
    {
    	new_head = RecFlipList(SLLNext(head));
    	SLLNext(head)->next = head;
		head->next = NULL;
		return new_head;
    }
}

/* ~~~ Fibonaci ~~~ */

int RecFibonacciIterative(int element_index)
{
	int prev = 0;
	int current = 0;
	int temp = 0;
	
	assert(0 < element_index);
	
	if(2 >= element_index)
	{
		return element_index - 1;
	}
	
	prev = 0;
	current = 1;
	--element_index;
	
	while(1 < element_index)
	{
		temp = current;
		current += prev;
		prev = temp;
		--element_index;
	}
	
	return current;
}

int RecFibonacci(int element_index)
{
	assert(0 <= element_index);

	if(2 >= element_index)
	{
		return element_index - 1;
	}
	else 
	{
		return (RecFibonacci(element_index-1) + RecFibonacci(element_index-2));
	}
}

/* ~~~ String ~~~ */

size_t RecStrLen(const char *str)
{
	assert(NULL != str);

	if('\0' != *str)
	{
		return RecStrLen(str + 1) + 1;
	}
	else
	{
		return 0;
	}
}

int RecStrCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);

	if(('\0' != *str1) && ('\0' != *str2) && 0 == (*str1 - *str2))
	{
		return RecStrCmp(str1 + 1, str2 + 1);
	}
	else
	{
		return (*str1 - *str2);
	}
}

char *RecStrCpy(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	*dest = *src;
	
	if(('\0' != *src))
	{
		RecStrCpy(dest + 1, src + 1);
	}

	return dest;	
}

char *RecStrCat(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	if(('\0' != *dest))
	{
		RecStrCat(dest + 1, src);
	}
	else
	{
		RecStrCpy(dest, src);
	}
	
	return dest;
}

char *RecStrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);

	if('\0' == *haystack)
	{
		return NULL;
	}
	
	if(*haystack != *needle)
	{
		return RecStrStr(haystack + 1, needle);
	}
	
	if(0 == StrnCmp(haystack, needle, RecStrLen(needle)))
	{
		return (char *)haystack;
	}
	
	return RecStrStr(haystack + 1, needle);
}

static int StrnCmp(const char *str1, const char *str2, size_t n)
{
	assert(NULL != str1);
	assert(NULL != str2);

	if(0 == n)
	{
		return 0;
	}
	
	if(('\0' != *str1) && ('\0' != *str2) && 0 == (*str1 - *str2) && (0 != n))
	{
		return StrnCmp(str1 + 1, str2 + 1, n - 1);
	}
	else
	{
		return (*str1 - *str2);
	}
}


