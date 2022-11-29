#ifndef __LINKE_LIST_H__
#define __LINKE_LIST_H__

#include <stddef.h> /* size_t */

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

/*~~~~~Flip~~~~~*/
node_t *Flip(node_t *head);
/*~~~~~HasLoop~~~~~*/
int HasLoop(const node_t *head);
/*~~~~~FindIntersection~~~~~*/
node_t *FindIntersection(node_t *head1, node_t *head2);
int CountSize(node_t *runner1);
node_t * Equality(int steps, node_t *runner);
node_t *FindMeetPoint(node_t *runner1, node_t *runner2);


#endif /*__LINKE_LIST_H__*/
