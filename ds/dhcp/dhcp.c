/*****************************************************************************
 *Author: Daniel Jenudi														 *
 *Reviewer: Ran          													 *
 *Date: 25/05/2022															 *
 *dhcp.c																		 *
 ******************************************************************************/

#include <assert.h>   /* assert */
#include <arpa/inet.h>/* inet_pton, inet_ntop */
#include <stdlib.h>   /* malloc, free */
#include <string.h>   /* strncmp */

#include "dhcp.h"

#define IP_SIZE 16
#define IP_BITS_SIZE 32
#define IS_NODE_FULL(node) (node->state == FULL ? TRUE : FALSE)

typedef struct node node_t;

enum Children
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN
};

enum Node_State
{
    UNFULL = 0,
    FULL
};

enum Inet_Status
{
    INET_PTON_FAIL = 0,
    INET_PTON_SUCCESS
};

enum Overall_Status
{
    SUCCESS = 0,
    FAIL
};

enum GetReq_Status
{
    FALSE = 0,
    TRUE,
    ALLOC_FAIL
};

struct DHCP
{
    node_t *root;
    size_t rev_subnet;
    char network[4];
};

struct node
{
    node_t *children[NUM_OF_CHILDREN];
    int state;
};

static int InitReservedIP(dhcp_t *dhcp);
static int ExtractIP(char *buffer, const char *ip);
static int ReadBit(int ip, size_t index);
static int IsChildFull(node_t *node, int direction);
static int IsBothChildrenFull(node_t *node);
static int GetReqIP(node_t *root, size_t hight, int req_ip);
static int GetFreeIP(node_t *root, size_t hight, int *new_ip);
static int CheckNetwork(int dhcp_net, int user_net, size_t rev_subnet);
static int SetNetworkToNewIp(int dhcp_net, char *user_net, size_t subnet);
static int intToIP(int new_ip, char *buffer);
static size_t Pow(size_t x, size_t y);
static size_t CalcFreeSpace(node_t *root, size_t hight, int result);
static node_t *CreatNode(void);
static void DestroyTree(node_t *root);
static void FreeIP(node_t *root, size_t hight, int ip);
static int ReservedTwoBigestIP(node_t *root, size_t hight);
static int Inverter(int to_invert);
static void Swap(char *x, char *y);

/* ~~~~~~~~~~ DHCPCreate ~~~~~~~~~~ */

dhcp_t *DHCPCreate(const char *network, size_t subnet)
{
    dhcp_t *dhcp = NULL;
    node_t *root = NULL;

    assert(NULL != network);
    assert(30 >= subnet);
    assert(3 <= subnet);

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return NULL;
    }

    if (INET_PTON_FAIL == ExtractIP(dhcp->network, network))
    {
        free(dhcp);
        dhcp = NULL;
        return NULL;
    }

    root = CreatNode();
    if (NULL == root)
    {
        free(dhcp);
        dhcp = NULL;
        return NULL;
    }

    /*init dhcp*/
    dhcp->root = root;
    dhcp->rev_subnet = IP_BITS_SIZE - subnet;

    if (FAIL == InitReservedIP(dhcp))
    {
        DHCPDestroy(dhcp);
        dhcp = NULL;

        return NULL;
    }

    return dhcp;
}

static int InitReservedIP(dhcp_t *dhcp)
{
    int bigest_ip = ~0;

    assert(NULL != dhcp);

    if (FAIL == ReservedTwoBigestIP(dhcp->root, dhcp->rev_subnet))
    {
        return FAIL;
    }

    if (FAIL == GetFreeIP(dhcp->root, dhcp->rev_subnet, &bigest_ip))
    {
        return FAIL;
    }

    return SUCCESS;
}

