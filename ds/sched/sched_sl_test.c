/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Osher
Date: 30/03/2022
File: Data struct - Schedular
Description: Test file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* system */
#include <time.h>/* time */

#include "sched.h"/* ds functions */

enum status
{
	FALSE = 0,
	TRUE
};

typedef struct Remove_Task
{
	sched_t *sched;
	ilrd_uid_t uid;
} remove_task_t;

remove_task_t *RTCreat();
void RTDestroy(void *rt);
int RemoveTask(void *rt);

void SimpleTest();
int Print(void *action_param);
int PrintAdd(void *action_param);
int AddTask(void *sched);

void RegularTest();
void SchedRunTest();

int ActionInt(void *action_param);
void CleanInt(void *clean_up_param);

int ActionStopLimit(void *action_param);
int ActionStop(void *action_param);
void CleanStop(void *clean_up_param);

static void RunTest(int test);

int main()
{
	SimpleTest();
	RegularTest();
	SchedRunTest();
	
	return 0;
}

void RegularTest()
{
	int x = 10, y = 20, z = 30;
	
	sched_t *sched = SchedCreate();
	ilrd_uid_t ilrd_uid1, ilrd_uid2;
	
	printf("\nsched should be empty: ");
	RunTest(TRUE == SchedIsEmpty(sched));
	
	printf("sched size should be 0: ");
	RunTest(0 == SchedSize(sched));
	
	ilrd_uid1 = SchedAddTask(sched, ActionInt, &x, CleanInt, &x, time(NULL));
	ilrd_uid2 = SchedAddTask(sched, ActionInt, &y, CleanInt, &y, time(NULL));
	SchedAddTask(sched, ActionInt, &z, CleanInt, &z, time(NULL));
	
	printf("sched should not be empty: ");
	RunTest(FALSE == SchedIsEmpty(sched));
	
	printf("sched size should be size: ");
	RunTest(3 == SchedSize(sched));
	
	SchedRemoveTask(sched, ilrd_uid1);
	
	printf("sched size should be (size - 1): ");
	RunTest(2 == SchedSize(sched));
	
	SchedRemoveTask(sched, ilrd_uid2);
	SchedRemoveTask(sched, ilrd_uid2);
	
	printf("sched size should be (size - 2): ");
	RunTest(1 == SchedSize(sched));
	
	SchedClear(sched);
	
	printf("sched should be empty: ");
	RunTest(TRUE == SchedIsEmpty(sched));
	
	SchedDestroy(sched);
}

void SchedRunTest()
{
	int x = 1, y = 2, z = 3;
	
	sched_t *sched = SchedCreate();
	
	SchedAddTask(sched, ActionStop, sched, CleanStop, sched, time(NULL));
	SchedAddTask(sched, ActionStopLimit, sched, CleanInt, sched, time(NULL) + 10);
	
	SchedAddTask(sched, ActionInt, &x, CleanInt, &x, time(NULL) + 1);
	SchedAddTask(sched, ActionInt, &y, CleanInt, &y, time(NULL) + 2);
	SchedAddTask(sched, ActionInt, &z, CleanInt, &z, time(NULL) + 3);
	
	SchedRun(sched);
	
	printf("Osher == 0 ? 1 : 1\n");
	SchedAddTask(sched, ActionStop, sched, CleanStop, sched, time(NULL));
	SchedAddTask(sched, ActionStopLimit, sched, CleanInt, sched, time(NULL) + 10);
	
	SchedRun(sched);
	
	SchedDestroy(sched);
}

void SimpleTest()
{
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	ilrd_uid_t uid3 = UIDBadUID;
	ilrd_uid_t uid4 = UIDBadUID;
	ilrd_uid_t uid5 = UIDBadUID;

	remove_task_t *rt = RTCreat();
	sched_t *sched = SchedCreate();
	
	(void)uid1;
	(void)uid2;
	(void)uid3;
	(void)uid4;
	(void)uid5;
	
	
	printf("is isempty: %d\n", SchedIsEmpty(sched));
	
	uid1 = SchedAddTask(sched, Print, NULL, CleanInt, 
						NULL, time(NULL) + 1);
	uid2 = SchedAddTask(sched, Print, NULL, CleanInt,
						NULL, time(NULL) + 2);
	uid3 = SchedAddTask(sched, Print, NULL, CleanInt,
						NULL, time(NULL) + 4);
	
	uid4 = SchedAddTask(sched, AddTask, sched, CleanInt,
						NULL, time(NULL) + 5);
						
	uid5 = SchedAddTask(sched, AddTask, sched, CleanInt,
						NULL, time(NULL) + 3);
			
	rt->sched = sched;
	rt->uid = uid4;	
			
	SchedAddTask(sched, RemoveTask, rt, RTDestroy, rt, time(NULL));
	
						
	printf("is isempty: %d\n", SchedIsEmpty(sched));
	
	SchedRun(sched);
	
	printf("\nis size: %lu\n", SchedSize(sched));
	printf("is isempty: %d\n", SchedIsEmpty(sched));
	
	SchedDestroy(sched);
}
/*********Remove Task Functions*****/
void RTDestroy(void *rt)
{
	free(rt);
	rt = NULL;
}

remove_task_t *RTCreat()
{
	remove_task_t *rt = (remove_task_t *)malloc(sizeof(remove_task_t));
	if(NULL == rt)
	{
		return NULL;
	}
	
	rt->sched = NULL;
	rt->uid = UIDBadUID;
	
	return rt;
}

int RemoveTask(void *rt)
{
	remove_task_t *cast = (remove_task_t *)rt;
	SchedRemoveTask(cast->sched, cast->uid);

	return 0;
}

/*********Action Tasks*****/

int AddTask(void *sched)
{
	size_t x = 2;
	SchedAddTask((sched_t *)sched, PrintAdd, (void *)x,
				 CleanInt, NULL, time(NULL) + 2);	

	return 0;
}

int PrintAdd(void *action_param)
{
	printf("\nadd action, param : %ld\n", (size_t)action_param);
	return 0;
}

int Print(void *action_param)
{
	(void)action_param;
	printf("\naction have been made\n");
	return 0;
}

int ActionStopLimit(void *action_param)
{
		SchedStop(action_param);
	
		return 0;
}

int ActionInt(void *action_param)
{
	printf("%d\n", ++(*(int *)action_param));
	return 3;
}

int ActionStop(void *action_param)
{
	FILE *fp;
	fp = fopen("stop.txt", "r");
	
	if (NULL != fp)
	{
		SchedStop(action_param);
		fclose(fp);
		
		return 0;
	}
	
	return 1;
}

/*********Clean Tasks*****/
void CleanInt(void *clean_up_param)
{
	(void)clean_up_param;
}

void CleanStop(void *clean_up_param)
{
	FILE *fp;
	fp = fopen("stop.txt", "r");
	
	if (NULL != fp)
	{
		fclose(fp);	
		system("rm stop.txt");
	}
	
	(void)clean_up_param;
}

/***************************/
static void RunTest(int test)
{
	if (1 == test)
	{
		printf("\x1b[0;34m");
		printf("OK!\n\n");
		printf("\x1b[0m");
	}
	else
	{
		printf("\x1b[1;35m");
		printf("\nTest Failed!\n\n");
		printf("\x1b[0m");
	}
}



