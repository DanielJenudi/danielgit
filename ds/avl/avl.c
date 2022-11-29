/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Ran
Date: 15/05/2022
File: Calculate
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include <stdio.h>


#include "avl.h"

#define CMP_CHILD_DIRECTION(X) (X > 0 ? 1 : 0) 
#define MAX2(x,y) ((x) > (y) ? (x) : (y))
#define FAMILY_RELATION(x,y) ((x->children[LEFT]) == (y) ? LEFT : RIGHT)
#define ORDER_TYPE_NUM 3

#define ROOT (avl->root)

typedef struct avl_node node_t;
typedef int (*ActionLUT_t)(node_t *node, 
						   avl_action_func_t act_func, void *param);

enum status
{
	SUCCESS = 0,
	FAIL
};

enum children
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
};

struct avl_node
{
	node_t *children[NUM_OF_CHILDREN];
	void *data;
	size_t height;
};
	
struct avl
{
	node_t *root;
	avl_cmp_func_t cmp; 
	void *param;
};

/* Other static functions */

static void DestroyNodes(node_t *node);
static void SwapData(node_t *node1, node_t *node2);
static void InitNewNode(node_t *new_node, void *data);
static void InsertNode(avl_t *avl, node_t *tree_node, node_t *new_node);
static size_t CountNouds(node_t *node);
static void *Search(const avl_t *avl, node_t *node, const void *to_search);

/* AVLRotation */

static size_t ChildHeight(node_t *node, int direction);

static void RotationCheck(node_t *node);
static void HeavyLeft(node_t *node);
static void HeavyRight(node_t *node);

static void RotationLL(node_t *parent, node_t *child);
static void RotationRR(node_t *parent, node_t *child);
static void RotationLR(node_t *parent, node_t *child);
static void RotationRL(node_t *parent, node_t *child);

/* AVLRemove */

static void ReplaceGrandChild(node_t *to_remove, node_t *parent,
 							  node_t *child, int direction);
static void FindNode(avl_t *avl, node_t *node, node_t *parent, 
					 const void *to_search);
static void FindReplace(node_t *to_remove, node_t *parent, avl_t *avl);
static void SetHeight(node_t *node);

/* Action LUT functions*/

static int AVLActionPostOrder(node_t *node, 
							  avl_action_func_t act_func, void *param);
static int AVLActionInOrder(node_t *node, 
							avl_action_func_t act_func, void *param);
static int AVLActionPreOrder(node_t *node, 
							 avl_action_func_t act_func, void *param);

static void RecPrintAscending(node_t *root);
static void RecLevel(node_t *node, int height, int level);
static void RecPrint(node_t *root, int level);



/* LUT */

ActionLUT_t g_actionLUT[ORDER_TYPE_NUM] = 
	{&AVLActionPreOrder, &AVLActionInOrder, &AVLActionPostOrder};

/* AVLCreate */

avl_t *AVLCreate(avl_cmp_func_t cmp, void *param)
{
	avl_t *avl = NULL;
	
	assert(NULL != cmp);
	
	avl = (avl_t *)malloc(sizeof(avl_t));
	if(NULL == avl)
	{
		return 0;
	}	
	
	/*init avl*/
	avl->root = NULL;
	avl->cmp = cmp;
	avl->param = param;
	
	return avl;
}

/* AVLDestroy */

void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	DestroyNodes(avl->root);	

	free(avl);
	avl = NULL;
}

static void DestroyNodes(node_t *node)
{
	if (NULL != node)
    {
        DestroyNodes(node->children[LEFT]);
        DestroyNodes(node->children[RIGHT]);
        
       	free(node);
       	node = NULL;
    }
}

/* AVLIsEmpty */

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == avl->root);
}

/* AVLHeight */

size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);
	
	if(!AVLIsEmpty(avl))
	{
		return avl->root->height;
	}
	else
	{
		return 0;
	}
}

/* AVLInsert */

int AVLInsert(avl_t *avl, void *new_data)
{
	node_t *new_node = NULL;
	
	assert(NULL != avl);
	assert(NULL == AVLFind(avl, new_data));
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		return FAIL;
	}
	
	InitNewNode(new_node, new_data);
	
	if(!AVLIsEmpty(avl))
	{
		InsertNode(avl, avl->root, new_node);
	}
	else
	{
		avl->root = new_node;
	}
	
	return SUCCESS;
}

