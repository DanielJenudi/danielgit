/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 15/05/2022
File: Calculate
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <stdio.h>/* printf */

#include "avl.h"

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

enum status
{
	SUCCESS = 0,
	FAIL
};

void OverAllTransition();
void ForEachTest();
void RotationTest();

int cmp_func(const void *new_data, const void *tree_data, void *param);
int action_func(void *data, void *param);
int complicate_action_func(void *data, void *param);

int IntComper(int x, int y);
int IsNULL(void *data);

static int PrintAVL(avl_t *avl, int order);
static int PrintFunc(void *data, void *param);

int main()
{
	printf("*\n~~~ RotationTest ~~~\n*\n");
	RotationTest();
	printf("*\n~~~ OverAllTransition ~~~\n*\n");
	OverAllTransition();
	printf("*\n~~~ ForEachTest ~~~\n*\n");
	ForEachTest();

	return 0;
}

void RotationTest()
{
	int a = 10, b = 20, c = 30, d = 40, e = 50, f = 60, g = 70, h = 80, i = 90;
	
	avl_t *avl = AVLCreate(cmp_func, NULL);
	
	printf("\n~~~ Empty AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 1));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 0));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 0));
	
	printf("\n~~~ Insert AVL height check ~~~\n");
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 2));
	
	AVLInsert(avl, &d);
	AVLInsert(avl, &e);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 3));
	
	AVLInsert(avl, &f);
	AVLInsert(avl, &g);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 3));
	
	AVLInsert(avl, &h);
	AVLInsert(avl, &i);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 4));
	
	AVLDestroy(avl);

	avl = AVLCreate(cmp_func, NULL);
	
	printf("\n~~~ Empty AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 1));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 0));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 0));
	
	printf("\n~~~ Remove AVL height check ~~~\n");
	
	AVLInsert(avl, &e);
	AVLInsert(avl, &c);
	AVLInsert(avl, &g);
	AVLInsert(avl, &d);
	AVLInsert(avl, &f);
	AVLInsert(avl, &a);
	AVLInsert(avl, &i);
	AVLInsert(avl, &b);
	AVLInsert(avl, &h);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 4));
	
	AVLRemove(avl, &a);
	AVLRemove(avl, &b);
	AVLRemove(avl, &c);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 3));

	AVLRemove(avl, &h);
	AVLRemove(avl, &i);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 3	));
	
	AVLRemove(avl, &d);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 2	));
	
	AVLRemove(avl, &f);
	AVLRemove(avl, &e);
	
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 1	));
	
	AVLRemove(avl, &g);
	
	printf("\n~~~ Empty AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 1));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 0));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 0));
	
	AVLDestroy(avl);
}

