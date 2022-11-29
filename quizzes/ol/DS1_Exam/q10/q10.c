#include <stdlib.h>/* malloc, free */
#include <stdio.h>/* printf */

#define Q_SIZE 4


typedef struct Queue
{
	char queue[Q_SIZE];
	size_t num_of_elements;
	size_t head;
} queue_t;

void Push(queue_t *queue, char c);
void Pop(queue_t *queue);
queue_t *Creat(void);
void Destroy(queue_t *queue);
char Peek(queue_t *queue);

int main()
{
	queue_t *queue = Creat();
	
	Push(queue, 't');
	Push(queue, 's');
	Push(queue, 'e');
	Push(queue, 'T');
	
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	
	Push(queue, 'u');
	Push(queue, 'S');
	Push(queue, ' ');
	
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	
	Push(queue, 's');
	Push(queue, 'e');
	Push(queue, 'c');
	Push(queue, 'c');
	
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	printf("%c", Peek(queue));
	Pop(queue);
	
	Push(queue, 's');
	printf("%c\n", Peek(queue));
	Pop(queue);

	Destroy(queue);
	
	return 0;
}

void Push(queue_t *queue, char c)
{
	size_t insert_index = 0;
	
	insert_index = (queue->head + 1) % Q_SIZE;
	queue->queue[insert_index] = c;
	++queue->num_of_elements;	
	queue->head = insert_index;
}

void Pop(queue_t *queue)
{
	if(0 == queue->head)
	{
		queue->head = Q_SIZE - 1;
	}
	else
	{
		--queue->head;	
	}
	
	--queue->num_of_elements;
}

char Peek(queue_t *queue)
{
	return queue->queue[queue->head];
}

queue_t *Creat(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	
	queue->head = 0;
	queue->head = 0;
	
	return queue;
}

void Destroy(queue_t *queue)
{
	free(queue);
	queue = NULL;
}