static void InitNewNode(node_t *new_node, void *data)
{
	assert(NULL != new_node);

	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->data = data;
	new_node->height = 1;
}

static void InsertNode(avl_t *avl, node_t *tree_node, node_t *new_node)
{
	int cmp_result = 0;
	
	assert(NULL != new_node);
	assert(NULL != tree_node);
	assert(NULL != avl);
	
	cmp_result = (*avl->cmp)(new_node->data, tree_node->data, avl->param);
	cmp_result = CMP_CHILD_DIRECTION(cmp_result);
	
	if(NULL == tree_node->children[cmp_result])
	{
		tree_node->children[cmp_result] = new_node;
		SetHeight(tree_node);
		RotationCheck(tree_node);
	}
	else
	{
		InsertNode(avl, tree_node->children[cmp_result], new_node);
		SetHeight(tree_node);
		RotationCheck(tree_node);
	}
}

/* AVLRemove*/

void AVLRemove(avl_t *avl, const void *to_remove)
{
	assert(NULL != avl);
	assert(NULL != to_remove);
	
	FindNode(avl, avl->root, avl->root, to_remove);	
}

static void FindNode(avl_t *avl, node_t *node, node_t *parent, 
					   const void *to_search)
{
	int cmp_result = 0;

	assert(NULL != avl);
	assert(NULL != node);

	if(to_search == node->data)
	{
		FindReplace(node, parent, avl);
	}
	else
	{
		cmp_result = (*avl->cmp)(to_search, node->data, avl->param);
		cmp_result = CMP_CHILD_DIRECTION(cmp_result);
	
		if(NULL != node->children[cmp_result])
		{
			FindNode(avl, node->children[cmp_result], node, to_search);
			SetHeight(node);
			RotationCheck(node);
		}
	}
}

static void FindReplace(node_t *to_remove, node_t *parent, avl_t *avl)
{
	assert(NULL != avl);
	assert(NULL != to_remove);
	assert(NULL != parent);
	
	if(NULL != to_remove->children[LEFT])
	{
		ReplaceGrandChild(to_remove, to_remove, to_remove->children[LEFT], 
						  RIGHT);			 
		SetHeight(to_remove);	
		RotationCheck(to_remove);
	}
	else if(NULL != to_remove->children[RIGHT])
	{
		ReplaceGrandChild(to_remove, to_remove, to_remove->children[RIGHT], 
						  LEFT);
		SetHeight(to_remove);	
		RotationCheck(to_remove);	
	}
	else
	{
		avl->root = (avl->root == to_remove) ? NULL : avl->root; 
		parent->children[FAMILY_RELATION(parent, to_remove)] = NULL;
		free(to_remove);
		to_remove = NULL;
	}
}

static void ReplaceGrandChild(node_t *to_remove, node_t *parent, 
							  node_t *child, int direction)
{
	int family_relation = 0;
	
	assert(NULL != child);
	assert(NULL != to_remove);
	assert(NULL != parent);
	
	if(NULL != child->children[direction])
	{
		ReplaceGrandChild(to_remove, child, child->children[direction], 
						  direction);
		SetHeight(child);
		RotationCheck(child);				 
	}
	else
	{
		to_remove->data = child->data;
		family_relation = FAMILY_RELATION(parent, child);
		parent->children[family_relation] = child->children[!direction];
	
		free(child);
		child = NULL;
	}
}

static void SetHeight(node_t *node)
{	
	assert(NULL != node);

	if(NULL != node->children[LEFT] && NULL != node->children[RIGHT])
	{
		node->height = MAX2(node->children[RIGHT]->height + 1, 
							node->children[LEFT]->height + 1);
	}
	else if(NULL != node->children[RIGHT])
	{
		node->height = node->children[RIGHT]->height + 1;
	}
	else if(NULL != node->children[LEFT])
	{
		node->height = node->children[LEFT]->height + 1;
	}
	else
	{
		node->height = 1;
	}
}

/* Rotations */

static void RotationCheck(node_t *node)
{
	size_t left_height = 0;
	size_t right_height = 0;	
	
	assert(NULL != node);
	
	left_height = ChildHeight(node, LEFT);
	right_height = ChildHeight(node, RIGHT);
	
	if(left_height > (right_height + 1))
	{
		HeavyLeft(node);
	}
	else if(right_height > (left_height + 1))
	{
		HeavyRight(node);
	}
}

