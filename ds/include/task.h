/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Yaniv
Date: 29/03/2022
File: Data struct - Task
Description: header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Data struct - Task
********************************************************************************

Attributes and policy:
- creat a task to be execute at a certain time
- task get action func to excute, and clean up func to clean after the action.
- set time of execute.

-------------------------------------------------------------------------------

Operations on DS:
- create Task
- destroy task
- execute task
- get execute time of execute task
- change execute time of execute task
- get uid of task

*******************************************************************************/

#ifndef __ILRD_TASK_H__
#define __ILRD_TASK_H__

#include <time.h> /* time_t */

#include "/home/daniel/git/ds/uid/uid.h" /* ilrd_uid_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct task task_t;

/* function run when task run */
typedef int(*task_action_func_t)(void *action_param);

/* function run when task destroy */
typedef void(*task_clean_up_func_t)(void *clean_up_param);


/*******************************************************************************
TaskCreate
Description: creates a new Task
Parameters: 
	- action func
	- action param
	- clean up func
	- clean up param
	- time	
Return value:
	- new Task, in case of fail return NULL.
Complexity: O(1) time
*******************************************************************************/
task_t *TaskCreate(task_action_func_t action_func, void *action_param, 
		 task_clean_up_func_t clean_up_func, void *clean_up_param, time_t time);

/******************************************************************************
TaskDestroy
Description: destroy a Task
Parameters: 
	- Task
Complexity: O(1) time
NOTE: clean up function will operate in TaskDestroy
*******************************************************************************/
void TaskDestroy(task_t *task);

/*******************************************************************************
TaskExecute
Description: Get Task time
Parameters: 
	- task
Return value:
	- return 0 if execute succeed, else return 1
Complexity: O(1) time
*******************************************************************************/
int TaskExecute(task_t *task);

/*******************************************************************************
TaskGetTime
Description: Get Task time
Parameters: 
	- task
Return value:
	- time of task.
Complexity: O(1) time
*******************************************************************************/
time_t TaskGetTime(const task_t *task);

/*******************************************************************************
TaskSetTime
Description: add time to Task time
Parameters: 
	- task
	- time to add
Complexity: O(1) time
*******************************************************************************/
void TaskSetTime(task_t *task, time_t add_time);

/*******************************************************************************
TaskGetUID
Description: Get Task UID
Parameters: 
	- task
Return value:
	- task UID.
Complexity: O(1) time
*******************************************************************************/
ilrd_uid_t TaskGetUID(const task_t *task);


#endif /* __ILRD_TASK_H__ */


