#include <stdio.h>/* printf */
#include <assert.h>/* assert */

typedef struct node node_t;

struct node
{
    node_t *left; 
    node_t *right;
    int data;
};

node_t *BSTToSL(node_t *root);
static void InOrderBSTToSL(node_t *root, node_t **head, node_t **prev);
static void PrintTree(node_t *root);
static void PrintList(node_t *root);

int main()
{
    node_t node0 = {0};
    node_t node1 = {0};
    node_t node2 = {0};
    node_t node3 = {0};
    node_t node4 = {0};
    node_t node5 = {0};
    node_t node6 = {0};
    node_t node7 = {0};
    node_t node8 = {0};
    node_t node9 = {0};
    node_t *new_head = NULL;

    node0.data = 10;
    node0.left = &node1;
    node0.right = &node2;

    node1.data = 5;
    node1.left = &node3;
    node1.right = &node4;

    node2.data = 15;
    node2.left = &node5;
    node2.right = &node6;

    node3.data = 3;
    node3.left = &node7;
    node3.right = &node8;

    node4.data = 7;
    node4.left = &node9;
    node4.right = NULL;

    node5.data = 12;
    node5.left = NULL;
    node5.right = NULL;

    node6.data = 17;
    node6.left = NULL;
    node6.right = NULL;

    node7.data = 1;
    node7.left = NULL;
    node7.right = NULL;

    node8.data = 4;
    node8.left = NULL;
    node8.right = NULL;

    node9.data = 6;
    node9.left = NULL;
    node9.right = NULL;

    printf("~~~ Print Befor (tree): ~~~ \n");
    PrintTree(&node0);

    new_head = BSTToSL(&node0);

    printf("\n\n~~~ Print After (sl): ~~~\n");
    PrintList(new_head);

    printf("\n");

    return 0;
}

node_t *BSTToSL(node_t *root)
{
	node_t *prev = NULL;
	node_t *head = NULL;

	assert(NULL != root);

	InOrderBSTToSL(root, &head, &prev);

	return head;
}

static void InOrderBSTToSL(node_t *root, node_t **head, node_t **prev)
{
	assert(NULL != head);

	if(root != NULL)
	{
		InOrderBSTToSL(root->left, head, prev);

		if (*prev == NULL)
		{
			*head = root;
		}
		else
		{
			root->left = *prev;
			(*prev)->right = root;
		}
		*prev = root;

		InOrderBSTToSL(root->right, head, prev);
	}
}

static void PrintList(node_t *root)
{
    if(NULL == root)
    {
        return;
    }

		printf("%d  ", root->data);
		PrintList(root->right);
}

static void PrintTree(node_t *root)
{
    if(NULL == root)
    {
        return;
    }

    PrintTree(root->left); 
    printf("%d  ", root->data);
    PrintTree(root->right);
}