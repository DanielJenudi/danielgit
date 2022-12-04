/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Yaniv
Date: 29/03/2022
File: Data struct - Task
Description: source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <assert.h>/* assert */
#include <stdlib.h>/* malloc, free */

#include "task.h"/* task.h */

	
struct task
{
    time_t time;
    task_action_func_t action_func;
    void *action_param;
    task_clean_up_func_t clean_up_func;
    void *clean_up_param;
    ilrd_uid_t uid;
};

task_t *TaskCreate(task_action_func_t action_func, void *action_param, 
		  task_clean_up_func_t clean_up_func, void *clean_up_param, time_t time)
{
	task_t *task = NULL;
	
	assert(NULL != action_func);
	assert(NULL != clean_up_func);
	
	task = (task_t *)malloc(sizeof(task_t));
	if(NULL == task)
	{
		return NULL;
	}
	
	/*init task*/
	task->uid = UIDCreate();
	if(UIDIsSame(UIDBadUID, task->uid))
	{
		free(task);
		return NULL;
	}
	
	
	task->time = time;
	
	task->action_func = action_func;
	task->action_param = action_param;
	
	task->clean_up_func = clean_up_func;
	task->clean_up_param = clean_up_param;
	/*end of init*/
	
	return task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->clean_up_func(task->clean_up_param);
	free(task);
	task = NULL;
}

int TaskExecute(task_t *task)
{
	assert(NULL != task);
	return (*task->action_func)(task->action_param);
}

time_t TaskGetTime(const task_t *task)
{
	assert(NULL != task);
	return task->time;
}

void TaskSetTime(task_t *task, time_t add_time)
{	
	assert(NULL != task);
	
	task->time += add_time;
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}

