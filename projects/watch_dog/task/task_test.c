/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Yaniv
Date: 29/03/2022
File: Data struct - Task
Description: test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>/* printf */
#include <unistd.h>/* sleep */

#include "task.h"/* task.h */


int ActionInt(void *action_param);
void CleanInt(void *clean_up_param);

int main()
{
	int x = 10, y = 20;
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	task1 = TaskCreate(&ActionInt, &x, &CleanInt, &x, time(NULL));
	sleep(1);
	task2 = TaskCreate(&ActionInt, &y, &CleanInt, &y, time(NULL));
	
	printf("Time\n");
	printf("%ld\n", TaskGetTime(task1));
	printf("%ld\n\n", TaskGetTime(task2));
	
	printf("Execute\n");
	printf("%d\n", TaskExecute(task1));
	printf("%d\n\n", TaskExecute(task2));
	
	TaskSetTime(task1, 1);
	TaskSetTime(task2, 1);
	
	printf("NewTime\n");
	printf("%ld\n", TaskGetTime(task1));
	printf("%ld\n\n", TaskGetTime(task2));
	
	printf("Clean\n");
	TaskDestroy(task1);
	TaskDestroy(task2);
	
	return 0;
}

int ActionInt(void *action_param)
{
	printf("%d\n", *(int *)action_param);
	return 0;
}

void CleanInt(void *clean_up_param)
{
	printf("%d\n", *(int *)clean_up_param);
}










