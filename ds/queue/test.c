#include <stdio.h>/*print_F*/

#include "queue.h"
#include "/home/daniel/git/ds/queue/link_list/link_list.h"



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

void TestRunningQueue();
void TestAppendQueue();
int IntComper(int x, int y);
int IsNull(void *ptr);

int main()
{

	TestRunningQueue();
	TestAppendQueue();
	
	return 0;
}

void TestRunningQueue()
{
	int a = 5, b = 6, c = 58, d = 321;
	
	queue_t *queue = QueueCreate();
	
	QueueEnqueue(queue, &a);
	QueueEnqueue(queue, &b);
	QueueEnqueue(queue, &c);
	QueueEnqueue(queue, &d);
	
	printf("\n~~~TestRunningQueue~~~\n");
	
	printf("\n---check size---\n");
	RUNTEST(IntComper(QueueGetSize(queue), 4));
	
	printf("\n---check 'a' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue), a));
	QueueDequeue(queue);
	
	printf("\n---check 'b' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue), b))
	QueueDequeue(queue);
	
	printf("\n---check is empty---\n");
	RUNTEST(IntComper(QueueIsEmpty(queue), 0));
	
	printf("\n---check 'c' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue), c))
	QueueDequeue(queue);
	
	printf("\n---check 'd' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue), d))
	QueueDequeue(queue);
	
	printf("\n---check is empty---\n");
	RUNTEST(IntComper(QueueIsEmpty(queue), 1));
	
	QueueEnqueue(queue, &a);
	printf("\n---check 'a' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue), a));
	
	QueueDestroy(queue);
}

void TestAppendQueue()
{
	int a = 5, b = 6, c = 58, d = 321;
	
	queue_t *queue1 = QueueCreate();
	queue_t *queue2 = QueueCreate();
	
	QueueEnqueue(queue1, &a);
	QueueEnqueue(queue1, &b);
	QueueEnqueue(queue2, &c);
	QueueEnqueue(queue2, &d);
	
	printf("\n~~~TestAppendQueue~~~\n");
	
	QueueAppend(queue1, queue2);
	
	printf("\n---check size---\n");
	RUNTEST(IntComper(QueueGetSize(queue1), 4));
	
	printf("\n---check 'a' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue1), a));
	QueueDequeue(queue1);
	
	printf("\n---check 'b' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue1), b))
	QueueDequeue(queue1);
	
	printf("\n---check is empty---\n");
	RUNTEST(IntComper(QueueIsEmpty(queue1), 0));
	
	printf("\n---check 'c' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue1), c))
	QueueDequeue(queue1);
	
	printf("\n---check 'd' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue1), d))
	QueueDequeue(queue1);
	
	printf("\n---check is empty---\n");
	RUNTEST(IntComper(QueueIsEmpty(queue1), 1));
	
	QueueEnqueue(queue1, &a);
	printf("\n---check 'a' value---\n");
	RUNTEST(IntComper(*(int *)QueuePeek(queue1), a));
	
	QueueDestroy(queue1);
}

int IntComper(int x, int y)
{
	if(x != y)
	{
		return FAIL;
	}
	
	return SUCCESS;
}