static size_t ChildHeight(node_t *node, int direction)
{
	assert(NULL != node);
	
	if(node->children[direction] != NULL)
	{
		return node->children[direction]->height;
	}
	else
	{
		return 0;
	}
}

static void HeavyLeft(node_t *node)
{
	node_t *child = NULL;
	
	assert(NULL != node);
	
	child = node->children[LEFT];
	
	if(NULL == child->children[LEFT])
	{
		RotationLR(node, child);
	}
	else
	{
		RotationLL(node, child);
	}
}

static void HeavyRight(node_t *node)
{
	node_t *child = NULL;
	
	assert(NULL != node);
	
	child = node->children[RIGHT];
	
	if(NULL == child->children[RIGHT])
	{
		RotationRL(node, child);
	}
	else
	{
		RotationRR(node, child);
	}
}

static void RotationLL(node_t *parent, node_t *child)
{
	assert(NULL != parent);
	assert(NULL != child);

	SwapData(parent, child);

	parent->children[LEFT] = child->children[LEFT];
	
	child->children[LEFT] = child->children[RIGHT];
	child->children[RIGHT] = parent->children[RIGHT];
	
	parent->children[RIGHT] = child;
	
	SetHeight(child);
	SetHeight(parent);
}

static void RotationRR(node_t *parent, node_t *child)
{
	assert(NULL != parent);
	assert(NULL != child);

	SwapData(parent, child);

	parent->children[RIGHT] = child->children[RIGHT];
	
	child->children[RIGHT] = child->children[LEFT];
	child->children[LEFT] = parent->children[LEFT];
	
	parent->children[LEFT] = child;
	
	SetHeight(child);
	SetHeight(parent);
}

static void RotationLR(node_t *parent, node_t *child)
{
	assert(NULL != parent);
	assert(NULL != child);
	assert(NULL != child->children[RIGHT]);
	
	RotationRR(child, child->children[RIGHT]);
	RotationLL(parent, child);
}

static void RotationRL(node_t *parent, node_t *child)
{
	assert(NULL != parent);
	assert(NULL != child);
	assert(NULL != child->children[LEFT]);
	
	RotationLL(child, child->children[LEFT]);
	RotationRR(parent, child);
}

static void SwapData(node_t *node1, node_t *node2)
{
	void *temp = NULL;
	
	assert(NULL != node1);
	assert(NULL != node2);
	
	temp = node1->data;
	node1->data = node2->data;
	node2->data =temp;
}

/* AVLCount */

size_t AVLCount(const avl_t *avl)
{
	assert(NULL != avl);	
	
	return CountNouds(avl->root);
}

static size_t CountNouds(node_t *node)
{
	size_t count = 0;	

	if(NULL != node)
	{
		count += CountNouds(node->children[LEFT]);
        count += CountNouds(node->children[RIGHT]);
        return count + 1;
	}
	
	return count;
}

/* AVLFind */

void *AVLFind(const avl_t *avl, const void *to_search)
{
	assert(NULL != avl);	

	if(!AVLIsEmpty(avl))
	{
		return Search(avl, avl->root, to_search);
	}
	else
	{
		return NULL;
	}
}

static void *Search(const avl_t *avl, node_t *node, const void *to_search)
{
	int cmp_result = 0;

	assert(NULL != avl);	
	assert(NULL != node);

	if(to_search == node->data)
	{
		return node->data;
	}
	
	cmp_result = (*avl->cmp)(to_search, node->data, avl->param);
	cmp_result = CMP_CHILD_DIRECTION(cmp_result);
	
	if(NULL != node->children[cmp_result])
	{
		return Search(avl, node->children[cmp_result], to_search);
	}
	else
	{
		return 	NULL;
	}
}

/* AVLForEach */

int AVLForEach(avl_t *avl, avl_action_func_t act_func, void *param, 
			   int order_type)
{
	assert(NULL != avl);
	assert(NULL != act_func);
	assert(2 >= order_type && 0 <= order_type);
	
	return (*g_actionLUT[order_type])(avl->root, act_func, param);
}

static int AVLActionPreOrder(node_t *node, 
							 avl_action_func_t act_func, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != act_func);
	
    if (NULL != node)
    {
    	status = (*act_func)(node->data, param);
        if(SUCCESS != status)
        {
        	return status;
        }
        
        status = AVLActionPreOrder(node->children[LEFT], act_func, param);
        if(SUCCESS != status)
        {
        	return status;
        }
        
        status = AVLActionPreOrder(node->children[RIGHT], act_func, param);
        if(SUCCESS != status)
        {
        	return status;
        }
    }
    
    return SUCCESS;
}