static int ReservedTwoBigestIP(node_t *root, size_t hight)
{
    assert(NULL != root);

    if (hight == 1)
    {
        root->children[RIGHT] = CreatNode();
        if (NULL == root->children[RIGHT])
        {
            return FAIL;
        }

        root->children[LEFT] = CreatNode();
        if (NULL == root->children[LEFT])
        {
            return FAIL;
        }

        root->state = FULL;
        root->children[RIGHT]->state = FULL;
        root->children[LEFT]->state = FULL;

        return SUCCESS;
    }

    root->children[RIGHT] = CreatNode();
    if (NULL == root->children[RIGHT])
    {
        return FAIL;
    }
    else
    {
        return ReservedTwoBigestIP(root->children[RIGHT], hight - 1);
    }
}

static node_t *CreatNode(void)
{
    node_t *node = NULL;

    node = (node_t *)malloc(sizeof(node_t));
    if (NULL == node)
    {
        return NULL;
    }

    /*init root*/
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->state = UNFULL;

    return node;
}

/* ~~~~~~~~~~ DHCPDestroy ~~~~~~~~~~ */

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    DestroyTree(dhcp->root);

    free(dhcp);
    dhcp = NULL;
}

static void DestroyTree(node_t *root)
{
    if (NULL != root)
    {
        DestroyTree(root->children[LEFT]);
        DestroyTree(root->children[RIGHT]);

        free(root);
        root = NULL;
    }
}

/* ~~~~~~~~~~ DHCPAllocIP ~~~~~~~~~~ */

int DHCPAllocIP(dhcp_t *dhcp, const char *req_ip, char *buffer)
{
    size_t subnet = 0;

    assert(NULL != dhcp);
    assert(NULL != buffer);

    subnet = IP_BITS_SIZE - dhcp->rev_subnet;

    if (NULL == req_ip)
    {
        if (SUCCESS == GetFreeIP(dhcp->root, dhcp->rev_subnet, (int *)buffer))
        {
            return SetNetworkToNewIp(*(int *)dhcp->network, buffer, subnet);
        }
        else
        {
            return FAIL;
        }
    }

    if (INET_PTON_FAIL == ExtractIP(buffer, req_ip))
    {
        return FAIL;
    }

    if (SUCCESS == CheckNetwork(*(int *)dhcp->network, *(int *)buffer, subnet) &&
        SUCCESS == GetReqIP(dhcp->root, dhcp->rev_subnet, Inverter(*(int *)buffer)))
    {
        memcpy(buffer, req_ip, IP_SIZE);
        return SUCCESS;
    }

    if (SUCCESS == GetFreeIP(dhcp->root, dhcp->rev_subnet, (int *)buffer))
    {
        return SetNetworkToNewIp(*(int *)dhcp->network, buffer, subnet);
    }

    *(int *)buffer = 0;
    return FAIL;
}

static int CheckNetwork(int dhcp_net, int user_net, size_t rev_subnet)
{
    size_t i = 0;
    size_t subnet = IP_BITS_SIZE - rev_subnet;

    user_net = Inverter(user_net) >> rev_subnet;
    dhcp_net = Inverter(dhcp_net) >> rev_subnet;

    for (i = 0; i < subnet; ++i)
    {
        if (((dhcp_net >> i) & 1) != ((user_net >> i) & 1))
        {
            return FAIL;
        }
    }

    return SUCCESS;
}

static int GetReqIP(node_t *root, size_t hight, int req_ip)
{
    int direction = 0;

    assert(NULL != root);

    if (0 == hight)
    {
        root->state = FULL;
        return SUCCESS;
    }

    direction = ReadBit(req_ip, hight - 1);
    if ((FULL == root->state) || (FALSE != IsChildFull(root, direction)))
    {
        return FAIL;
    }

    if (FAIL == GetReqIP(root->children[direction], (hight - 1), req_ip))
    {
        return FAIL;
    }

    if (TRUE == IsBothChildrenFull(root))
    {
        root->state = FULL;
    }

    return SUCCESS;
}

