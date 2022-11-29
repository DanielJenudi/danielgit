/*******************************************************************************
 Author: daniel jenudi 
 Date: 28/04/2022
 Reviewed By: noam
*******************************************************************************/
#include <stdio.h> /* for printf */

#include "bst.h"
#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

int CreateDestroy(void);
int GetDataIsEqual(void);
int NextPrevCount(void);
int EndBegin(void);
int RemoveCount(void);
int RemoveRoot(void);
int FIND(void);
int ForEach(void);

int TestInt(const char *str, int expected, int result);
int Sort(const void *new_data, const void *list_data, void *param);
 int AddNum(void *data, void *parameter);
 
int main(void)
{
	printf("-------Test for Create Destroy -------\n");
	RUNTEST(CreateDestroy());
	printf("-------Test for GetData IsEqual -------\n");
	RUNTEST(GetDataIsEqual());
	printf("-------Test for Next Prev Count -------\n");
	RUNTEST(NextPrevCount());
	printf("-------Test for End Begin -------\n");
	RUNTEST(EndBegin());
	printf("-------Test for Remove -------\n");
	RUNTEST(RemoveCount());
	printf("-------Test for Remove Root -------\n");
	RUNTEST(RemoveRoot());
	printf("-------Test for FIND -------\n");
	RUNTEST(FIND());
	printf("-------Test for ForEach -------\n");
	RUNTEST(ForEach());
	return 0;
}

