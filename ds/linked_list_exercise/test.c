#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc, free*/

#include "ex.h"

#define RUNTEST(test) {\
            if (!test)\
            {\
                printf("\x1b[0;34m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;35m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

enum
{
	SUCCESS = 0,
	FAIL
};

void TestFlip();
void TestHasLoop();
void TestFindIntersection();
void PrintList(node_t *head);
int IntComper(int x, int y);

int main()
{
	TestFlip();  
	TestHasLoop();
	TestFindIntersection();
    
    return SUCCESS;
}

void TestFlip()
{
	int a = 0, b = 1, c = 2, d = 3, e = 4;

    node_t *head = (node_t *)malloc(sizeof(node_t));
    node_t *one = (node_t *)malloc(sizeof(node_t));
    node_t *two = (node_t *)malloc(sizeof(node_t));
    node_t *three = (node_t *)malloc(sizeof(node_t));
    node_t *four = (node_t *)malloc(sizeof(node_t));
    
    printf("\n--- TestFlip ---\n");
    
    head->data = &a;
    one->data = &b;
    two->data = &c;
    three->data = &d;
    four->data = &e;
    
    head->next = one;
    one->next = two;
    two->next = three;
    three->next = four;
    four->next = NULL;
    
    PrintList(head);
    head = Flip(head);
    PrintList(head);
    
    free(four->next->next->next->next);
    free(four->next->next->next);
    free(four->next->next);
    free(four->next);
    free(four);
}

void TestHasLoop()
{
	int a = 0, b = 1, c = 2, d = 3, e = 4;

    node_t *head = (node_t *)malloc(sizeof(node_t));
    node_t *one = (node_t *)malloc(sizeof(node_t));
    node_t *two = (node_t *)malloc(sizeof(node_t));
    node_t *three = (node_t *)malloc(sizeof(node_t));
    node_t *four = (node_t *)malloc(sizeof(node_t));
    
    printf("\n--- TestHasLoop ---\n");
    
    head->data = &a;
    one->data = &b;
    two->data = &c;
    three->data = &d;
    four->data = &e;
    
    head->next = one;
    one->next = two;
    two->next = three;
    three->next = four;
    four->next = two;

    RUNTEST(IntComper(HasLoop(head), 1));
    
    free(head);
    free(one);
    free(two);
    free(three);
    free(four);
}

void TestFindIntersection()
{
	int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;

    node_t *head = (node_t *)malloc(sizeof(node_t));
    node_t *one = (node_t *)malloc(sizeof(node_t));
    node_t *two = (node_t *)malloc(sizeof(node_t));
    node_t *three = (node_t *)malloc(sizeof(node_t));
    node_t *four = (node_t *)malloc(sizeof(node_t));
    
    node_t *five = (node_t *)malloc(sizeof(node_t));
    node_t *six = (node_t *)malloc(sizeof(node_t));
    node_t *seven = (node_t *)malloc(sizeof(node_t));
    
    node_t *result = NULL;
    
    printf("\n--- TestFindIntersection ---\n");
    
    head->data = &a;
    one->data = &b;
    two->data = &c;
    three->data = &d;
    four->data = &e;
    
    five->data = &f;
    six->data = &g;
    seven->data = &h;
    
    head->next = one;
    one->next = two;
    two->next = three;
    three->next = four;
    four->next = NULL;
    
    five->next = six;
    six->next = seven;
    seven->next = three;

	result = FindIntersection(head, five);
	RUNTEST(IntComper(*(int *)result->data, *(int *)three->data));


	free(head);
    free(one);
    free(two);
    free(three);
	free(four);
    
    free(five);
    free(six);
    free(seven);
}

void PrintList(node_t *head)
{
    node_t *runner = head;
    
    printf("\n");
    
    while (NULL != runner)
    {
        printf("%d ", *(int *)runner->data);
        runner = runner->next;
    }
    printf("\n");
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}




























