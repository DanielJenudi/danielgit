/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Osher
Date: 30/03/2022
File: Data struct - Schedular
Description: Header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*******************************************************************************
                        Data struct - Schedular
********************************************************************************

Attributes and policy:
- creat a Schedular to mange tasks at a diffrent time.
- task get action func to execute, and clean up func to clean after the action, 
  sidelong time of execute.
- stop tasks can be add.

--------------------------------------------------------------------------------
notes:
Run - keep running until done even if tasks failed
      return 0 for success for all, or fail for at list one failure
=> action func policy :
negative - if execute task failed and clean function should be done
zero     - if execute task succeeded and clean function should be done
positive - if execute task failed or succeeded and should be reschedule
* self-removal of task enable 
* self-reschedule of task enable 
* in AddTask - time is absolute


--------------------------------------------------------------------------------

Operations on DS:
- create Schedular
- destroy Schedular
- remove task from Schedular
- clear Schedular from all tasks
- run Schedular
- stop Schedular
- get number of tasks
- get if Schedular is empty

*******************************************************************************/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "uid.h" /* uid.h */
#include <stddef.h>
/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct sched sched_t;

typedef int(*sc_action_func_t)(void *action_param);
/* action function of tasks run when execute run */

typedef void(*sc_clean_up_func_t)(void *clean_up_param);
/* clean function of tasks run when execute destroy or task finish*/


/*******************************************************************************
SchedCreate
Description: creates a new Schedular
Return value:
	- new Schedular, in case of fail return NULL.
Complexity: O(1) time
*******************************************************************************/
sched_t *SchedCreate(void);

/******************************************************************************
SchedDestroy
Description: destroy a Schedular
Parameters: 
	- Schedular
Complexity: O(1) time
NOTE: clean up function will operate in SchedDestroy
*******************************************************************************/
void SchedDestroy(sched_t *sched);

/*******************************************************************************
SchedAddTask
Description: add new task to Schedular
Parameters: 
	- Schedular
	- action func
	- action param
	- clean up func
	- clean up param
	- time	
Return value:
	- the UID of the new task.
Complexity: O(n) time
*******************************************************************************/
ilrd_uid_t SchedAddTask(sched_t *sched, sc_action_func_t action_func,
						void *action_param, sc_clean_up_func_t clean_up_func,
						void *clean_up_param, time_t time);
						
/******************************************************************************
SchedRemoveTask
Description: remove a task from Schedular by UID
Parameters: 
	- Schedular
	- UID
Complexity: O(n) time
NOTE: clean up function will operate in SchedRemoveTask
*******************************************************************************/
void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid);

/*******************************************************************************
SchedRun
Description: run all tasks in Schedular
Parameters: 
	- Schedular
Return value:
	- return 0 if all execute succeed, else return 1
Complexity: O(1) time
*******************************************************************************/
int SchedRun(sched_t *sched);

/*******************************************************************************
SchedStop
Description: stop running Schedular
Parameters: 
	- Schedular
Complexity: O(1) time
NOTE: if SchedStop execute while Schedular is runnig, Schedular immediately stop
	  and all the remaining tasks stay in the Scheduler
*******************************************************************************/
void SchedStop(sched_t *sched);

/******************************************************************************
SchedClear
Description: clear a Schedular from all tasks
Parameters: 
	- Schedular
Complexity: O(n) time
*******************************************************************************/
void SchedClear(sched_t *sched);

/*******************************************************************************
SchedSize
Description: return the number of tasks in a Schedular
Parameters: 
	- Schedular
Return value:
	- the number of tasks in a Schedular
Complexity: O(n) time 
*******************************************************************************/
size_t SchedSize(const sched_t *sched);

/*******************************************************************************
SchedIsEmpty
Description: return if Schedular is empty
Parameters: 
	- Schedular
Return value:
	- return 1 if Schedular is empty, else return 0
Complexity: O(1) time
*******************************************************************************/
int SchedIsEmpty(const sched_t *sched);

#endif /* __SCHED_H__ */