static int AVLActionInOrder(node_t *node, 
							avl_action_func_t act_func, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != act_func);
	
    if (NULL != node)
    {
    	status = AVLActionInOrder(node->children[LEFT], act_func, param);
    	if(SUCCESS != status)
    	{
			return status;  
		}
        
        status = (*act_func)(node->data, param);
        if(SUCCESS != status)
        {
        	return status;  
        }
        
        status = AVLActionInOrder(node->children[RIGHT], act_func, param);
        if(SUCCESS != status)
        {
        	return status;  
        }
    }
    
    return SUCCESS;
}

static int AVLActionPostOrder(node_t *node, 
							  avl_action_func_t act_func, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != act_func);
	
    if (NULL != node)
    {
        status = AVLActionPostOrder(node->children[LEFT], act_func, param);
        if(SUCCESS != status)
        {
        	 return status;  
        }
        
        status = AVLActionPostOrder(node->children[RIGHT], act_func, param);
        if(SUCCESS != status)
        {
        	 return status;  
        }
        
       	status = (*act_func)(node->data, param);
       	if(SUCCESS != status)
        {
        	 return status;  
        }
    }
    
    return SUCCESS;
}

void AVLPrintAscending(avl_t *avl)
{
    printf("Printing:\n");
    RecPrintAscending(ROOT);
    printf("\n");
}

static void RecPrintAscending(node_t *root)
{
    if (NULL == root)
    {
        return;
    }
    
    RecPrintAscending(root->children[LEFT]);
    printf("%d ", *(int *)root->data);
    RecPrintAscending(root->children[RIGHT]);
}

void AVLPrint(avl_t *avl)
{
    printf("Printing:\n");
    RecLevel(ROOT, AVLHeight(avl), 1);

}

static void RecLevel(node_t *node, int height, int level)
{
    if(level > height)
    {
        printf("\n~~~~~~~~~~~~~~~~~~\n");
        return;
    }
    RecPrint(node, level);
    printf("\n");
    RecLevel(node, height, level+1);

}

static void RecPrint(node_t *root, int level)
{
    if (NULL == root)
    {
        return;
    }
    
    if(level == 1)
    {
        printf("%d ", *(int *)root->data);
        return;
    }
    
    RecPrint(root->children[LEFT], level - 1);
    RecPrint(root->children[RIGHT], level - 1);
}





typedef struct asciinode_struct asciinode_t;

struct asciinode_struct
{
  asciinode_t * left, * right;

  /*length of the edge from this node to its children*/
  int edge_length; 
    
  int height;      

  int lablen;

  /*-1=I am left, 0=I am root, 1=right  */ 
  int parent_dir;   
                         
  /*max supported unit32 in dec, 10 digits max*/
  char label[11];  
};

/*****************************print tree***************************************/
#include <stdio.h>
#include <string.h>

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

/*adjust gap between left and right nodes*/
int gap = 3;  

/*used for printing next node in the same level, */
/*this is the x coordinate of the next char printed*/
int print_next;    

int MIN (int X, int Y)  
{
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)  
{
  return ((X) > (Y)) ? (X) : (Y);
}

static asciinode_t * BuildAsciiTreeRecursive(node_t *t) 
{
  asciinode_t * node;
  
  if (t == NULL) return NULL;

  node = malloc(sizeof(asciinode_t));
  node->left = BuildAsciiTreeRecursive(t->children[LEFT]);
  node->right = BuildAsciiTreeRecursive(t->children[RIGHT]);
  
  if (node->left != NULL) 
  {
    node->left->parent_dir = -1;
  }

  if (node->right != NULL) 
  {
    node->right->parent_dir = 1;
  }

  sprintf(node->label, "%d", *(int *)t->data);
  node->lablen = strlen(node->label);

  return node;
}


/*Copy the tree into the ascii node structre*/
static asciinode_t * BuildAsciiTree(node_t *t) 
{
  asciinode_t *node;
  if (t == NULL) return NULL;
  node = BuildAsciiTreeRecursive(t);
  node->parent_dir = 0;
  return node;
}

/*Free all the nodes of the given tree*/
static void FreeAsciiTree(asciinode_t *node) 
{
  if (node == NULL) return;
  FreeAsciiTree(node->left);
  FreeAsciiTree(node->right);
  free(node);
}

