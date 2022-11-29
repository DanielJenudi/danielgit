#include <stdio.h>/* printf */

#include "/home/daniel/git/ds/queue/queue.h"

typedef struct node node_t;

enum Status
{
    FALSE = 0,
    TRUE = 1
};

struct node
{
    node_t *left;
    node_t *right;
    int data;
};

void PrintTreeByLevel(node_t *node, queue_t *queue);

/* gd -o test PrintTreeByLevel.c ./link_list/link_list.c queue.c */

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

    queue_t *queue = QueueCreate();

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

    PrintTreeByLevel(&node0, queue);
    QueueDestroy(queue);

    queue = NULL;

    return 0;
}

void PrintTreeByLevel(node_t *node, queue_t *queue)
{
    node_t *peek_node = NULL;

    QueueEnqueue(queue, node);

    while (FALSE == QueueIsEmpty(queue))
    {
        peek_node = (node_t *)QueuePeek(queue);

        if (NULL != peek_node->left)
        {
            QueueEnqueue(queue, peek_node->left);
        }

        if (NULL != peek_node->right)
        {
            QueueEnqueue(queue, peek_node->right);
        }

        printf("%d\n", peek_node->data);
        QueueDequeue(queue);
    }
}