static int GetFreeIP(node_t *root, size_t hight, int *new_ip)
{
    int status = FAIL;

    assert(NULL != root);
    assert(NULL != new_ip);

    if (0 == hight)
    {
        root->state = FULL;
        return SUCCESS;
    }

    if (FALSE == IsChildFull(root, LEFT))
    {
        *new_ip <<= 1;
        *new_ip += LEFT;
        status = GetFreeIP(root->children[LEFT], hight - 1, new_ip);
    }
    else if (FALSE == IsChildFull(root, RIGHT))
    {
        *new_ip <<= 1;
        *new_ip += RIGHT;
        status = GetFreeIP(root->children[RIGHT], hight - 1, new_ip);
    }

    if (TRUE == IsBothChildrenFull(root))
    {
        root->state = FULL;
    }

    return status;
}

static int IsBothChildrenFull(node_t *node)
{
    assert(NULL != node);

    if (NULL == node->children[LEFT] || NULL == node->children[RIGHT])
    {
        return FALSE;
    }
    else
    {
        return IS_NODE_FULL(node->children[LEFT]) &
               IS_NODE_FULL(node->children[RIGHT]);
    }
}

static int IsChildFull(node_t *node, int direction)
{
    assert(NULL != node);

    if (NULL == node->children[direction])
    {
        node->children[direction] = CreatNode();
        if (NULL == node->children[direction])
        {
            return ALLOC_FAIL;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return IS_NODE_FULL(node->children[direction]);
    }
}

static int SetNetworkToNewIp(int dhcp_net, char *user_net, size_t subnet)
{
    int new_ip = 0;

    assert(NULL != user_net);

    new_ip = *(int *)user_net;

    while (0 != subnet)
    {
        new_ip <<= 1;
        new_ip += (dhcp_net >> (subnet - 1)) & 1;
        --subnet;
    }

    return intToIP(new_ip, user_net);
}

static int intToIP(int new_ip, char *buffer)
{
    assert(NULL != buffer);

    if (NULL != inet_ntop(AF_INET, &new_ip, buffer, IP_SIZE))
    {
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }
}

/* ~~~~~~~~~~ DHCPFreeIP ~~~~~~~~~~ */

void DHCPFreeIP(dhcp_t *dhcp, char *ip)
{
    char buffer[4] = {0};

    assert(NULL != dhcp);
    assert(NULL != ip);

    ExtractIP(buffer, ip);
    if (FAIL == CheckNetwork(*(int *)dhcp->network, *(int *)buffer,
                             IP_BITS_SIZE - dhcp->rev_subnet))
    {
        return;
    }

    FreeIP(dhcp->root, dhcp->rev_subnet, Inverter(*(int *)buffer));
}

static void FreeIP(node_t *root, size_t hight, int ip)
{
    int direction = 0;

    assert(NULL != root);

    if (0 != hight)
    {
        direction = ReadBit(ip, hight - 1);

        if (NULL != root->children[direction])
        {
            FreeIP(root->children[direction], (hight - 1), ip);
        }
    }

    root->state = UNFULL;
}

/* ~~~~~~~~~~ DHCPAvailableIPs ~~~~~~~~~~ */

size_t DHCPAvailableIPs(const dhcp_t *dhcp)
{
    size_t max_capacity = 0;

    assert(NULL != dhcp);

    max_capacity = Pow(2, dhcp->rev_subnet);

    return CalcFreeSpace(dhcp->root, dhcp->rev_subnet, max_capacity);
}

static size_t CalcFreeSpace(node_t *root, size_t hight, int result)
{
    assert(NULL != root);

    if (FULL == root->state && NULL == root->children[LEFT] &&
        NULL == root->children[RIGHT])
    {
        result -= 1;
    }

    if (NULL != root->children[LEFT])
    {
        result = CalcFreeSpace(root->children[LEFT], hight - 1, result);
    }

    if (NULL != root->children[RIGHT])
    {
        result = CalcFreeSpace(root->children[RIGHT], hight - 1, result);
    }

    return result;
}

/* ~~~~~~~~~~ General Functions ~~~~~~~~~~ */

static int ExtractIP(char *buffer, const char *ip)
{
    assert(NULL != buffer);
    assert(NULL != ip);

    return inet_pton(AF_INET, ip, buffer);
}

static int ReadBit(int ip, size_t index)
{
    assert(32 > index);

    return ((ip >> index) & 1);
}

static size_t Pow(size_t x, size_t y)
{
    size_t result = x;

    if (0 == y)
    {
        return 0;
    }

    while (1 != y)
    {
        result *= x;
        --y;
    }

    return result;
}

static int Inverter(int to_invert)
{
    char *start = (char *)&to_invert;
    char *end = start + 3;

    Swap(start, end);
    ++start;
    --end;
    Swap(start, end);

    return to_invert;
}

static void Swap(char *x, char *y)
{
    char temp = 0;

    assert(NULL != x);
    assert(NULL != y);

    temp = *x;
    *x = *y;
    *y = temp;
}

/*******************************************************************************
                                PRINT TREE
*******************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1 << 20)

typedef struct asciinode_struct asciinode_t;

struct asciinode_struct
{
    asciinode_t *left, *right;

    /*length of the edge from this node to its children*/
    int edge_length;

    int height;

    int lablen;

    /*-1=I am left, 0=I am root, 1=right  */
    int parent_dir;

    /*max supported unit32 in dec, 10 digits max*/
    char label[11];
};

