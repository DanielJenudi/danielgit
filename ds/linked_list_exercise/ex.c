#include <stddef.h>/*NULL*/
#include <stdlib.h>/*malloc*/

#include "ex.h"

enum
{
	SUCCESS = 0,
	FAIL
};


/*~~~~~Flip~~~~~*/
node_t *Flip(node_t *head);
/*~~~~~HasLoop~~~~~*/
int HasLoop(const node_t *head);
int IntComper(int x, int y);
/*~~~~~FindIntersection~~~~~*/
node_t *FindIntersection(node_t *head1, node_t *head2);
int CountSize(node_t *runner1);
node_t * Equality(int steps, node_t *runner);
node_t *FindMeetPoint(node_t *runner1, node_t *runner2);


/*~~~~~TestFlip~~~~~*/
node_t *Flip(node_t *head)
{
	node_t *pre_node = NULL;
	node_t *current_node = head;
	node_t *next_node = NULL;
	
	while(NULL != current_node)
	{
		next_node = current_node->next;
		current_node->next = pre_node;
		pre_node = current_node;
		current_node = next_node;
	}
	
	return pre_node;
}

/*~~~~~HasLoop~~~~~*/
int HasLoop(const node_t *head)
{
	const node_t *jump_by_1 = head;
	const node_t *jump_by_2 = head;
	
	while(NULL != jump_by_1->next && NULL != jump_by_2->next)
	{	
		jump_by_2 = jump_by_2->next;
			
		if(jump_by_1 == jump_by_2)
		{
			return FAIL;
		}
		
		if(NULL != jump_by_2->next)
		{
			jump_by_2 = jump_by_2->next;
		}
		
		jump_by_1 = jump_by_1->next;
	}
	
	return SUCCESS;
}

/*~~~~~FindIntersection~~~~~*/
node_t *FindIntersection(node_t *head1, node_t *head2)
{
	node_t *runner1 = head1;
	node_t *runner2 = head2;
	
	int count1 = 0;
	int count2 = 0;
	
	count1 = CountSize(runner1);
	count2 = CountSize(runner2);
	
	if(count1 > count2)
	{
		runner1 = Equality(count1 - count2, runner1);
		return FindMeetPoint(runner1, runner2);
	}
	
	else
	{
		runner2 = Equality(count2 - count1, runner2);
		return FindMeetPoint(runner1, runner2);
	}
}

int CountSize(node_t *runner1)
{
	int count = 0;
	
	while(NULL != runner1->next)
	{
		runner1 = runner1->next;
		++count;
	}
	
	return count;
}

node_t *Equality(int steps, node_t *runner)
{
	while(steps != 0)
	{
		--steps;
		runner = runner->next;
	}
	
	return runner;
}

node_t *FindMeetPoint(node_t *runner1, node_t *runner2)
{
	while (NULL != runner1 && NULL != runner2)
    {
        if (runner1 == runner2)
        {
        	return runner1;
        }
        runner1 = runner1->next;
        runner2 = runner2->next;
    }
    
    return NULL;
}