int CreateDestroy(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50};
	bst_cmp_func_t cmp_func = Sort;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("2IsEmpty", 1 , BSTIsEmpty(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("3Size", 0 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTInsert(bst, &num[30]);
	status += TestInt("4AfterInsert", 0 , BSTIsEmpty(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTInsert(bst, &num[40]);
	status += TestInt("5AfterInsert", 0 , BSTIsEmpty(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTInsert(bst, &num[50]);
	
	
	BSTDestroy(bst);
	return result;
}

int GetDataIsEqual(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50};
	bst_cmp_func_t cmp_func = Sort;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	bst_iter_t root = NULL;
	bst_iter_t node1 = NULL;
	bst_iter_t node2 = NULL;
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;

	root = BSTInsert(bst, &num[30]);
	status += TestInt("Size", 1 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	node1 = BSTInsert(bst, &num[40]);
	status += TestInt("Size", 2 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	node2 = BSTInsert(bst, &num[50]);
	status += TestInt("Size", 3 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("1GetData", 30 , *(int *)BSTGetData(root));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("2GetData", 40 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("3GetData", 50 , *(int *)BSTGetData(node2));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("4IsIterEqual", 0 , BSTIterIsEqual(node2, node1));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("5IsIterEqual", 0 , BSTIterIsEqual(root, node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	node2=node1;
	status += TestInt("6IsIterEqual", 1 , BSTIterIsEqual(node2, node1));
	result += status;
	RUNTEST(status);
	status = 0;
	

	BSTDestroy(bst);
	return result;
}

int NextPrevCount(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50,51,52};
	bst_cmp_func_t cmp_func = Sort;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	bst_iter_t node1 = NULL;
	bst_iter_t node2 = NULL;
	bst_iter_t node3 = NULL;
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;

	BSTInsert(bst, &num[30]);
	node1 = BSTInsert(bst, &num[40]);
	node2 = BSTInsert(bst, &num[50]);
	BSTInsert(bst, &num[52]);
	BSTInsert(bst, &num[35]);
	BSTInsert(bst, &num[10]);
	BSTInsert(bst, &num[15]);
	BSTInsert(bst, &num[12]);
	BSTInsert(bst, &num[13]);
	BSTInsert(bst, &num[14]);
	status += TestInt("Size", 10 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTInsert(bst, &num[11]);
	BSTInsert(bst, &num[5]);
	BSTInsert(bst, &num[3]);
	BSTInsert(bst, &num[4]);
	BSTInsert(bst, &num[1]);
	node3 = BSTInsert(bst, &num[2]);
	status += TestInt("Size", 16 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("IsIterEqual", 0 , BSTIterIsEqual(node2, node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	node1 = BSTNext(node1);
	status += TestInt("IsIterEqual", 1 , BSTIterIsEqual(node2, node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("1GetData", 50 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	node1 = BSTNext(node1);
	status += TestInt("2GetData", 52 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	node1 = BSTPrev(node1);
	status += TestInt("3GetData", 50 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("4GetData", 2 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTNext(node3);
	status += TestInt("5GetData", 3 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTPrev(node3);
	status += TestInt("GetData", 2 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTPrev(node3);
	status += TestInt("GetData", 1 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	
	node3 = BSTNext(node3);
	status += TestInt("GetData", 2 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTNext(node3);
	status += TestInt("GetData", 3 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTNext(node3);
	status += TestInt("GetData", 4 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTNext(node3);
	status += TestInt("GetData", 5 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTNext(node3);
	status += TestInt("GetData", 10 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	node3 = BSTNext(node3);
	status += TestInt("GetData", 11 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	
	node1 = BSTPrev(node1);
	status += TestInt("GetData", 40 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	node1 = BSTPrev(node1);
	status += TestInt("GetData", 35 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	node1 = BSTPrev(node1);
	status += TestInt("GetData", 30 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	node1 = BSTPrev(node1);
	status += TestInt("GetData", 15 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	node1 = BSTNext(node1);
	node1 = BSTNext(node1);
	status += TestInt("LastGetData", 35 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("Size", 16 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(BSTBegin(bst));
	status += TestInt("Size", 15 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	status += TestInt("Size", 12 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	BSTRemove(BSTBegin(bst));
	status += TestInt("Size", 1 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(BSTBegin(bst));
	status += TestInt("Size", 0 , BSTCount(bst));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTDestroy(bst);
	return result;
}

int EndBegin(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50,51,52};
	bst_cmp_func_t cmp_func = Sort;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	bst_iter_t root = NULL;
	bst_iter_t node1 = NULL;
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;

	root = BSTInsert(bst, &num[30]);
	BSTInsert(bst, &num[40]);
	BSTInsert(bst, &num[50]);
	
	node1 = BSTNext(root);
	node1 = BSTNext(node1);
	node1 = BSTNext(node1);
	
	status += TestInt("IsIterEqual", 1 , BSTIterIsEqual(BSTEnd(bst), node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("BSTBegin", 30 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTInsert(bst, &num[52]);
	BSTInsert(bst, &num[35]);
	BSTInsert(bst, &num[10]);
	
	status += TestInt("BSTBegin", 10 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTInsert(bst, &num[15]);
	BSTInsert(bst, &num[12]);
	BSTInsert(bst, &num[13]);
	BSTInsert(bst, &num[14]);
	BSTInsert(bst, &num[11]);
	BSTInsert(bst, &num[5]);
	
	status += TestInt("BSTBegin", 5 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("IsIterEqual", 1 , BSTIterIsEqual(BSTEnd(bst), node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTInsert(bst, &num[3]);
	
	status += TestInt("BSTBegin", 3 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTInsert(bst, &num[4]);
	
	status += TestInt("BSTBegin", 3 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTInsert(bst, &num[1]);
	
	status += TestInt("BSTBegin", 1 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTInsert(bst, &num[2]);
	
	status += TestInt("IsIterEqual", 1 , BSTIterIsEqual(BSTEnd(bst), node1));
	result += status;
	RUNTEST(status);
	status = 0;

	
	status += TestInt("BSTBegin", 1 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	

	BSTDestroy(bst);
	return result;
}

int RemoveCount(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50,51,52};
	bst_cmp_func_t cmp_func = Sort;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	bst_iter_t node1 = NULL;
	bst_iter_t node2 = NULL;
	bst_iter_t node3 = NULL;
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;

	BSTInsert(bst, &num[30]);
	node1 = BSTInsert(bst, &num[40]);
	BSTInsert(bst, &num[50]);
	BSTInsert(bst, &num[52]);
	BSTInsert(bst, &num[31]);
	node2 = BSTInsert(bst, &num[33]);
	BSTInsert(bst, &num[35]);
	node3 = BSTInsert(bst, &num[34]);
	BSTInsert(bst, &num[10]);
	BSTInsert(bst, &num[15]);
	BSTInsert(bst, &num[12]);
	BSTInsert(bst, &num[13]);
	BSTInsert(bst, &num[14]);
	BSTInsert(bst, &num[11]);
	BSTInsert(bst, &num[18]);
	BSTInsert(bst, &num[17]);
	BSTInsert(bst, &num[20]);
	BSTInsert(bst, &num[19]);
	BSTInsert(bst, &num[5]);
	BSTInsert(bst, &num[3]);
	BSTInsert(bst, &num[4]);
	BSTInsert(bst, &num[1]);
	BSTInsert(bst, &num[2]);
	
	printf("Finish build BST\n");
	printf("~~~~~~~~~~Remove Leef~~~~~~~~~~\n");
	
	status += TestInt("BSTBegin", 1 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("BSTNextBSTBegin", 2 , *(int *)BSTGetData(BSTNext(BSTBegin(bst))));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTRemove(BSTNext(BSTBegin(bst)));
	BSTRemove(BSTBegin(bst));
	
	status += TestInt("BSTBegin", 3 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTNextBSTBegin", 4 , *(int *)BSTGetData(BSTNext(BSTBegin(bst))));
	result += status;
	RUNTEST(status);
	status = 0;
	
	printf("~~~~~~~~~~Remove one child~~~~~~~~~~\n");
	
	BSTRemove(BSTBegin(bst));
	
	status += TestInt("BSTBegin", 4 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTNextBSTBegin", 5 , *(int *)BSTGetData(BSTNext(BSTBegin(bst))));
	result += status;
	RUNTEST(status);
	status = 0;
	
	printf("~~~~~~~~~~Remove two children~~~~~~~~~~\n");
	status += TestInt("BSTGetData", 33 , *(int *)BSTGetData(node2));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTGetDataNext", 31 , *(int *)BSTGetData(BSTPrev(node2)));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTGetDataNext", 34 , *(int *)BSTGetData(BSTNext(node2)));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTGetDataNextNext", 35 , *(int *)BSTGetData(BSTNext(BSTNext(node2))));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTGetDataNextNext", 40 , *(int *)BSTGetData(BSTNext(BSTNext(BSTNext(node2)))));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTGetData", 40 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(node1);
	status += TestInt("BSTGetData", 35 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	status += TestInt("BSTGetDataNextNext", 50 , *(int *)BSTGetData(BSTNext(BSTNext(BSTNext(node2)))));
	result += status;
	RUNTEST(status);
	status = 0;
	
	printf("~~~~~~~~~~Remove ~~~~~~~~~~\n");
	
	status += TestInt("BSTGetDataNext", 33 , *(int *)BSTGetData(node2));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(node2);
	status += TestInt("BSTGetDataNext", 34 , *(int *)BSTGetData(node3));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(node3);
	
	status += TestInt("BSTGetData", 35 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	BSTRemove(node1);
	status += TestInt("BSTGetData", 31 , *(int *)BSTGetData(node1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	
	BSTDestroy(bst);
	return result;
}

int RemoveRoot(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50,51,52};
	bst_cmp_func_t cmp_func = Sort;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	bst_iter_t root = NULL;
	
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;

	root = BSTInsert(bst, &num[30]);
	BSTInsert(bst, &num[40]);
	BSTInsert(bst, &num[50]);
	BSTInsert(bst, &num[52]);
	BSTInsert(bst, &num[31]);
	BSTInsert(bst, &num[33]);
	BSTInsert(bst, &num[35]);
	BSTInsert(bst, &num[34]);
	BSTInsert(bst, &num[10]);
	BSTInsert(bst, &num[15]);
	BSTInsert(bst, &num[12]);
	BSTInsert(bst, &num[13]);
	BSTInsert(bst, &num[14]);
	BSTInsert(bst, &num[11]);
	BSTInsert(bst, &num[18]);
	BSTInsert(bst, &num[17]);
	BSTInsert(bst, &num[20]);
	BSTInsert(bst, &num[19]);
	BSTInsert(bst, &num[5]);
	BSTInsert(bst, &num[3]);
	BSTInsert(bst, &num[4]);
	BSTInsert(bst, &num[1]);
	BSTInsert(bst, &num[2]);
	
	printf("Finish build BST\n");
	
	status += TestInt("BSTGetData", 30 , *(int *)BSTGetData(root));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTRemove(root);
	
	status += TestInt("BSTGetData", 20 , *(int *)BSTGetData(root));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTDestroy(bst);
	
	return result;
}

int FIND(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50,51,52};
	bst_cmp_func_t cmp_func = Sort;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	bst_iter_t iter1 = NULL;
	bst_iter_t from = NULL;
	bst_iter_t to = NULL;
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;

	BSTInsert(bst, &num[30]);
	BSTInsert(bst, &num[40]);
	BSTInsert(bst, &num[50]);
	BSTInsert(bst, &num[52]);
	BSTInsert(bst, &num[31]);
	BSTInsert(bst, &num[33]);
	BSTInsert(bst, &num[35]);
	BSTInsert(bst, &num[34]);
	from = BSTInsert(bst, &num[10]);
	BSTInsert(bst, &num[15]);
	BSTInsert(bst, &num[12]);
	BSTInsert(bst, &num[13]);
	BSTInsert(bst, &num[14]);
	BSTInsert(bst, &num[11]);
	BSTInsert(bst, &num[18]);
	BSTInsert(bst, &num[17]);
	to = BSTInsert(bst, &num[20]);
	BSTInsert(bst, &num[19]);
	BSTInsert(bst, &num[5]);
	BSTInsert(bst, &num[3]);
	BSTInsert(bst, &num[4]);
	BSTInsert(bst, &num[1]);
	BSTInsert(bst, &num[2]);
	
	printf("Finish build BST\n");
	iter1 = BSTFind(bst, from,  to, &num[12]);
	status += TestInt("BSTGetData", 12 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, from,  to, &num[30]);
	
	status += TestInt("BSTGetData", 20 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, from,  to, &num[19]);
	
	status += TestInt("BSTGetData", 19 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, from,  to, &num[10]);
	
	status += TestInt("BSTGetData", 10 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, BSTBegin(bst),  to, &num[1]);
	
	status += TestInt("BSTGetData", 1 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, BSTBegin(bst),  to, &num[18]);
	
	status += TestInt("BSTGetData", 18 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, BSTBegin(bst),  to, &num[50]);
	
	status += TestInt("BSTGetData", 20 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, BSTBegin(bst), BSTPrev(BSTEnd(bst)), &num[0]);
	
	status += TestInt("BSTGetData", 52 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	iter1 = BSTFind(bst, BSTBegin(bst), BSTPrev(BSTEnd(bst)), &num[40]);
	
	status += TestInt("BSTGetData", 40 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTDestroy(bst);
	
	return result;
}

int ForEach(void)
{
	int result = 0;
	int status = 0;
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
					24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,
					44,45,46,47,48,49,50,51,52};
					
	int param = 2;
	bst_cmp_func_t cmp_func = Sort;
	bst_action_func_t action_func = AddNum;
	bst_t *bst = BSTCreate(cmp_func, &num[1]);
	bst_iter_t iter1 = NULL;
	bst_iter_t to = NULL;
	
	printf("Create\n");
	status += (NULL == bst);
	result += status;
	RUNTEST(status);
	status = 0;

	BSTInsert(bst, &num[30]);
	BSTInsert(bst, &num[40]);
	BSTInsert(bst, &num[50]);
	BSTInsert(bst, &num[52]);
	BSTInsert(bst, &num[31]);
	BSTInsert(bst, &num[33]);
	BSTInsert(bst, &num[35]);
	BSTInsert(bst, &num[34]);
	BSTInsert(bst, &num[10]);
	BSTInsert(bst, &num[15]);
	BSTInsert(bst, &num[12]);
	BSTInsert(bst, &num[13]);
	BSTInsert(bst, &num[14]);
	BSTInsert(bst, &num[11]);
	BSTInsert(bst, &num[18]);
	BSTInsert(bst, &num[17]);
	to = BSTInsert(bst, &num[20]);
	BSTInsert(bst, &num[19]);
	BSTInsert(bst, &num[5]);
	BSTInsert(bst, &num[3]);
	BSTInsert(bst, &num[4]);
	BSTInsert(bst, &num[1]);
	BSTInsert(bst, &num[2]);
	
	printf("Finish build BST\n");
	
	iter1 = BSTBegin(bst);
	status += TestInt("BSTGetData", 1 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	iter1 = BSTNext(iter1);
	status += TestInt("BSTGetData", 2 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	iter1 = BSTNext(iter1);
	status += TestInt("BSTGetData", 3 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	iter1 = BSTNext(iter1);
	iter1 = BSTNext(iter1);
	iter1 = BSTNext(iter1);
	status += TestInt("BSTGetData", 10 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("BSTForeach", 0 , BSTForeach(BSTBegin(bst), to, action_func, &param));
	result += status;
	RUNTEST(status);
	status = 0;
	iter1 = BSTBegin(bst);
	status += TestInt("BSTGetData", 3 , *(int *)BSTGetData(BSTBegin(bst)));
	result += status;
	RUNTEST(status);
	status = 0;
	iter1 = BSTNext(iter1);
	status += TestInt("BSTGetData", 4 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	iter1 = BSTNext(iter1);
	status += TestInt("BSTGetData", 5 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	iter1 = BSTNext(iter1);
	iter1 = BSTNext(iter1);
	iter1 = BSTNext(iter1);
	status += TestInt("BSTGetData", 12 , *(int *)BSTGetData(iter1));
	result += status;
	RUNTEST(status);
	status = 0;
	
	status += TestInt("BSTGetData", 20 , *(int *)BSTGetData(to));
	result += status;
	RUNTEST(status);
	status = 0;
	
	BSTDestroy(bst);
	return result;
}

int TestInt(const char *str, int expected, int result)
{
	printf("%s\n" , str);
	return !(expected == result);
}


int Sort(const void *new_data, const void *list_data, void *param)
{
	(void) param ;
	if (*(int *)new_data < *(int *)list_data)
	{
		return -1;
	}
	if (*(int *)new_data > *(int *)list_data)
	{
		return 1 ;
	}
	return 0; 
}
int AddNum(void *data, void *parameter)
{
	*(int *)data += *(int *)parameter;
	return 0;
} 