void OverAllTransition()
{
	int a = 10, b = 8, c = 12, d = 9, e = 7, f = 11, g = 13, h = 15, i = 17;
	int find_test = 100, action_param = 10;
	avl_t *avl = AVLCreate(cmp_func, NULL);
	
	printf("\n~~~ Empty AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 1));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 0));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 0));
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	AVLInsert(avl, &d);
	AVLInsert(avl, &e);
	AVLInsert(avl, &f);
	AVLInsert(avl, &g);
	AVLInsert(avl, &h);
	AVLInsert(avl, &i);

	printf("\n~~~ Full AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 0));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 9));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 4));
	
	printf("\n~~~ Find AVL ~~~\n");
	printf("\nAVLFind found: ");
	RUNTEST(IntComper(*(int *)AVLFind(avl, &f), f));
	printf("\nAVLFind not found : ");
	RUNTEST(IsNULL(AVLFind(avl, &find_test)));

	printf("\n~~~ Remove number - %d ~~~\n", h);
	AVLRemove(avl, &h);
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 0));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 8));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 4));
	
	printf("\n~~~ Remove number - %d ~~~\n", i);
	AVLRemove(avl, &i);
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 0));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 7));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 3));
	
	printf("\n~~~ Remove root ~~~\n");
	AVLRemove(avl, &a);
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 0));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 6));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 3));
	
	/*PrintAVL(avl, PRE);*/
	
	AVLForEach(avl, &action_func, &action_param, PRE);
	
	printf("\n~~~ After action add 10 PRE ~~~\n");
	RUNTEST(IntComper(b, 18));
	RUNTEST(IntComper(g, 23));
	RUNTEST(IntComper(d, 19));
	
	AVLForEach(avl, &action_func, &action_param, IN);
	
	printf("\n~~~ After action add 10 IN ~~~\n");
	RUNTEST(IntComper(b, 28));
	RUNTEST(IntComper(g, 33));
	RUNTEST(IntComper(d, 29));
	
	AVLForEach(avl, &action_func, &action_param, POST);
	
	printf("\n~~~ After action add 10 POST ~~~\n");
	RUNTEST(IntComper(b, 38));
	RUNTEST(IntComper(g, 43));
	RUNTEST(IntComper(d, 39));
	
	AVLDestroy(avl);
	
	printf("\n~~~ Only Root Test ~~~\n");
	avl = AVLCreate(cmp_func, NULL);
	printf("\n~~~ Empty AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 1));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 0));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 0));
	
	AVLInsert(avl, &a);
	
	printf("\n~~~ Empty AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 0));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 1));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 1));
	
	AVLRemove(avl, &a);
	
	printf("\n~~~ Empty AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 1));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 0));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 0));
	
	AVLDestroy(avl);
}

void ForEachTest()
{
	int a = 10, b = 8, c = 12, d = 9, e = 7, f = 11, g = 13, h = 15, i = 17;
	int action_param = 10;
	avl_t *avl = AVLCreate(cmp_func, NULL);
	
	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	AVLInsert(avl, &d);
	AVLInsert(avl, &e);
	AVLInsert(avl, &f);
	AVLInsert(avl, &g);
	AVLInsert(avl, &h);
	AVLInsert(avl, &i);

	printf("\n~~~ Full AVL ~~~\n");
	printf("\nAVLIsEmpty : ");
	RUNTEST(IntComper(AVLIsEmpty(avl), 0));
	printf("\nAVLCount : ");
	RUNTEST(IntComper(AVLCount(avl), 9));
	printf("\nAVLHeight : ");
	RUNTEST(IntComper(AVLHeight(avl), 4));
	
	AVLForEach(avl, &complicate_action_func, &action_param, PRE);
	
	printf("\n~~~ After action add 10 PRE ~~~\n");
	RUNTEST(IntComper(a, 10));
	RUNTEST(IntComper(b, 8));
	RUNTEST(IntComper(c, 12));
	RUNTEST(IntComper(d, 9));
	RUNTEST(IntComper(e, 7));
	RUNTEST(IntComper(f, 11));
	RUNTEST(IntComper(g, 13));
	RUNTEST(IntComper(h, 15));
	RUNTEST(IntComper(i, 17));
	
	AVLDestroy(avl);
}

static int PrintAVL(avl_t *avl, int order)
{
	AVLForEach(avl, PrintFunc, NULL, order);
	puts("");
	
	return 0;
}

static int PrintFunc(void *data, void *param)
{
	(void)param;
	printf("%d ",*(int *)data);
	
	return 0;
}

int cmp_func(const void *new_data, const void *tree_data, void *param)
{
	(void)param;
	return *(int *)new_data - *(int *)tree_data;
}

int action_func(void *data, void *param)
{
	*(int *)data += *(int *)param;
	return SUCCESS;
} 

int complicate_action_func(void *data, void *param)
{
	if(*(int *)data != *(int *)param)
	{
		*(int *)data += *(int *)param;
		return SUCCESS;
	}
	return FAIL;
} 

int IsNULL(void *data)
{
	return data == NULL ? 0 : 1;
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}