/*The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
/fields have been computed for this tree.*/
static void ComputeLprofile(asciinode_t *node, int x, int y) 
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
  if (node->left != NULL) 
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
    {
	    lprofile[y+i] = MIN(lprofile[y+i], x-i);
    }
  }
  ComputeLprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  ComputeLprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

static void ComputeRprofile(asciinode_t *node, int x, int y) 
{
  int i, notleft;
  if (node == NULL) return;
  notleft = (node->parent_dir != -1);
  rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
  if (node->right != NULL) 
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
    {
	    rprofile[y+i] = MAX(rprofile[y+i], x+i);
    }
  }
  ComputeRprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  ComputeRprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

/*This function fills in the edge_length and 
height fields of the specified tree*/
static void computeEdgeLengths(asciinode_t *node) 
{
  int h, hmin, i, delta;
  if (node == NULL) return;
  computeEdgeLengths(node->left);
  computeEdgeLengths(node->right);

  /* first fill in the edge_length of node */
  if (node->right == NULL && node->left == NULL) 
  {
	  node->edge_length = 0;
  } 
  else 
  {
    if (node->left != NULL) 
    {
	    for (i=0; i<node->left->height && i < MAX_HEIGHT; i++) 
      {
		    rprofile[i] = -INFINITY;
	    }
	    ComputeRprofile(node->left, 0, 0);
	    hmin = node->left->height;
    } 
    else 
    {
	    hmin = 0;
    }
	  if (node->right != NULL) 
    {
	    for (i=0; i<node->right->height && i < MAX_HEIGHT; i++) 
      {
		    lprofile[i] = INFINITY;
	    }
	    ComputeLprofile(node->right, 0, 0);
	    hmin = MIN(node->right->height, hmin);
    } 
    else 
    {
	    hmin = 0;
    }
	  delta = 4;
	  for (i=0; i<hmin; i++) 
    {
	    delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
    }
	  
    /*If the node has two children of height 1, then we allow the
    two leaves to be within 1, instead of 2 */
	  if (((node->left != NULL && node->left->height == 1) ||
	      (node->right != NULL && node->right->height == 1))&&delta>4) 
    {
      delta--;
    }
	    
    node->edge_length = ((delta+1)/2) - 1;
  }

  /*now fill in the height of node*/
  h = 1;
  if (node->left != NULL) 
  {
	  h = MAX(node->left->height + node->edge_length + 1, h);
  }
  if (node->right != NULL) 
  {
	  h = MAX(node->right->height + node->edge_length + 1, h);
  }
  node->height = h;
}

/*This function prints the given level of the given tree, assuming
that the node has the given x cordinate.*/
static void PrintLevel(asciinode_t *node, int x, int level) 
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  if (level == 0) 
  {
	  for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++) 
    {
	    printf(" ");
    }
	  print_next += i;
	  printf("%s", node->label);
	  print_next += node->lablen;
  } 
  else if (node->edge_length >= level) 
  {
	  if (node->left != NULL) 
    {
	    for (i=0; i<(x-print_next-(level)); i++) 
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("/");
	    print_next++;
    }
	  if (node->right != NULL) 
    {
	    for (i=0; i<(x-print_next+(level)); i++) 
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("\\");
	    print_next++;
    }
  } 
  else 
  {
	  PrintLevel(node->left, 
                x-node->edge_length-1, 
                level-node->edge_length-1);
	  PrintLevel(node->right, 
                x+node->edge_length+1, 
                level-node->edge_length-1);
  }
}

/*prints ascii tree for given Tree structure*/
static void PrintAsciiTree(node_t *t) 
{
  asciinode_t *proot;
  int xmin, i;
  if (t == NULL) return;
  proot = BuildAsciiTree(t);
  computeEdgeLengths(proot);
  for (i=0; i<proot->height && i < MAX_HEIGHT; i++) 
  {
	  lprofile[i] = INFINITY;
  }
  ComputeLprofile(proot, 0, 0);
  xmin = 0;
  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) 
  {
	  xmin = MIN(xmin, lprofile[i]);
  }
  for (i = 0; i < proot->height; i++) 
  {
	  print_next = 0;
	  PrintLevel(proot, -xmin, i);
	  printf("\n");
  }
  if (proot->height >= MAX_HEIGHT) 
  {
	  printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
  }
  FreeAsciiTree(proot); 
}

void PrintTree(avl_t *avl)
{
	PrintAsciiTree(avl->root);
}

