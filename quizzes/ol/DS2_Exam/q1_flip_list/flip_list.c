#include <stdio.h>	/* printf */
#include <assert.h> /* assert */

#define RUNTEST(test)                     \
	{                                     \
		if (!test)                        \
		{                                 \
			printf("\x1b[0;34m");         \
			printf("OK!\n\n");            \
			printf("\x1b[0m");            \
		}                                 \
		else                              \
		{                                 \
			printf("\x1b[1;35m");         \
			printf("\nTest Failed!\n\n"); \
			printf("\x1b[0m");            \
		}                                 \
	}

typedef struct Node node_t;

struct Node
{
	node_t *next;
	size_t data;
};

enum
{
	SUCCESS,
	FAIL
};

void FlipListIter();
node_t *FlipIter(node_t *node);

void FlipListReq();
node_t *FlipReq(node_t *node);

void PrintList(node_t *node);

int main()
{
	FlipListIter();
	FlipListReq();

	return 0;
}

void FlipListIter()
{
	node_t a = {0};
	node_t b = {0};
	node_t c = {0};
	node_t d = {0};
	node_t e = {0};
	node_t *head = &a;

	printf("--- Test Flip List Iter ---\n");

	a.data = 1;
	a.next = &b;

	b.data = 2;
	b.next = &c;

	c.data = 3;
	c.next = &d;

	d.data = 4;
	d.next = &e;

	e.data = 5;
	e.next = NULL;

	PrintList(head);
	head = FlipIter(head);
	PrintList(head);
}

node_t *FlipIter(node_t *node)
{
	node_t *prev = NULL;
	node_t *cur = NULL;
	node_t *next = NULL;

	assert(NULL != node);

	cur = node;

	while (NULL != cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	return prev;
}

void FlipListReq()
{
	node_t a = {0};
	node_t b = {0};
	node_t c = {0};
	node_t d = {0};
	node_t e = {0};
	node_t *head = &a;

	printf("\n--- Test Flip List Req ---\n");

	a.data = 1;
	a.next = &b;

	b.data = 2;
	b.next = &c;

	c.data = 3;
	c.next = &d;

	d.data = 4;
	d.next = &e;

	e.data = 5;
	e.next = NULL;

	PrintList(head);
	head = FlipReq(head);
	PrintList(head);
}

node_t *FlipReq(node_t *node)
{
	node_t *new_head = NULL;
	node_t *next = NULL;

	assert(NULL != node);

	if (NULL == node->next)
	{
		return node;
	}

	next = node->next;
	new_head = FlipReq(next);
	next->next = node;
	node->next = NULL;

	return new_head;
}

void PrintList(node_t *node)
{
	while (NULL != node)
	{
		printf("%lu ", node->data);
		node = node->next;
	}

	printf("\n");
}