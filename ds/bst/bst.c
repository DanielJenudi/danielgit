/*******************************************************************************
 Author: daniel jenudi 
 Date: 28/04/2022
 Reviewed By: noam
*******************************************************************************/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "bst.h"

#define NO_LEFT_CHILD (NULL == left_child)
#define NO_RIGHT_CHILD (NULL == right_child)
#define NO_CHILDREN (NO_LEFT_CHILD && NO_RIGHT_CHILD)
#define TWO_CHILDREN (!NO_LEFT_CHILD && !NO_RIGHT_CHILD)

enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN
};

enum
{
	FALSE = 0,
	SUCCESS = 0,
	TRUE = 1,
	FAIL = 1,
	PREV = LEFT,
	NEXT = RIGHT
};

typedef struct bst_node bst_node_t;

struct bst_node
{
	void *data;
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILDREN];
};

struct bst
{
	bst_node_t dummy_root;
	bst_cmp_func_t cmp; 
	void *param;
};

static bst_iter_t InitIter();
static bst_iter_t Move(bst_iter_t iter, size_t direction);
static bst_iter_t NearestGrandChild(bst_iter_t iter, size_t direction);
static bst_iter_t NearestGrandFather(bst_iter_t iter, size_t direction);
static bst_t *InitBts(bst_t *bst, bst_cmp_func_t cmp, void *param);
static bst_iter_t AddNode(bst_node_t *perent, size_t direction, void *data);

static int FindDirection(bst_iter_t iter);
static void FreeTwoChildren(bst_iter_t iter);
static void FreeOneChild(bst_iter_t iter, int direction);
void FreeLeaf(bst_iter_t iter);

static bst_iter_t InitIter()
{
	return NULL;
}

bst_t *BSTCreate(bst_cmp_func_t cmp, void *param)
{
	bst_t *bst = NULL;

	assert(NULL != cmp);
	
	bst = (bst_t *)malloc(sizeof(bst_t));
	if(NULL == bst)
	{
		return NULL;
	}
	
	return InitBts(bst, cmp, param);
}

static bst_t *InitBts(bst_t *bst, bst_cmp_func_t cmp, void *param)
{
	bst_node_t *node = NULL;

	assert(NULL != bst);
	assert(NULL != cmp);
		
	node = &bst->dummy_root;
		
	/*dummy root node init*/
	node->data = NULL;
	node->parent = NULL;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;

	/*bts init*/
	bst->cmp = cmp;
	bst->param = param;
	
	return bst;
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t perent = InitIter();
	int next_child = LEFT;
	bst_cmp_func_t cmp = NULL;
	void *param = NULL;
	
	assert(NULL != bst);
	assert(BSTIterIsEqual(BSTFind(bst, BSTBegin(bst), BSTEnd(bst), data),
                          BSTEnd(bst)));
	
	param = bst->param;
	cmp = bst->cmp;
	perent = &bst->dummy_root;
	
	while(NULL != perent->children[next_child])
	{
		perent = perent->children[next_child];
		next_child = cmp(data, BSTGetData(perent), param);
		next_child =  (0 < next_child) ? RIGHT : LEFT;
	}
	
	return AddNode(perent, next_child, data);
}

void BSTDestroy(bst_t *bst)
{
	assert(NULL != bst);
	
	while (FALSE == BSTIsEmpty(bst))
	{
		BSTRemove(BSTBegin(bst));
	}
	
	free(bst);
	bst = NULL;
}

void BSTRemove(bst_iter_t iter)
{
	bst_iter_t right_child = InitIter();
	bst_iter_t left_child = InitIter();
	
	assert(InitIter() != iter);
	
	right_child = iter->children[RIGHT];
	left_child = iter->children[LEFT];
    
    if (NO_CHILDREN)
    {
        FreeLeaf(iter);
    }
    else if (TWO_CHILDREN)
    {
        FreeTwoChildren(iter);
    }
    else if (NO_RIGHT_CHILD)
    {
        FreeOneChild(iter, LEFT);
    }
    else
    {
        FreeOneChild(iter, RIGHT);
    }
}

static void FreeTwoChildren(bst_iter_t iter)
{
	int direction = LEFT;
	bst_iter_t new_iter_parent = InitIter();
	bst_iter_t new_iter = InitIter();
	bst_iter_t new_iter_left = InitIter();
	
	assert(InitIter() != iter);
	
	new_iter = NearestGrandChild(iter, LEFT);
	new_iter_parent = new_iter->parent;
	new_iter_left = new_iter->children[LEFT];
	
	iter->data = new_iter->data;
	
	direction = FindDirection(new_iter);
	new_iter_parent->children[direction] = new_iter_left;
	
	if (NULL != new_iter_left)
	{
		new_iter_left->parent = new_iter_parent;
	}
	
	free(new_iter);
	new_iter = NULL;
}