void PrintTree(dhcp_t *dhcp);
static void PrintAsciiTree(node_t *t);
static void PrintLevel(asciinode_t *node, int x, int level);
static void computeEdgeLengths(asciinode_t *node);
static void ComputeLprofile(asciinode_t *node, int x, int y);
static void ComputeRprofile(asciinode_t *node, int x, int y);
static void FreeAsciiTree(asciinode_t *node);
static asciinode_t *BuildAsciiTree(node_t *t);

/*adjust gap between left and right nodes*/
int gap = 3;

/*used for printing next node in the same level, */
/*this is the x coordinate of the next char printed*/
int print_next;

int MIN(int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}

static asciinode_t *BuildAsciiTreeRecursive(node_t *t)
{
    asciinode_t *node;

    if (t == NULL)
        return NULL;

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

    sprintf(node->label, "%d", t->state);
    node->lablen = strlen(node->label);

    return node;
}

/*Copy the tree into the ascii node structre*/
static asciinode_t *BuildAsciiTree(node_t *t)
{
    asciinode_t *node;
    if (t == NULL)
        return NULL;
    node = BuildAsciiTreeRecursive(t);
    node->parent_dir = 0;
    return node;
}

/*Free all the nodes of the given tree*/
static void FreeAsciiTree(asciinode_t *node)
{
    if (node == NULL)
        return;
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
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    ComputeLprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    ComputeLprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

static void ComputeRprofile(asciinode_t *node, int x, int y)
{
    int i, notleft;
    if (node == NULL)
        return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    ComputeRprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    ComputeRprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

/*This function fills in the edge_length and
height fields of the specified tree*/
static void computeEdgeLengths(asciinode_t *node)
{
    int h, hmin, i, delta;
    if (node == NULL)
        return;
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
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
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
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
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
        for (i = 0; i < hmin; i++)
        {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        /*If the node has two children of height 1, then we allow the
        two leaves to be within 1, instead of 2 */
        if (((node->left != NULL && node->left->height == 1) ||
             (node->right != NULL && node->right->height == 1)) &&
            delta > 4)
        {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
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
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    if (level == 0)
    {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
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
            for (i = 0; i < (x - print_next - (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL)
        {
            for (i = 0; i < (x - print_next + (level)); i++)
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
                   x - node->edge_length - 1,
                   level - node->edge_length - 1);
        PrintLevel(node->right,
                   x + node->edge_length + 1,
                   level - node->edge_length - 1);
    }
}

/*prints ascii tree for given Tree structure*/
static void PrintAsciiTree(node_t *t)
{
    asciinode_t *proot;
    int xmin, i;
    if (t == NULL)
        return;
    proot = BuildAsciiTree(t);
    computeEdgeLengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
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

void PrintTree(dhcp_t *dhcp)
{
    PrintAsciiTree(dhcp->root);
}
