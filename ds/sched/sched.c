/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Osher
Date: 30/03/2022
File: Data struct - Schedular
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdlib.h>/* malloc, free */
#include <assert.h>/* assert */
#include <unistd.h>/* sleep */
#include <time.h>/* time */

#include "pq_heap.h"    /* pq.h */
#include "task.h" /* task.h */
#include "sched.h"    /* ds functions */

struct sched
{
	pq_t *pq;
	task_t *current_task;
	short stop_flag;
};

enum
{
	FALSE = 0,
	TRUE = 1,
	FAIL = 1
};

static void WaitTime(time_t task_time);
static int pq_is_match(const void *current_uid, void *remove_uid);
static int pq_cmp_func(const void *current_task, const void *new_task, 
					   void *param);

static int pq_cmp_func(const void *current_task, const void *new_task, 
					   void *param)
{
	(void)param;
	return (TaskGetTime(new_task) - TaskGetTime(current_task));
}

static int pq_is_match(const void *current_uid, void *remove_uid)
{
	return UIDIsSame(TaskGetUID(current_uid), *(ilrd_uid_t *)remove_uid);
}

sched_t *SchedCreate(void)
{
	sched_t *sched = (sched_t *)malloc(sizeof(sched_t));
	if(NULL == sched)
	{
		return NULL;
	}
	
	sched->pq = PQCreate(pq_cmp_func, NULL);
	if(NULL == sched->pq)
	{
		free(sched);
		sched = NULL;
		return NULL;
	}
	
	sched->current_task = NULL;
	sched->stop_flag = FALSE;
	
	return sched;
}

void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	SchedClear(sched);
	
	PQDestroy(sched->pq);
	sched->pq = NULL;

	free(sched);
	sched = NULL;
}
			    
size_t SchedSize(const sched_t *sched)
{
	size_t activ_task = 0;

	assert(NULL != sched);
	
	if(sched->current_task != NULL)
	{
		activ_task = 1;
	}
	
	return PQSize(sched->pq) + activ_task;
}			    

int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	if(sched->current_task != NULL)
	{
		return 0;
	}
	
	return PQIsEmpty(sched->pq);
}				    
	
ilrd_uid_t SchedAddTask(sched_t *sched, 
						sc_action_func_t action_func, void *action_param,
						sc_clean_up_func_t clean_up_func,
						void *clean_up_param, time_t time)
{
	task_t *task = NULL;
	
	assert(NULL != sched);
	assert(NULL != action_func);
	assert(NULL != clean_up_func);

	task = TaskCreate(action_func, action_param, clean_up_func, clean_up_param,
					  time);
	if(NULL == task)
	{
		return UIDBadUID;
	}
	
	if(FAIL == PQEnqueue(sched->pq ,task))
	{
		TaskDestroy(task);
		return UIDBadUID;
	}

	return TaskGetUID(task);
}	

void SchedClear(sched_t *sched)
{
	assert(NULL != sched);

	while(!SchedIsEmpty(sched))
	{
		TaskDestroy(PQDequeue(sched->pq));
	}
}			    

void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid)
{
	task_t *task = NULL;

	assert(NULL != sched);
	
	task = PQErase(sched->pq, &uid, pq_is_match);
	if(NULL != task)
	{
		TaskDestroy(task);
	}
}
    
int SchedRun(sched_t *sched)
{
	int resched = 0;
	int status = FALSE;
	
	assert(NULL != sched);

	sched->stop_flag = FALSE;

	while(!SchedIsEmpty(sched) && FALSE == sched->stop_flag)
	{
		sched->current_task = PQPeek(sched->pq);
		WaitTime(TaskGetTime(sched->current_task));
		
		if(TaskGetTime(sched->current_task) <= time(NULL))
		{
			resched = TaskExecute(sched->current_task);
		
			if(0 < resched)
			{
				TaskSetTime(sched->current_task, resched);
				PQDequeue(sched->pq);
				PQEnqueue(sched->pq, sched->current_task);
			}
			else
			{
				TaskDestroy(PQDequeue(sched->pq));
			}
		
			if(0 > resched)
			{
				status = TRUE;
			}
		}
		
		sched->current_task = NULL;
	}
	
	
	return status;
}
				     
static void WaitTime(time_t task_time)
{
	time_t wait_time = 0;
	
	wait_time = task_time - time(NULL);

	if(0 < wait_time)
	{
		sleep(wait_time);
	}
}				    
				    
void SchedStop(sched_t *sched)
{
	assert(NULL != sched);
	sched->stop_flag = TRUE;
}					    
	
	