static void FreeOneChild(bst_iter_t iter, int direction)
{
	bst_iter_t parent = InitIter();
	bst_iter_t child = InitIter();
	
	assert(NULL != iter);
	
	parent = iter->parent;	
	child = iter->children[direction];
	
	parent->children[FindDirection(iter)] = child;
	child->parent = parent;

	free(iter);
	iter = NULL;
}

void FreeLeaf(bst_iter_t iter)
{
	bst_iter_t parent = InitIter();

	assert(NULL != iter);
	
	parent = iter->parent;	
	parent->children[FindDirection(iter)] = NULL;
	
	free(iter);
	iter = NULL;
}

static int FindDirection(bst_iter_t iter)
{
	bst_iter_t parent = InitIter();

	assert(NULL != iter);
	
	parent = iter->parent;
	
	return BSTIterIsEqual(parent->children[RIGHT], iter);
}


static bst_iter_t AddNode(bst_node_t *perent, size_t direction, void *data)
{
	bst_node_t *new_node = NULL;
	
	assert(NULL != perent);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if(NULL == new_node)
	{
		return InitIter();
	}
	
	new_node->data = data;
	new_node->parent = perent;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	perent->children[direction] = new_node;
	
	return new_node;
}

bst_iter_t BSTBegin(bst_t *bst)
{
	bst_iter_t runner = NULL;
	
	assert(NULL != bst);
	
	runner = (bst_iter_t)&bst->dummy_root;
	
	while(NULL != runner->children[LEFT])
	{
		runner = runner->children[LEFT];
	}
	
	return runner;
}

bst_iter_t BSTEnd(bst_t *bst)
{
	assert(NULL != bst);
	return (bst_iter_t)&bst->dummy_root;
}

void *BSTGetData(bst_iter_t iter)
{
	assert(InitIter() != iter);
	return iter->data;
}

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return (iter1 == iter2);
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	assert(InitIter() != iter);
		
	return Move(iter, NEXT);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{	
	assert(InitIter() != iter);
		
	return Move(iter, PREV);
}

static bst_iter_t Move(bst_iter_t iter, size_t direction)
{	
	assert(InitIter() != iter);
	
	if(NULL != iter->children[direction])
	{	
		return NearestGrandChild(iter, direction);
	}
	else
	{
		return NearestGrandFather(iter, direction);
	}
}

static bst_iter_t NearestGrandChild(bst_iter_t iter, size_t direction)
{
	size_t opposite_direction = (direction) ? LEFT : RIGHT;
	
	assert(InitIter() != iter);
	assert(NULL != iter->children[direction]);
	
	iter = iter->children[direction];
	while(NULL != iter->children[opposite_direction])
	{
		iter = iter->children[opposite_direction];
	}
	
	return iter;
}

static bst_iter_t NearestGrandFather(bst_iter_t iter, size_t direction)
{
	bst_iter_t perent = InitIter();
	
	assert(InitIter() != iter);
	
	perent = iter->parent;
	
	while(BSTIterIsEqual(perent->children[direction], iter) &&
		  NULL != perent->parent)
	{
		iter = perent;
		perent = iter->parent;
	}
	
	return perent;
}

size_t BSTCount(const bst_t *bst)
{
	bst_iter_t runner = InitIter();
	bst_iter_t end = InitIter();
	size_t count = 0;
	
	assert(NULL != (bst_t *)bst);
	
	end = BSTEnd((bst_t *)bst);
	runner = BSTBegin((bst_t *)bst);
	
	while(!BSTIterIsEqual(runner, end))
	{
		++count;
		runner = BSTNext(runner);
	}
	
	return count;
}

int BSTIsEmpty(const bst_t *bst)
{
	return BSTBegin((bst_t *)bst) == BSTEnd((bst_t *)bst);
}

bst_iter_t BSTFind(bst_t *bst, bst_iter_t from, bst_iter_t to, void *data)
{
	assert(InitIter() != from);
	assert(InitIter() != to);
	assert(NULL != bst);

	while(!BSTIterIsEqual(from, to) &&
		  0 != bst->cmp(data, BSTGetData(from), bst->param))
	{
		from = BSTNext(from);	
	}
	
	return from;
}

int BSTForeach(bst_iter_t from, bst_iter_t to, bst_action_func_t act_func, void *param)
{
	int result = SUCCESS;
	
	assert(InitIter() != from);
	assert(InitIter() != to);
	assert(NULL != act_func);

	while(!BSTIterIsEqual(from, to) && SUCCESS == result)
	{
		result = act_func(BSTGetData(from), param);
		from = BSTNext(from);	
	}

	return result;	
}




